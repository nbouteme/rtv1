/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:53:58 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 11:54:06 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

t_ast			*get_value(t_ast *assarr, const char *name)
{
	int i;

	i = 1;
	while (i < assarr->n_children)
	{
		if (ft_strcmp(name, assarr->children[i]->children[0]->value) == 0)
			return (assarr->children[i]->children[2]);
		i += 2;
	}
	return (0);
}

t_ast			*find_aa_with_name(t_ast *root, const char *name)
{
	t_ast	*ret;
	int		i;

	i = 0;
	if (!root)
		return (0);
	if (strstr(root->tag, "|assoc_array") && (ret = get_value(root, "name"))
	&& ft_strstr(ret->tag, "|string") && ft_strcmp(name, ret->value) == 0)
		return (ret);
	while (i < root->n_children)
		if ((ret = find_aa_with_name(root->children[i], name)))
			return (ret);
		else
			++i;
	return (0);
}

t_ast			*eval_ref(t_ast *root, t_ast *elem)
{
	char	*name;
	t_ast	*arr;

	if (!elem || !elem->n_children
		|| !ft_strstr(elem->children[0]->tag, "|ref"))
		return (elem);
	name = elem->children[0]->value;
	arr = find_aa_with_name(root, name);
	return (get_value(arr, elem->children[2]->value));
}
