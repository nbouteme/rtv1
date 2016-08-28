#include <cpu/math.h>
#include <cpu/shapes.h>

/*
static inline float minf(float a, float b)
{
	return (a < b ? a : b);
}

static inline float maxf(float a, float b)
{
	return (a > b ? a : b);
}
*/
static inline void fsw(float *a, float *b)
{
	float c;

	c = *a;
	*a = *b;
	*b = c;
}

bool cube_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	t_vec3 tmin;
	t_vec3 tmax;

	t_cube *self;
	(void) self;
	self = (void*)base;
	(void)out;
	if (ray->dir.v[0] == ray->dir.v[1] && ray->dir.v[1] == 0)
	{
		float a, b;
		fsw(&a, &b);
	}
	if (ray->dir.v[0] == ray->dir.v[1] && ray->dir.v[1] != 0)
	{
		float a, b;
		fsw(&a, &b);
	}
	tmin = vec3_div(vec3_sub((t_3dvec){-0.5f, -0.5f, -0.5f }, ray->pos), ray->dir);
	tmax = vec3_div(vec3_sub((t_3dvec){0.5f, 0.5f, 0.5f }, ray->pos), ray->dir);
    if (tmin.v[0] > tmax.v[0]) fsw(&tmin.v[0], &tmax.v[0]);
    if (tmin.v[1] > tmax.v[1]) fsw(&tmin.v[1], &tmax.v[1]);
    if ((tmin.v[0] > tmax.v[1]) || (tmin.v[1] > tmax.v[0]))
        return false;
    if (tmin.v[1] > tmin.v[0])
        tmin.v[0] = tmin.v[1];
    if (tmax.v[1] < tmax.v[0])
        tmax.v[0] = tmax.v[1];
    if (tmin.v[2] > tmax.v[2]) fsw(&tmin.v[2], &tmax.v[2]);
    if ((tmin.v[0] > tmax.v[2]) || (tmin.v[2] > tmax.v[0]))
        return false;
    if (tmin.v[2] > tmin.v[0])
        tmin.v[0] = tmin.v[2];
    if (tmax.v[2] < tmax.v[0])
        tmax.v[0] = tmax.v[2];
    return true;
}
