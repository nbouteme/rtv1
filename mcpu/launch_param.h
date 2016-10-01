/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_param.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:04:02 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 11:04:32 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCH_PARAM_H
# define LAUNCH_PARAM_H

typedef struct	s_launch_param
{
	t_display	*d;
	t_scene		*s;
	int			n;
}				t_launch_param;

#endif
