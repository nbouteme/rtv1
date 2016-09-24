#ifndef RAYTRACER_H
# define RAYTRACER_H

# include <cpu/math.h>
# include <cpu/scene.h>

typedef struct	s_inter_info
{
	float maxdist;
	t_primitive **out;
}				t_inter_info;

typedef struct	s_colargs
{
	t_scene *scene;
	t_ray *ray;
	t_primitive *prim;
	t_hit_info *hit;
	t_ray shadow_ray;
	t_vec3 light_dir;
}				t_colargs;

void correct_gamma(t_vec3 *framebuffer);
void bake_camray(t_camera *c);
t_ray gen_camray(int x, int y, t_camera *c);
t_vec3 color_from_ray(t_scene *scene, t_ray *from);
void handle_key(t_xmlx_window *self, int key, int act, int mods);
float deg2rad(float deg);


#endif
