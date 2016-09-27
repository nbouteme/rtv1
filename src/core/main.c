/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:10:35 by nbouteme          #+#    #+#             */
/*   Updated: 2016/09/19 03:30:44 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <core/core.h>
#include <unistd.h>

void usage()
{
	ft_putstr("Usage: ./rtv1 [scene file] (-{c|g|m}) (-{p|x|d})\n");
	ft_putstr("c: CPU renderer (Default)\ng: GPU renderer (CUDA)\nm: Multi-threaded "
			  "CPU renderer\n");
	ft_putstr("-x: Display in a window (Default)\n");
	ft_putstr("-p: Write PNG file to stdout\n");
	exit(1);
}

t_args load_args(int ac, char **av)
{
	const char drivers[256] = {['c'] = CPU_DRIVER, ['g'] = CUDA_DRIVER,
							['m'] = MCPU_DRIVER};
	const char display[256] = {['d'] = XMLX_DIRECT_DISPLAY, ['p'] = PNG_DISPLAY,
							['x'] = XMLX_DISPLAY};
	t_args ret;

	ft_memset(&ret, ac * 0, sizeof(ret));
	ret.driver = CPU_DRIVER;
	ret.display = XMLX_DISPLAY;
	while (*++av)
	{
		if (*av[0] == '-')
		{
			if (av[0][2] || !ft_strchr("cdgpmx", av[0][1]))
				ret.errored = 1;
			if (av[0][1] == 'c' || av[0][1] == 'g' || av[0][1] == 'm')
				ret.driver = drivers[(unsigned)av[0][1]];
			if (av[0][1] == 'd' || av[0][1] == 'p' || av[0][1] == 'x')
				ret.display = display[(unsigned)av[0][1]];
		}
		else
			ret.filename = *av;
	}
	ret.errored |= ret.display == -1 || ret.driver == -1 || !ret.filename;
	return ret;
}

int main(int argc, char **argv)
{
	t_iscene *scene;
	t_display *display;

	if (argc <= 1)
		return (0);
	t_args args = load_args(argc, argv);
	if (args.errored || !(scene = load_iscene(args.filename)))
	{
		ft_putstr("Error detected, stopping...\n");
		usage();
		return (1);
	}
	display = new_display((t_display_init_param)
						{
							1280, 720, 0, 0,
							args.driver,
							args.display,
							scene
						});
	if (display)
	{
		register_display(display);
		run_display(display);
	}
	free(scene->spots);
	free(scene->primitives);
	free(scene);
	return 0;
}
