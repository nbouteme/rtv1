/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:28:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:46:28 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CPU_DRIVER_H
# define	CPU_DRIVER_H

#include "driver.h"

void cpu_init(t_driver *self);
void cpu_genimage(t_driver *self, t_display *disp);
void cpu_destroy(t_driver *self);

typedef struct	s_cpudri_data
{
	void *mlx_ptr;
	void *win_ptr;
}				t_cpudri_data;

#endif
