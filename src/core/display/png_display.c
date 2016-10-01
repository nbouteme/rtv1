/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:13:56 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:42:43 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/core.h>
#include <unistd.h>
#include "png_display.h"

void	init_png_res(t_display *d)
{
	d->disp_internal = 0;
	d->disp_param = ft_memalloc(sizeof(float) * 3 * 1280 * 720);
	if (d->renderer_driver->init)
		d->renderer_driver->init(d);
}

int		gen_png(t_display *d)
{
	int		size;
	void	*image;
	int		i;
	char	*pixbuf;

	d->renderer_driver->genimage(d);
	size = 3 * 1280 * 720;
	pixbuf = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		float f = ((float*)d->disp_param)[i] >= 1.0f ? 1.0f : ((float*)d->disp_param)[i];
		pixbuf[i] = f * 255.0f;
		++i;
	}
//	image = to_png((t_png_conv_p){1280, 720, pixbuf, size, &size});
	image = pixbuf;
	write(1, image, size);
	close(1);
	return (false);
}

void	init_png(t_display *d)
{
	d->init = init_png_res;
	d->draw = gen_png;
	d->fini = 0;
}
