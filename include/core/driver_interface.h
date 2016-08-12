#ifndef DRIVER_INTERFACE_H
# define DRIVER_INTERFACE_H

# include <core/core.h>

typedef struct s_driver t_driver;
typedef void(*t_driver_init)(struct s_driver *self);
typedef void(*t_driver_genimage)(struct s_driver *self, t_display *disp);
typedef void(*t_driver_destroy)(struct s_driver *self);
t_driver *get_driver(t_display_type type);

# ifndef HIDE_DRIVER_DEF

typedef struct	s_driver
{
	t_driver_init			init;
	t_driver_genimage		genimage;
	t_driver_destroy		destroy;
	void					*ctx;
	t_display_init_param	param;
}				t_driver;

#endif

#endif
