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

typedef t_driver *(*t_driver_gen_fun)();

t_driver *build_cpu_driver()
{
	t_driver *ret;

	ret = malloc(sizeof(*ret));

	ret->init = cpu_init;
	ret->genimage = cpu_genimage;
	ret->destroy = cpu_destroy;
	return (ret);
}

t_driver *build_mcpu_driver()
{
	t_driver *ret;

	ret = malloc(sizeof(*ret));

	ret->init = mcpu_init;
	ret->genimage = mcpu_genimage;
	ret->destroy = mcpu_destroy;
	return (ret);
}

t_driver *build_cuda_driver()
{
	return 0;
}

t_driver *get_driver(t_display_type type)
{
	const t_driver_gen_fun drivers[] = {
		build_cpu_driver,
		build_mcpu_driver,
		build_cuda_driver
	};
	return (drivers[type]());
}
