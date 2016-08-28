#ifndef CORE_H
# define CORE_H

# include <libft/std.h>
# include <stdbool.h>
# include <stdlib.h>

typedef enum
{
	CPU_DRIVER,
	CUDA_DRIVER
}				t_display_type;

# include <core/math_types.h>
# include <core/display.h>
# include <core/iscene.h>
# include <core/spot.h>
# include <core/ray.h>
# include <core/driver_interface.h>
# include <core/lexer.h>
# include <core/parser.h>
# include <core/generator.h>
# include <core/utils.h>

#endif
