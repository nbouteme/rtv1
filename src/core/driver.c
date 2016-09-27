/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:25:05 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/22 00:06:25 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/driver_interface.h>
#include <cpu/cpu_driver_functions.h>
#include <mcpu/mcpu_driver_functions.h>
#include <cuda/cuda_driver_functions.h>

#ifndef GPU
# define CUDA_INIT (void*)not_implemented
# define CUDA_GENIMAGE (void*)not_implemented
# define CUDA_FINI (void*)not_implemented
#else
# define CUDA_INIT cuda_init
# define CUDA_GENIMAGE cuda_genimage
# define CUDA_FINI cuda_fini
#endif

#ifndef MCPU
# define MCPU_GENIMAGE (void*)not_implemented
#else
# ifndef SRC_CPU
#  error "This module depends on the CPU module"
# endif
# define MCPU_GENIMAGE mcpu_genimage
#endif

typedef t_driver *(*t_driver_gen_fun)(int);

int not_implemented(void)
{
	ft_putendl("This feature isn't implemented in this build");
	return 1;
}

t_driver *build_cpu_driver(int type)
{
	t_driver *ret;

	if (type == XMLX_DIRECT_DISPLAY)
		return (0);
	ret = malloc(sizeof(*ret));
	ret->init = 0;
	ret->genimage = cpu_genimage;
	ret->destroy = 0;
	return (ret);
}

t_driver *build_mcpu_driver(int type)
{
	t_driver *ret;

	if (type == XMLX_DIRECT_DISPLAY)
		return (0);
	ret = malloc(sizeof(*ret));
	ret->init = 0;
	ret->genimage = MCPU_GENIMAGE;
	ret->destroy = 0;
	return (ret);
}

t_driver *build_cuda_driver(int type)
{
	t_driver *ret;

	if (type != XMLX_DIRECT_DISPLAY)
		return (0);
	ret = malloc(sizeof(*ret));
	ret->init = CUDA_INIT;
	ret->genimage = CUDA_GENIMAGE;
	ret->destroy = CUDA_FINI;
	return (ret);
}

t_driver *get_driver(t_display_type type, t_display_interface i)
{
	const t_driver_gen_fun drivers[] = {
		build_cpu_driver,
		build_mcpu_driver,
		build_cuda_driver
	};
	return (drivers[type](i));
}
