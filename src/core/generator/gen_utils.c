/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:53:03 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 11:53:43 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

t_generror		*new_gerror(t_ast *wfrag, const char *m, const char *mi)
{
	t_generror *ret;

	ret = malloc(sizeof(*ret));
	ret->frag_w = wfrag;
	ret->message = ft_strdup(m);
	ret->miss = ft_strdup(mi);
	return (ret);
}

t_generror		*ukwn_sink(t_iscene *ret, t_ast *sink, t_ast *r)
{
	(void)ret;
	(void)r;
	return (new_gerror(sink->children[0], "Unknown sink name: ",
					sink->children[0]->value));
}

void			print_gerror(t_generror *e, const char *i)
{
	t_error f;

	f.loc = e->frag_w->loc;
	ft_putstr("Error: `");
	ft_putstr(e->message);
	ft_putstr(e->miss);
	ft_putstr("` near ");
	ft_putnbr(f.loc.line);
	ft_putstr(":");
	ft_putnbr(f.loc.col);
	ft_putendl("");
	print_error(&f, i);
}

int				str_arr_find(const char **a, const char *s)
{
	int i;

	i = 0;
	while (a[i])
		if (ft_strcmp(a[i], s) == 0)
			return (i);
		else
			++i;
	return (-1);
}

float			a3_dot(float a[3], float b[3])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}
