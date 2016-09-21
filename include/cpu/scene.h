#ifndef SCENE_H
# define SCENE_H

# include <core/iscene.h>
# include <cpu/shapes.h>

typedef struct	s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	u;
	t_vec3	v;
	t_vec3	vpblp;
	float	vphw;
	float	vphh;
}				t_camera;

typedef struct	s_scene
{
	t_camera cam;
	int n_primitives;
	int n_spots;
	t_primitive *primitives;
	t_spot *spots;
}				t_scene;

t_scene *generate_scene(t_iscene *iscene);

#endif
