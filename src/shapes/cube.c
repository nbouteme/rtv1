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
	self = (void*)base;
	(void)out;
/*	t_vec3 tmin;
	t_vec3 tmax;


	float t[10];

	t[7] = maxf(maxf(minf(tmin.v[0], tmin.v[1]), minf(tmin.v[2], tmax.v[0])), minf(tmax.v[1], tmax.v[2]));
	t[8] = minf(minf(maxf(tmin.v[0], tmin.v[1]), maxf(tmin.v[2], tmax.v[0])), maxf(tmax.v[1], tmax.v[2]));
	if(t[8] < 0 || t[7] > t[8])
		return false;
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, t[7]));
	out->normal = out->point;
	vec3_normalize(&out->normal);
	return true;*/


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

	tmin = vec3_div(vec3_sub(vec3_null(), ray->pos), ray->dir);
	tmax = vec3_div(vec3_sub(self->dims, ray->pos), ray->dir);

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

t_primitive *new_cube(t_cube *ret, t_vec3 dims, t_vec3 pos, t_vec3 color)
{
	new_primitive(&ret->base, mat4_translate(pos), color);
	ret->base.intersect = cube_ray_intersect;
	ret->dims.s = dims.s;
	return ((t_primitive*)ret);
}
