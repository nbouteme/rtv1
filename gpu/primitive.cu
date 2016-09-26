#include "ctypes.hu"

__host__
float deg2rad(float deg)
{
	const float tran = 180.0f / M_PI;

	return deg / tran;
}

__host__
t_primitive *new_primitive(t_primitive *alloc, t_iprimitive *base)
{
	t_cvec3 rot_axis = t_cvec3(base->trans.rot_axis).normalize();
	alloc->transform = translate(base->trans.pos);
	alloc->transform = alloc->transform * rotate(rot_axis, deg2rad(base->trans.rot_angle));
	//* t_cmat4(1);
	alloc->itransform = alloc->transform.inverse();
	alloc->norm = alloc->itransform.topleft().transpose();
	alloc->inorm = alloc->transform.topleft().transpose();
	alloc->diffuse = t_cvec3(base->mat.diffuse);
	alloc->ambiant = t_cvec3(base->mat.ambiant);
	alloc->spec = base->mat.spec_intensity;
	return (alloc);
}
