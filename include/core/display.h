/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:32:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 11:10:43 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <core/core.h>

typedef struct s_driver		t_driver;
typedef struct s_display	t_display;

typedef void				(*t_keyhandle_fun)		();
typedef void				(*t_mousehandle_fun)	();
typedef void				(*t_display_init_fun)	(t_display*);
typedef int					(*t_display_gen_fun)	(t_display*);
typedef void				(*t_disp_init_f)		(t_display*);

typedef enum				e_display_type
{
	CPU_DRIVER,
	MCPU_DRIVER,
	CUDA_DRIVER
}							t_display_type;

typedef enum				e_display_interface
{
	XMLX_DISPLAY,
	PNG_DISPLAY,
	XMLX_DIRECT_DISPLAY
}							t_display_interface;

typedef struct				s_display_init_param
{
	int						x;
	int						y;
	int						bx;
	int						by;
	t_display_type			type;
	t_display_interface		display_type;
	void					*user_ptr;
}							t_display_init_param;

struct						s_display
{
	t_display_init_fun		init;
	t_display_gen_fun		draw;
	t_display_init_fun		fini;
	t_keyhandle_fun			key_handler;
	t_mousehandle_fun		mouse_handler;
	t_mousehandle_fun		mouse_press_handler;
	int						mouse_state;
	int						type;
	t_driver				*renderer_driver;
	void					*user_ptr;
	void					*disp_param;
	void					*disp_internal;
	t_display_init_param	param;
};

t_display					*new_display(t_display_init_param tdip);
t_display					*register_display(t_display *d);
void						run_display(t_display *d);
void						end_application();
void						init_xmlx(t_display *d);
void						init_png(t_display *d);
void						init_xmlx_dir(t_display *d);

#endif
