extern "C" {
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
#include <cuda/cuda.h>
}

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

extern "C"
void cuda_genimage(t_display *disp)
{
	//static int texinit = 0;
	cuda_context *cc = (cuda_context*)disp->renderer_driver->ctx;
	cuda_bake_camray(&cc->scene->cam);

	cudaMemcpy(cc->gpu_scene, cc->scene, cc->scene->size, cudaMemcpyHostToDevice);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}

	cudaArray *array;
    dim3 block(8, 48, 1);
    dim3 grid(1280 / block.x, 720 / block.y, 1);
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
	draw_scene<<<grid, block>>>(*cc->gpu_scene);
	{
		cudaError_t err = cudaGetLastError();
		if (err != cudaSuccess) 
			printf("Error: %d: %s\n", __LINE__, cudaGetErrorString(err));
	}
    cudaDeviceSynchronize();
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
}

extern "C"
void cuda_fini(t_driver *driver)
{
	cudaDeviceReset();
}

extern "C"
void cuda_init(t_display *disp)
{
	cuda_context *cc = new cuda_context;
	tex = (int)(long)disp->disp_param;
	disp->renderer_driver->ctx = (void*)cc;

	vbo_res = 0;
	cudaGLSetGLDevice(0);
	glBindTexture(GL_TEXTURE_2D, tex);
	cudaGraphicsGLRegisterImage(&vbo_res, tex, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsSurfaceLoadStore);
	// Par rapport a la scene sur cpu, la scene sur GPU est plate
	//cc->scene = generate_cscene((t_iscene*)disp->user_ptr);
	cc->scene = generate_cscene((t_iscene*)disp->user_ptr);
	printf("SIZE: %d\n", cc->scene->size);
	cc->gpu_scene = 0;
	auto e = cudaMalloc(&cc->gpu_scene, 4096);//cc->scene->size);
	printf("Allocated scene, size: %p, %d\n", cc->gpu_scene, cc->scene->size);
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
		ret->primitives[i].intersect = funs[fn->primitives[i].type];
		printf("assigned %p\n", ret->primitives[i].intersect);
		++i;
	}
	ret->size = sizeof(t_cuda_scene) +
		sizeof(t_primitive) * fn->n_primitives +
		sizeof(t_spot) * fn->n_spots;
	return (ret);
}
