/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:10:35 by nbouteme          #+#    #+#             */
/*   Updated: 2016/11/08 16:01:53 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <core/core.h>
#include <unistd.h>

void	usage(void)
{
	ft_putstr("Usage: ./rtv1 [scene file] (-{c|g|m}) (-{p|x|d})\n");
	ft_putstr("c: CPU renderer (Default)\ng: GPU renderer (CUDA)\nm: "
			"Multi-threaded CPU renderer\n");
	ft_putstr("-x: Display in a window (Default)\n");
	ft_putstr("-d: Display in a cuda window (required for gpu renderer)\n");
	ft_putstr("-p: Write PNG file to stdout\n");
	exit(1);
}

#define S(x) [x]

void	handle_single_arg(char *arg, t_args *ret, const char *vals)
{
	ret->errored |= arg[1] == 0;
	if (ret->errored)
		return ;
	if (*arg == '-')
	{
		if (arg[2] || !ft_strchr("cdgpmx", arg[1]))
			ret->errored = 1;
		if (arg[1] == 'c' || arg[1] == 'g' || arg[1] == 'm')
			ret->driver = vals[(unsigned)arg[1]];
		if (arg[1] == 'd' || arg[1] == 'p' || arg[1] == 'x')
			ret->display = vals[(unsigned)arg[1]];
	}
	else
		ret->filename = arg;
}

t_args	load_args(int ac, char **av)
{
	const char	valuess[256] = {S('c') = CPU_DRIVER,
								S('g') = CUDA_DRIVER,
								S('m') = MCPU_DRIVER,
								S('d') = XMLX_DIRECT_DISPLAY,
								S('p') = PNG_DISPLAY,
								S('x') = XMLX_DISPLAY};
	t_args		ret;

	ft_memset(&ret, ac * 0, sizeof(ret));
	ret.driver = CPU_DRIVER;
	ret.display = XMLX_DISPLAY;
	while (*++av)
		handle_single_arg(av[0], &ret, valuess);
	ret.errored |= ret.display == -1 || ret.driver == -1 || !ret.filename;
	return (ret);
}

#undef S

int		main(int argc, char **argv)
{
	t_iscene	*scene;
	t_display	*display;
	t_args		args;

	args = load_args(argc, argv);
	if (args.errored || !(scene = load_iscene(args.filename)))
	{
		ft_putstr("Error detected, stopping...\n");
		usage();
		return (1);
	}
	display = new_display((t_display_init_param)
						{1280, 720, 0, 0, args.driver, args.display, scene});
	if (display)
	{
		register_display(display);
		run_display(display);
	}
	free(scene->spots);
	free(scene->primitives);
	free(scene);
	return (0);
}
