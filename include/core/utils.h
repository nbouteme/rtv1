/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:46:56 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:46:58 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef int	(*t_check_fun)(char *s, int size, unsigned long tsize);
void		*from_file(const char *fn, unsigned long *size, t_check_fun check);

#endif
