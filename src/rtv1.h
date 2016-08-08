/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:21:01 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/08 03:46:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RTV1_H
# define	RTV1_H

# include <stdbool.h>
# include <stdlib.h>
# include <libft/std.h>
# include <math.h>

typedef enum
{
	CPU_DRIVER,
	CUDA_DRIVER
}				t_display_type;

typedef struct	s_4dvec
{
	float x;
	float y;
	float z;
	float w;
}				t_4dvec;

typedef struct	s_3dvec
{
	float x;
	float y;
	float z;
}				t_3dvec;


struct	s_3dmat_named
{
	struct	s_3dvec a;
	struct	s_3dvec b;
	struct	s_3dvec c;
};

struct	s_3dmat
{
	union
	{
		struct	s_3dmat_named n;
		struct	s_3dvec v[3];
	};
};

struct	s_4dmat_named
{
	struct	s_4dvec a;
	struct	s_4dvec b;
	struct	s_4dvec c;
	struct	s_4dvec d;
};

struct	s_4dmat
{
	union
	{
		struct	s_4dmat_named n;
		struct	s_4dvec v[4];
	};
};

union u_vec3
{
	struct s_3dvec s;
	float v[3];
}  __attribute__ ((__transparent_union__));

typedef union u_vec3 t_vec3;

union u_vec4
{
	struct s_4dvec s;
	float v[4];
} __attribute__ ((__transparent_union__));

typedef union u_vec4 t_vec4;

typedef union
{
	struct s_3dmat s;
	float v[3][3];
}				t_mat3;

typedef union
{
	struct s_4dmat s;
	float v[4][4];
}				t_mat4;

struct	s_primitive;
typedef struct	s_primitive t_primitive;

struct	s_ray;
typedef struct	s_ray t_ray;

struct	s_display;
typedef struct	s_display t_display;

typedef struct	s_hit_info
{
	t_vec3 point;
	t_vec3 normal;
	float dist;
}				t_hit_info;

typedef bool (*t_ray_intersect_fun)(struct	s_primitive *self,
									t_ray *ray,
									t_hit_info *hit);

typedef void (*t_keyhandle_fun)();
typedef void (*t_mousehandle_fun)();

typedef struct s_driver t_driver;

typedef void(*t_driver_init)(struct s_driver *self);
typedef void(*t_driver_genimage)(struct s_driver *self, t_display *disp);
typedef void(*t_driver_destroy)(struct s_driver *self);

t_driver *get_driver(t_display_type type);

#endif
