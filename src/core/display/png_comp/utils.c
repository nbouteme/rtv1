/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:00:45 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/27 23:54:29 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png_comp.h"

unsigned	bswap_32(unsigned n)
{
	return (((n >> 24) & 0x000000FFu) |
			((n >> 8) & 0x0000FF00u) |
			((n << 8) & 0x00FF0000u) |
			((n << 24) & 0xFF000000u));
}

unsigned	adler32(unsigned char *data, size_t len)
{
	unsigned a;
	unsigned b;
	unsigned index;

	index = 0;
	a = 1;
	b = 0;
	while (index < len)
	{
		a = (a + data[index]) % 65521;
		b = (b + a) % 65521;
		++index;
	}
	return ((b << 16) | a);
}

unsigned	crc32(unsigned char *buf, int len)
{
	unsigned	c;
	int			i;
	int			k;
	unsigned	v;

	c = ~0;
	i = 0;
	v = 0;
	while (i < len)
	{
		c ^= buf[i];
		k = 0;
		while (k++ < 8)
		{
			v = (c & 1) ? 0xedb88320 : 0;
			c = v ^ (c >> 1);
		}
		++i;
	}
	return (c ^ ~0);
}

t_size_pair	**make_arr(unsigned char *data, int s, int c)
{
	t_size_pair	**ret;
	int			i;

	ret = ft_memalloc(sizeof(t_size_pair*) * ((s / c) + 2));
	i = 0;
	while (s > 0)
	{
		ret[i] = malloc(sizeof(t_size_pair) + (s >= c ? c : s));
		ret[i]->size = (s >= c ? c : s);
		ft_memcpy(ret[i]->data, data, (s >= c ? c : s));
		data += (s >= c ? c : s);
		s -= (s >= c ? c : s);
		++i;
	}
	return (ret);
}

t_png_chunk	*make_chunk(char type[4], void *data, int size, int *osize)
{
	t_png_chunk	*ret;
	unsigned	*crcp;

	*osize = sizeof(t_png_chunk) + size + 4;
	ret = malloc(*osize);
	ret->length = bswap_32(size);
	ft_memcpy(ret->magic, type, 4);
	ft_memcpy(ret->data, data, size);
	crcp = (void*)&((char*)ret->data)[size];
	*crcp = bswap_32(crc32((void*)&ret->magic, size + 4));
	return (ret);
}
