/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:59:08 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 11:59:35 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/core.h>
#include <unistd.h>
#include <sys/fcntl.h>

void	*from_file(const char *fn, unsigned long *size, t_check_fun chk)
{
	int		fd;
	char	*buff;
	int		r;

	fd = open(fn, O_RDONLY);
	if (fd < 0)
		return (0);
	*size = 0;
	buff = ft_memalloc(512);
	while (1)
	{
		r = read(fd, buff + *size, 512);
		*size += r;
		if (!chk(buff + *size, r))
		{
			free(buff);
			return (0);
		}
		if (r != 512)
			break ;
		buff = realloc(buff, *size + 512);
		ft_memset(buff + *size, 0, 512);
	}
	return (buff);
}
