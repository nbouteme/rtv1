extern "C" {
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
#include <cuda/cuda.h>
#include <xmlx.h>
}

#include <ctime>
#include "ctypes.hu"
#include "scene.hu"

__global__
void draw_scene(t_cuda_scene &scene);
__host__ __device__
void cuda_bake_camray(t_ccamera *c);

cudaGraphicsResource *vbo_res;
surface<void, cudaSurfaceType2D> surRef;
int tex;

#include "device_code.cuda"

void move_camera(cuda_context *cc, int key)
{
	t_cvec3 &pos = cc->scene->cam.pos;
	t_cvec3 &forward = cc->scene->cam.dir;
	t_cvec3 left = cc->scene->cam.u;
	left.normalize();
	t_cvec3 &up = cc->scene->cam.up;
	if (key == XMLX_KEY_LEFT)
		pos = pos + left;
	else if (key == XMLX_KEY_RIGHT)
		pos = pos - left;
	else if (key == XMLX_KEY_UP)
		pos = pos + forward;
	else if (key == XMLX_KEY_DOWN)
		pos = pos - forward;
	else if (key == XMLX_KEY_KP_SUBTRACT)
		pos = pos + up;
	else if (key == XMLX_KEY_KP_ADD)
		pos = pos - up;
	//cudaMemcpy(cc->gpu_scene, cc->scene, cc->scene->size, cudaMemcpyHostToDevice);
}

void rotate_camera(cuda_context *cc, double x, double y)
{
	static int oldx = 0, oldy = 0;
	// si le bouton de la souris est enfoncé
	if(cc->mouse_state[0] == 1)
	{
		// calcule la difference d'angle par pixel pour un champs de vision de 45 deg
		float xangle = 3.141529f / 4 / 1280;
		float yangle = 3.141529f / 4 / 720;

		t_cvec3 left = cc->scene->cam.u;
		left.normalize();
		t_cvec3 &up = cc->scene->cam.up;
		t_cvec3 &dir = cc->scene->cam.dir;

		dir = rotate(dir, float(y - oldy) * -yangle, left);
		dir = rotate(dir, float(x - oldx) * xangle, up);
		up = rotate(up, float(y - oldy) * -yangle, left);
	}
	oldx = x, oldy = y;
}

extern "C"
int cuda_genimage(t_display *disp)
{
	//static int texinit = 0;
	cuda_context *cc = (cuda_context*)disp->renderer_driver->ctx;
	cuda_bake_camray(&cc->scene->cam);

	cc->scene->primitives = (t_primitive*)(((char*)cc->gpu_scene) + sizeof(*cc->scene));
	cc->scene->spots = (t_cspot*)(((char*)cc->scene->primitives) + sizeof(t_primitive) * cc->scene->n_primitives);

	cudaMemcpy(cc->gpu_scene, cc->scene, cc->scene->size, cudaMemcpyHostToDevice);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}

	cudaArray *array;
    dim3 block(8, 48, 1);
    dim3 grid(1280 / 32 / block.x, 720 / block.y, 1);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaGraphicsMapResources(1, &vbo_res, 0);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
	cudaGraphicsSubResourceGetMappedArray(&array, vbo_res, 0, 0);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
	cudaBindSurfaceToArray(surRef, array);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
	cudaEventRecord(start);
	
	draw_scene<<<grid, block>>>(*cc->gpu_scene);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
	cudaEventRecord(stop);
    cudaDeviceSynchronize();
	cudaEventSynchronize(stop);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
	cudaGraphicsUnmapResources(1, &vbo_res);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);
	printf("\r%f ms, %f fps.", milliseconds, 1.0f / (milliseconds / 1000.0f));
	fflush(stdout);
	return 0;
}

extern "C"
void cuda_fini(t_driver *driver)
{
	cudaDeviceReset();
}

void set_mouse_state(cuda_context *cc, int button, int act, int mod)
{
	(void)mod;
	cc->mouse_state[button] = act;
}

extern "C"
void cuda_init(t_display *disp)
{
	disp->key_handler = (t_keyhandle_fun) move_camera;
	disp->mouse_press_handler = (t_mousehandle_fun)set_mouse_state;
	disp->mouse_handler = (t_mousehandle_fun)rotate_camera;
	cuda_context *cc = new cuda_context;
	cc->mouse_state[0] = 0;
	tex = (int)(long)disp->disp_param;
	disp->renderer_driver->ctx = (void*)cc;

	vbo_res = 0;
	cudaGLSetGLDevice(0);
	glBindTexture(GL_TEXTURE_2D, tex);
	cudaGraphicsGLRegisterImage(&vbo_res, tex, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsSurfaceLoadStore);
	cc->scene = generate_cscene((t_iscene*)disp->user_ptr);
	cc->gpu_scene = 0;
	auto e = cudaMalloc(&cc->gpu_scene, 4096);//cc->scene->size);
}

t_primitive *new_primitive(t_primitive *alloc, t_iprimitive *base);

#define D2(a, b) a ## b
#define D(x) D2(x, _cuda_ray_intersect)

t_cuda_scene *generate_cscene(t_iscene *fn)
{
	t_ray_intersect_fun funs[4];	

	cudaMemcpyFromSymbol(&funs[0], I(plane), sizeof(void*));
	cudaMemcpyFromSymbol(&funs[1], I(sphere), sizeof(void*));
	cudaMemcpyFromSymbol(&funs[2], I(cone), sizeof(void*));
	cudaMemcpyFromSymbol(&funs[3], I(cylinder), sizeof(void*));
	int i;
	i = 0;

	t_cuda_scene *ret;
	ret = (t_cuda_scene*)malloc(sizeof(t_cuda_scene) +
								sizeof(t_primitive) * fn->n_primitives +
								sizeof(t_spot) * fn->n_spots);
	memcpy(ret->cam.dir.v, fn->cam_dir, sizeof(t_vec3));
	memcpy(ret->cam.pos.v, fn->cam_pos, sizeof(t_vec3));
	memcpy(ret->cam.up.v, fn->cam_up, sizeof(t_vec3));
	ret->primitives = (t_primitive*)(((char*)ret) + sizeof(*ret));
	ret->spots = (t_cspot*)(((char*)ret->primitives) + sizeof(t_primitive) * fn->n_primitives);
	ret->n_primitives = fn->n_primitives;
	ret->n_spots = fn->n_spots;
	ft_memcpy(&ret->spots[0], fn->spots, sizeof(t_spot) * fn->n_spots);
	while (i < fn->n_primitives)
	{
		new_primitive(&ret->primitives[i], &fn->primitives[i]);
		ret->primitives[i].type = fn->primitives[i].type;
		++i;
	}
	ret->size = sizeof(t_cuda_scene) +
		sizeof(t_primitive) * fn->n_primitives +
		sizeof(t_spot) * fn->n_spots;
	return (ret);
}
