/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_comp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 13:40:50 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:17:32 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_COMP_H
# define PNG_COMP_H

# include <unistd.h>
# include <stdio.h>
# include <sys/fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <libft/std.h>

typedef struct
{
	unsigned		length;
	char			magic[4];
	char			data[];
}					t_png_chunk;

typedef struct
{
	int				size;
	unsigned char	data[];
}					t_size_pair;

typedef struct
{
	int				w;
	int				h;
	void			*data;
	int				s;
	int				*osize;
}					t_png_conv_p;

typedef struct		s_png_stream_p
{
	char	*li;
	int		w;
	int		h;
	int		os;
	int		*osize;
}					t_png_stream_p;

unsigned			bswap_32(unsigned n);
unsigned			adler32(unsigned char *data, size_t len);
unsigned			crc32(unsigned char *buf, int len);
t_size_pair			**make_arr(unsigned char *data, int s, int c);
t_png_chunk			*make_chunk(char type[4], void *data, int size, int *osize);
void				process_segment(t_size_pair **seg, char *kek[3], int *os);
void				*zlib_stream(void *data, int s, int *osize);
void				*deflate(void *data, int s, char l);
t_png_chunk			*png_ihdr(int w, int h, int *osize);
void				*png_stream(t_png_stream_p p);
void				*to_png(t_png_conv_p p);

#endif
