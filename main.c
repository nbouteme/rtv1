/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:10:35 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 23:46:20 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include "ray.h"

void usage()
{
	ft_putstr("Usage: ./rtv1 [scene file]");
	exit(1);
}

int main(int argc, char **argv)
{
	t_scene *scene;
	t_display *display;

	if (argc != 2)
		usage();
	scene = load_scene(argv[1]);
	display = new_display(800, 600);
	display->key_handler = rt_handle_key;
	display->mouse_handler = rt_handle_mouse;
	display->user_ptr = scene;
	display->renderer_driver = get_driver(DRIVER_CPU);
	run_display(display);
    return 0;
}
