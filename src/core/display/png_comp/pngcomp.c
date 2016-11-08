/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pngcomp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 13:49:00 by nbouteme          #+#    #+#             */
/*   Updated: 2016/11/08 14:43:37 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png_comp.h"

void		*deflate(void *data, int s, char l)
{
	void	*ret;
	char	*b;
	short	*u;

	ret = malloc(s + 1 + 4);
	b = ret;
	*b = l;
	u = (void*)(b + 1);
	u[0] = s;
	u[1] = 0xffff ^ s;
	ft_memcpy(&b[5], data, s);
	return (ret);
}

t_png_chunk	*png_ihdr(int w, int h, int *osize)
{
	char	data[4 + 4 + 5];
	int		*d;

	ft_memset(data, 0, sizeof(data));
	d = (void*)data;
	d[0] = bswap_32(w);
	d[1] = bswap_32(h);
	data[8] = 8;
	data[9] = 2;
	return (make_chunk("IHDR", data, sizeof(data), osize));
}

void		*png_stream(t_png_stream_p p)
{
	char	*ret;
	void	*chks[3];
	int		t[3];

	*p.osize = 0;
	chks[0] = png_ihdr(p.w, p.h, t);
	ret = zlib_stream(p.li, p.os, p.osize);
	chks[1] = make_chunk("IDAT", ret, *p.osize, t + 1);
	free(ret);
	chks[2] = make_chunk("IEND", "", 0, t + 2);
	*p.osize = 8 + t[0] + t[1] + t[2];
	ret = malloc(*p.osize);
	ft_memcpy(ret, "\x89PNG\r\n\x1a\n", 8);
	ft_memcpy(ret + 8, chks[0], t[0]);
	ft_memcpy(ret + 8 + t[0], chks[1], t[1]);
	ft_memcpy(ret + 8 + t[0] + t[1], chks[2], t[2]);
	free(chks[0]);
	free(chks[1]);
	free(chks[2]);
	return (ret);
}

void		*to_png(t_png_conv_p p)
{
	t_size_pair	**seg;
	char		*lines[3];
	int			os;

	os = 0;
	seg = make_arr(p.data, p.s, 3 * p.w);
	lines[0] = 0;
	lines[2] = (void*)seg;
	while (*seg)
	{
		lines[1] = lines[0];
		lines[0] = malloc(os + (*seg)->size + 1);
		ft_memcpy(lines[0], lines[1], os);
		free(lines[1]);
		lines[1] = &lines[0][os];
		*lines[1] = 0;
		ft_memcpy(lines[1] + 1, (*seg)->data, (*seg)->size);
		os += (*seg)->size + 1;
		free(*seg);
		++seg;
	}
	free(lines[2]);
	lines[2] = png_stream((t_png_stream_p){lines[0], p.w, p.h, os, p.osize});
	free(lines[0]);
	return (lines[2]);
}
