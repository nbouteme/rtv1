#ifndef SCENE_H
# define SCENE_H

# include <core/iscene.h>
# include <cpu/shapes.h>

typedef struct	s_scene
{
	t_vec3 cam_pos;
	t_vec3 cam_dir;
	int n_primitives;
	int n_spots;
	t_primitive *primitives;
	t_spot *spots;
}				t_scene;

t_scene *generate_scene(t_iscene *iscene);

#endif
