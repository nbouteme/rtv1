/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:22:19 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 11:10:19 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <libft/std.h>
# include <libft/parser.h>
# include <stdbool.h>
# include <stdlib.h>
# include <core/math_types.h>
# include <core/display.h>
# include <core/iscene.h>
# include <core/spot.h>
# include <core/ray.h>
# include <core/driver_interface.h>
# include <core/generator.h>
# include <core/utils.h>

typedef struct	s_args
{
	const char	*filename;
	int			driver;
	int			display;
	int			errored;
}				t_args;

t_args			load_args(int ac, char **av);
#endif
