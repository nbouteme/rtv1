/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:55:04 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/30 01:23:06 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/core.h>
#include "lang.h"

t_iscene	*load_iscene(const char *fn)
{
	unsigned long	size;
	void			*buf[4];
	t_langparser	*l;
	t_parser		*p;

	buf[0] = from_file(fn, &size, scene_file_check);
	buf[1] = from_file("lang", &size, scene_file_check);
	l = lang_parser(buf[1]);
	p = l ? get_parser(l, "file") : 0;
	ft_memset(buf + 2, 0, sizeof(void*) * 2);
	if (l && buf[0] && run_parser(p, buf[0], &buf[2]))
	{
		buf[3] = gen_iscene(buf[2], buf[0]);
		delete_ast(buf[2]);
	}
	else if (buf[2])
	{
		ft_putstr(((t_error*)buf[2])->expected);
		print_error(buf[2], buf[0]);
		free(buf[2]);
	}
	delete_langparser(l);
	free(buf[0]);
	return (buf[3]);
}

int			scene_file_check(char *buf, int s, unsigned long tsize)
{
	(void)buf;
	(void)s;
	if (tsize > 4096)
	{
		ft_putendl_fd("File too big.", 2);
		return (0);
	}
	return (1);
}
