#include <core/core.h>

typedef struct	s_gen_params
{
	int *errored;
	t_iscene *scene;
	t_scene_parser *parsed;
}				t_gen_params;

typedef int (*t_genfun)(t_object *in, void *out);

typedef struct	s_genfun_params
{
	t_gen_params *g_params;
	t_genfun fun;
	int ign;
}				t_genfun_params;

typedef void (*t_sink_gen)(t_sink *, t_gen_params *);

void calc_size(t_dlist *elem, int *s)
{
	(void)elem;
	s[0]++;
}

int gen_float(t_scalar *str, float *out)
{
	if (str->base.type != SCALAR)
	{
		ft_putendl("Expected scalar");
		return 1;
	}
	*out = str->value;
	return 0;
}

int arr_index_of(const char **arr, const char *v)
{
	int i;
	i = 0;
	while (arr[i])
		if (ft_strcmp(arr[i], v) == 0)
			return (i);
		else
			++i;
	return (-1);
}

int find_key(t_dlist *elem, const char *k)
{
	t_pair *pair;

	pair = elem->content;
	return (ft_strcmp(pair->key, k) == 0);
}

void gen_value(t_assarray *arr, char *k, void *out, t_genfun_params *in)
{
	t_dlist *elem;
	t_gen_params *params;

	params = in->g_params;
	if (*params->errored)
		return ;
	elem = ftext_lstfind(arr->pairs, (void*)find_key, k);
	arr = elem ? (void*)((t_pair*)elem->content)->value : 0;
	if (arr)
	{
		while (arr->base.type == REF)
			arr = (void*)((t_reference*)arr)->lazy_reference;
		if (!(*params->errored |= in->fun(&arr->base, out)))
			return ;
		highlight_line(params->parsed, arr->base.ref->line, arr->base.ref->col);
	}
	else if (!in->ign)
	{
		ft_putstr("Missing property `");
		ft_putstr(k);
		ft_putendl("` in a certain sink.");
		*params->errored |= 1;
	}
}

int gen_vec3(t_array *arr, float *out)
{
	int i;
	int size;

	size = 0;
	ftext_lstiterup(arr->values, (void*)calc_size, &size);
	if (size != 3)
	{
		ft_putstr("Expected array of 3 elements:\n");
		return 1;
	}
	i = 0;
	t_dlist *it;
	it = arr->values->next;
	while (i < 3)
	{
		if (gen_float(it->content, &out[i++]))
			return 1;
		it = it->next;
	}
	return 0;
}

void gen_err(t_sink *sink, t_gen_params *params)
{
	(void)sink;
	ft_putstr("Unknown sink `");
	ft_putstr(sink->name);
	ft_putstr("`.\n");
	*params->errored |= 1;
}

int gen_type(t_string *str, int *type)
{
	const char *handled[] = {"plane", "sphere", "cone", "cylinder"};
	int i;

	if (str->base.type != STRING)
		return 1;
	i = arr_index_of(handled, str->value);
	if (i == -1)
		return 1;
	*type = i;
	return (0);
}

int gen_mat(t_assarray *mat, t_gen_params *out)
{
	t_imaterial *cur;

	if (mat->base.type != ASSARRAY)
		return 1;
	cur = &out->scene->primitives[out->scene->n_primitives - 1].mat;
	ft_memset(cur, 0, sizeof(*cur));
	gen_value(mat, "diffuse", &cur->diffuse, &(t_genfun_params){
			out, (void*)gen_vec3, false
	});
	gen_value(mat, "ambiant", &cur->ambiant, &(t_genfun_params){
			out, (void*)gen_vec3, true
	});
	cur->spec_intensity = 999999.0f;
	gen_value(mat, "spec", &cur->spec_intensity, &(t_genfun_params){
			out, (void*)gen_float, true
	});
	return 0;
}

int gen_trans(t_assarray *mat, t_gen_params *out)
{
	t_itrans *cur;

	if (mat->base.type != ASSARRAY)
		return 1;
	cur = &out->scene->primitives[out->scene->n_primitives - 1].trans;
	ft_memset(cur, 0, sizeof(*cur));
	gen_value(mat, "position", &cur->pos, &(t_genfun_params){
			out, (void*)gen_vec3, false
	});
	cur->rot_axis.v[0] = 1.0f;
	gen_value(mat, "rot_axis", &cur->rot_axis, &(t_genfun_params){
			out, (void*)gen_vec3, true
	});
	gen_value(mat, "rot_angle", &cur->rot_angle, &(t_genfun_params){
			out, (void*)gen_float, true
	});
	gen_value(mat, "scale", &cur->scale, &(t_genfun_params){
			out, (void*)gen_vec3, true
	});
	return 0;
}

void gen_prim(t_sink *sink, t_gen_params *params)
{
	t_assarray *prim;

	prim = (t_assarray*)sink->value;
	params->scene->n_primitives++;
	params->scene->primitives = realloc(params->scene->primitives,
	sizeof(t_iprimitive) * params->scene->n_primitives);
	gen_value(prim, "type",
			  &params->scene->primitives[params->scene->n_primitives - 1].type,
			  &(t_genfun_params){params, (void*)gen_type, false});
	gen_value(prim, "material",
			  params,
			  &(t_genfun_params){params, (void*)gen_mat, false});
	gen_value(prim, "transform",
			  params,
			  &(t_genfun_params){params, (void*)gen_trans, false});
}

void gen_cam(t_sink *sink, t_gen_params *params)
{
	t_assarray *cam;

	cam = (t_assarray*)sink->value;
	gen_value(cam, "pos", params->scene->cam_pos, &(t_genfun_params){
			params, (void*)gen_vec3, false
	});
	gen_value(cam, "dir", params->scene->cam_dir, &(t_genfun_params){
			params, (void*)gen_vec3, false
	});
}

void gen_spot(t_sink *sink, t_gen_params *params)
{
	t_assarray *spot;

	spot = (t_assarray*)sink->value;
	params->scene->n_spots++;
	params->scene->spots = realloc(params->scene->spots, sizeof(t_spot) *
								params->scene->n_spots);
	gen_value(spot, "pos", &params->scene->spots[params->scene->n_spots - 1],
			  &(t_genfun_params){ params, (void*)gen_vec3, false });
}

void gen_sink(t_dlist *elem, t_gen_params *params)
{
	const t_sink_gen sink_gen[] = { gen_err, gen_cam, gen_spot, gen_prim };
	const char *supp[] = { "camera", "spots", "prims", 0 };
	t_sink *sink;

	if (*params->errored)
		return ;
	sink = elem->content;
	(sink_gen + 1)[arr_index_of(supp, sink->name)](sink, params);
}

int fill_scene(t_iscene *scene, t_scene_parser *parsed)
{
	int errored;

	errored = 0;
	ftext_lstiterup(parsed->sinks, (void*)gen_sink, &(t_gen_params){
			&errored, scene, parsed
	});
	return errored;
}

t_iscene *gen_iscene(t_scene_parser *parsed)
{
	t_iscene *ret;

	ret = ft_memalloc(sizeof(*ret));
	if (fill_scene(ret, parsed) || !(ret->n_primitives && ret->n_spots &&
		(ret->cam_dir[0] || ret->cam_dir[1] || ret->cam_dir[2])))
	{
		free(ret->spots);
		free(ret);
		ret = 0;
	}
	return (ret);
}
