/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:25:05 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 23:28:50 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "driver.h"
#include "cpu_driver.h"

typedef t_driver *(*t_driver_gen_fun)();

t_driver *build_cpu_driver()
{
	t_driver *ret;

	ret = malloc(sizeof(*ret));

	ret->init = cpu_init;
	ret->genimage = cpu_genimage;
	ret->destroy = cpu_destroy;
}

t_driver *build_cuda_driver()
{
	return 0;
}

t_driver *get_driver(int type)
{
	const t_driver_gen_fun drivers[] = {
		build_cpu_driver,
		build_cuda_driver
	};
	return (drivers[type]());
}
