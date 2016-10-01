/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:05:18 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:23:49 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include <stdio.h>
# include <unistd.h>
# include <cpu/cpu.h>
# include <cpu/cpu_driver.h>
# include <cpu/raytracer.h>

int		inter(t_ray *from, t_scene *scene, t_hit_info *hit, t_inter_info *out);
t_vec3	color_from_material(t_colargs *args);
t_vec3	color_from_ray(t_scene *s, t_ray *from);
void	bake_camray(t_camera *c);
t_ray	gen_ray(t_vec3 from, t_vec3 to);
t_ray	gen_camray(int x, int y, t_camera *c);
float	conv(float c);
void	correct_gamma(t_vec3 *framebuffer);
void	draw_scene(t_vec3 *surface, t_scene *scene);
int		cpu_genimage(t_display *disp);

#endif
