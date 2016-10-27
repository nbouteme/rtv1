/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_gens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:54:29 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/27 23:52:08 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

t_generror		*gen_scalar(float *a, t_ast *elem)
{
	int n;

	if (!ft_strstr(elem->tag, "|int") && !ft_strstr(elem->tag, "|float"))
		return (new_gerror(elem, "Expected scalable type, got: ", elem->tag));
	if (ft_strstr(elem->tag, "|int"))
		*a = ft_atoi(elem->value);
	else
	{
		n = elem->children[0]->value[0] == '-';
		*a = ft_atoi(elem->children[0]->value + n);
		*a += ((float)ft_atoi(elem->children[2]->value)) /
			pow(10, ft_strlen(elem->children[2]->value));
		*a = n ? -*a : *a;
	}
	if (*a <= -10000.0f || *a >= 10000.0f)
		return (new_gerror(elem, "Value out of range: ", elem->tag));
	return (0);
}

t_generror		*gen_vec3(float *a, t_ast *elem, t_ast *root)
{
	int		i;
	t_ast	*e;
	void	*tmp;

	if (!ft_strstr(elem->tag, "|array"))
		return (new_gerror(elem, "Expected type array, got: ", elem->tag));
	if (elem->n_children != 7)
		return (new_gerror(elem, "Wrong number of elements: ", "3 needed"));
	i = 1;
	while (i < elem->n_children)
	{
		e = eval_ref(root, elem->children[i]);
		if ((tmp = gen_scalar(&a[(i - 1) / 2], e)))
			return (tmp);
		i += 2;
	}
	return (0);
}

t_generror		*gen_type(t_prim_type *ret, t_ast *elem)
{
	const char	*types[] = {"plane", "sphere", "cone", "cylinder", 0};
	int			i;

	if (!ft_strstr(elem->tag, "|string"))
		return (new_gerror(elem, "Expected string type, got: ", elem->tag));
	i = str_arr_find(types, elem->value);
	if (i == -1)
		return (new_gerror(elem, "Unknown primitive type: ", elem->value));
	*ret = i;
	return (0);
}

t_generror		*gen_material(t_imaterial *ret, t_ast *ass, t_ast *r)
{
	t_ast	*pos;
	void	*e;

	pos = eval_ref(r, get_value(ass, "diffuse"));
	if (!pos)
		return (new_gerror(ass, ATTR_MISS "material: ", "diffuse"));
	if ((e = gen_vec3(ret->diffuse, pos, r)))
		return (e);
	ret->spec_intensity = 999999.9f;
	pos = eval_ref(r, get_value(ass, "ambiant"));
	if (pos && (e = gen_vec3(ret->ambiant, pos, r)))
		return (e);
	pos = eval_ref(r, get_value(ass, "spec"));
	if (pos && (e = gen_scalar(&ret->spec_intensity, pos)))
		return (e);
	return (0);
}

t_generror		*gen_trans(t_itrans *ret, t_ast *ass, t_ast *r)
{
	t_ast	*pos;
	void	*e;

	pos = eval_ref(r, get_value(ass, "position"));
	if (!pos)
		return (new_gerror(ass, ATTR_MISS "transform: ", "position"));
	if ((e = gen_vec3(ret->pos.v, pos, r)))
		return (e);
	ft_memcpy(ret->rot_axis.v, (float[]){1.0, 0.0, 0.0}, sizeof(ret->rot_axis));
	ft_memcpy(ret->scale.v, (float[]){1.0, 1.0, 1.0}, sizeof(ret->scale));
	ret->rot_angle = 0.0f;
	pos = eval_ref(r, get_value(ass, "rot_axis"));
	if (pos && (e = gen_vec3(ret->rot_axis.v, pos, r)))
		return (e);
	pos = eval_ref(r, get_value(ass, "rot_angle"));
	if (pos && (e = gen_scalar(&ret->rot_angle, pos)))
		return (e);
	pos = eval_ref(r, get_value(ass, "scale"));
	if (pos && (e = gen_vec3(ret->scale.v, pos, r)))
		return (e);
	return (0);
}
