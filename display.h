/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:32:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/20 00:07:33 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		DISPLAY_H
# define	DISPLAY_H

typedef struct	s_mlx
{
	void *mlx;
	void *win;
}				t_mlx;

typedef struct	s_display
{
	t_keyhandle_fun		key_handler;
	t_mousehandle_fun	mouse_handler;
	const t_driver		*renderer_driver;
	void				*user_ptr;
	t_mlx				ctx;
}				t_display;

t_display *new_display(int x, int y);
void run_display(t_display *d);

#endif
