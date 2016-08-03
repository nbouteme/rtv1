/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:21:01 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:11:16 by nbouteme         ###   ########.fr       */
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

typedef float (t_vec4)[4];
typedef float (t_mat4)[4][4];

typedef float (t_vec3)[3];
typedef float (t_mat3)[3][3];

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

t_vec3 *vec3_sub(t_vec3 a, t_vec3 b);
float vec3_dot(t_vec3 a, t_vec3 b);

#endif
