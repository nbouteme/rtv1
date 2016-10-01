/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zlib.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 13:54:08 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:14:56 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png_comp.h"

void		process_segment(t_size_pair **seg, char *kek[3], int *os)
{
	kek[1] = kek[0];
	kek[0] = malloc(*os + (*seg)->size + 5);
	ft_memcpy(kek[0], kek[1], *os);
	free(kek[1]);
	kek[1] = deflate((*seg)->data, (*seg)->size, !seg[1]);
	ft_memcpy(&((char*)kek[0])[*os], kek[1], (*seg)->size + 5);
	free(kek[1]);
	*os += (*seg)->size + 5;
	free(*seg);
}

void		*zlib_stream(void *data, int s, int *osize)
{
	t_size_pair	**seg;
	char		*kek[3];
	int			os;

	os = 0;
	seg = make_arr(data, s, 0xffff);
	memset(kek, 0, sizeof(kek));
	kek[2] = (void*)seg;
	while (*seg)
	{
		process_segment(seg, kek, &os);
		++seg;
	}
	free(kek[2]);
	*osize = 2 + os + 4;
	kek[2] = malloc(*osize);
	memcpy(kek[2], "\x78\x01", 2);
	memcpy(&kek[2][2], kek[0], os);
	free(kek[0]);
	*(unsigned*)&kek[2][2 + os] = bswap_32(adler32(data, s));
	return (kek[2]);
}
