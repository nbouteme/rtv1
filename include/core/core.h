#ifndef CORE_H
# define CORE_H

# include <libft/std.h>
# include <libft/parser.h>
# include <stdbool.h>
# include <stdlib.h>

typedef enum
{
	CPU_DRIVER,
	MCPU_DRIVER,
	CUDA_DRIVER
}				t_display_type;

typedef enum
{
	XMLX_DISPLAY,
	PNG_DISPLAY,
	XMLX_DIRECT_DISPLAY
}				t_display_interface;

# include <core/math_types.h>
# include <core/display.h>
# include <core/iscene.h>
# include <core/spot.h>
# include <core/ray.h>
# include <core/driver_interface.h>
# include <core/lexer.h>
# include <core/generator.h>
# include <core/utils.h>

typedef struct	s_args
{
	const char *filename;
	int driver;
	int display;
	int errored;
}				t_args;

t_args load_args(int ac, char **av);
#endif
