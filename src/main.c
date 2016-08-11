/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:10:35 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/09 02:17:31 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include "ray.h"
#include "scene.h"
#include "display.h"

void usage()
{
	ft_putstr("Usage: ./rtv1 [scene file]");
	exit(1);
}
float angle;
int main(int argc, char **argv)
{
	t_scene *scene;
	t_display *display;

	if (argc != 2)
		usage();
	angle = atof(argv[1]);
	scene = load_scene(argv[1]);
	display = new_display((t_display_init_param)
						{
							1280,
							720,
							CPU_DRIVER,
							scene
						});
	register_display(display);
	run_display(display);
    return 0;
}
