/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:52:00 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 12:28:36 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include <core/core.h>
# include <math.h>

# define ATTR_MISS "Couldn't find attribute in "

typedef struct	s_generror
{
	t_ast	*frag_w;
	char	*message;
	char	*miss;
}				t_generror;

typedef t_generror*(*t_sgen)(t_iscene *, t_ast *, t_ast *);
t_generror		*gen_camera(t_iscene *ret, t_ast *sink, t_ast *r);
t_generror		*gen_spot(t_iscene *ret, t_ast *sink, t_ast *r);
t_generror		*gen_prim(t_iscene *ret, t_ast *sink, t_ast *r);
t_generror		*gen_sink(t_iscene *ret, t_ast *sink, t_ast *root);
t_iscene		*gen_iscene(t_ast *parsed, const char *input);
t_ast			*get_value(t_ast *assarr, const char *name);
t_ast			*find_aa_with_name(t_ast *root, const char *name);
t_ast			*eval_ref(t_ast *root, t_ast *elem);
t_generror		*new_gerror(t_ast *wfrag, const char *m, const char *mi);
t_generror		*ukwn_sink(t_iscene *ret, t_ast *sink, t_ast *r);
void			print_gerror(t_generror *e, const char *i);
int				str_arr_find(const char **a, const char *s);
float			a3_dot(float a[3], float b[3]);
t_generror		*gen_scalar(float *a, t_ast *elem);
t_generror		*gen_vec3(float *a, t_ast *elem, t_ast *root);
t_generror		*gen_type(t_prim_type *ret, t_ast *elem);
t_generror		*gen_material(t_imaterial *ret, t_ast *ass, t_ast *r);
t_generror		*gen_trans(t_itrans *ret, t_ast *ass, t_ast *r);

#endif
