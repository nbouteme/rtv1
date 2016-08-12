#ifndef MATH_H
# define MATH_H

# include <math.h>
# include <libft/std.h>
# include <core/math_types.h>

# ifdef VEC3_H
#  undef VEC3_H
# endif
# include <cpu/math/vec3.h>

# ifdef VEC4_H
#  undef VEC4_H
# endif
# include <cpu/math/vec4.h>

# ifdef MAT3_H
#  undef MAT3_H
# endif
# include <cpu/math/mat3.h>

# ifdef MAT4_H
#  undef MAT4_H
# endif
# include <cpu/math/mat4.h>

# include <cpu/math/equation.h>

#endif
