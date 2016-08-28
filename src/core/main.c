/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:10:35 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/13 04:01:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <core/core.h>
#include <unistd.h>

void usage()
{
	ft_putstr("Usage: ./rtv1 [scene file]");
	exit(1);
}

float angle;

int main(int argc, char **argv)
{
	t_iscene *scene;
	t_display *display;

	if (argc != 2)
		return (0);
	scene = load_iscene(argv[1]);
	if (!scene)
	{
		ft_putstr("Error detected, stopping...\n");
		return (1);
	}
	display = new_display((t_display_init_param)
						  {
							1280,
							720,
							CPU_DRIVER,
							scene
						});
	register_display(display);
	run_display(display);
	free(scene->spots);
	free(scene);
	return 0;
}
