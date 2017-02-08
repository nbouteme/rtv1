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
	alloc->itransform = alloc->transform.inverse();
	alloc->norm = alloc->itransform.topleft().transpose();
	alloc->inorm = alloc->transform.topleft().transpose();
	alloc->mat.ambiant = base->mat.ambiant;
	alloc->mat.diffuse = base->mat.diffuse;
	alloc->mat.spec_intensity = base->mat.spec_intensity;
	alloc->mat.reflectivity = base->mat.reflectivity;
	alloc->mat.transluscence = base->mat.transluscence;
	return (alloc);
}
