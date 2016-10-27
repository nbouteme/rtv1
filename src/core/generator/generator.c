/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:22:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/28 00:09:42 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

t_generror		*gen_camera(t_iscene *ret, t_ast *sink, t_ast *r)
{
	t_ast	*pos;
	void	*e;

	if (ret->camset)
		return (new_gerror(sink->children[0], "Duplicate sink: ", "camera"));
	ret->camset = 1;
	pos = eval_ref(r, get_value(sink->children[2], "pos"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "camera: ", "pos"));
	if ((e = gen_vec3(ret->cam_pos, pos, r)))
		return (e);
	pos = eval_ref(r, get_value(sink->children[2], "dir"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "camera: ", "dir"));
	if ((e = gen_vec3(ret->cam_dir, pos, r)))
		return (e);
	pos = eval_ref(r, get_value(sink->children[2], "up"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "camera: ", "up"));
	if ((e = gen_vec3(ret->cam_up, pos, r)))
		return (e);
	if (fabs(a3_dot(ret->cam_up, ret->cam_dir)) >= 0.0001f)
		return (new_gerror(sink->children[2], "Up and Dir not possible", ""));
	return (0);
}

t_generror		*gen_spot(t_iscene *ret, t_ast *sink, t_ast *r)
{
	t_ast	*pos;
	void	*tmp;

	tmp = ret->spots;
	ret->spots = malloc(sizeof(t_spot) * (ret->n_spots + 1));
	ft_memcpy(ret->spots, tmp, sizeof(t_spot) * ret->n_spots);
	free(tmp);
	pos = eval_ref(r, get_value(sink->children[2], "pos"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "spot: ", "pos"));
	if ((tmp = gen_vec3(ret->spots[ret->n_spots].pos.v, pos, r)))
		return (tmp);
	ret->n_spots++;
	return (0);
}

t_generror		*gen_prim(t_iscene *ret, t_ast *sink, t_ast *r)
{
	t_ast	*pos;
	void	*tmp;

	tmp = ret->primitives;
	ret->primitives = ft_memalloc(sizeof(t_iprimitive) *
								(ret->n_primitives + 1));
	ft_memcpy(ret->primitives, tmp, sizeof(t_iprimitive) * ret->n_primitives);
	free(tmp);
	pos = eval_ref(r, get_value(sink->children[2], "type"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "primitive: ", "type"));
	if ((tmp = gen_type(&ret->primitives[ret->n_primitives].type, pos)))
		return (tmp);
	pos = eval_ref(r, get_value(sink->children[2], "material"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "prims: ", "material"));
	if ((tmp = gen_material(&ret->primitives[ret->n_primitives].mat, pos, r)))
		return (tmp);
	pos = eval_ref(r, get_value(sink->children[2], "transform"));
	if (!pos)
		return (new_gerror(sink->children[2], ATTR_MISS "prims: ", "transfor"));
	if ((tmp = gen_trans(&ret->primitives[ret->n_primitives].trans, pos, r)))
		return (tmp);
	ret->n_primitives++;
	return (0);
}

t_generror		*gen_sink(t_iscene *ret, t_ast *sink, t_ast *root)
{
	const char		*sinks[] = {"camera", "spots", "prims", 0};
	const t_sgen	sinkf[] = {&ukwn_sink, &gen_camera, &gen_spot, &gen_prim};

	if (!ft_strstr(sink->tag, "|sink"))
		return (new_gerror(sink, "Not a sink: ", sink->value));
	return (sinkf[str_arr_find(sinks, sink->children[0]->value) + 1](ret,
																	sink,
																	root));
}

t_iscene		*gen_iscene(t_ast *parsed, const char *input)
{
	t_iscene	*ret;
	t_generror	*e;
	int			i;

	if (parsed->n_children >= 10)
	{
		ft_putendl("Scene contains too many objects. (Limit: 8)");
		return (0);
	}
	ret = ft_memalloc(sizeof(*ret));
	i = 1;
	while (i < parsed->n_children - 1)
		if ((e = gen_sink(ret, parsed->children[i++], parsed)))
		{
			print_gerror(e, input);
			free(e->message);
			free(e->miss);
			free(ret->primitives);
			free(ret->spots);
			free(ret);
			return (0);
		}
	return (ret);
}
