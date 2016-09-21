#include <core/core.h>
#include <math.h>

typedef struct	s_generror
{
	t_ast	*frag_w;
	char	*message;
	char	*miss;
}				t_generror;

typedef t_generror*(*t_sgen)(t_iscene *, t_ast *, t_ast *);

static float a3_dot(float a[3], float b[3])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

t_generror *new_gerror(t_ast *wfrag, const char *m, const char *mi)
{
	t_generror *ret;
	ret = malloc(sizeof(*ret));
	ret->frag_w = wfrag;
	ret->message = ft_strdup(m);
	ret->miss = ft_strdup(mi);
	return ret;
}

t_generror *ukwn_sink(t_iscene *ret, t_ast *sink, t_ast *r)
{
	(void)ret;
	(void)r;
	return new_gerror(sink->children[0], "Unknown sink name: ", sink->children[0]->value);
}

t_ast *get_value(t_ast *assarr, const char *name)
{
	int i;

	i = 1;
	while (i < assarr->n_children)
	{
		if (ft_strcmp(name, assarr->children[i]->children[0]->value) == 0)
			return assarr->children[i]->children[2];
		i += 2;
	}
	return 0;
}

t_ast *find_aa_with_name(t_ast *root, const char *name)
{
	t_ast *ret;
	int i;
	i = 0;

	if (!root)
		return (0);
	if (strstr(root->tag, "|assoc_array") && (ret = get_value(root, "name"))
	&& ft_strstr(ret->tag, "|string") && ft_strcmp(name, ret->value) == 0)
		return ret;
	while (i < root->n_children)
		if ((ret = find_aa_with_name(root->children[i], name)))
			return ret;
		else
			++i;
	return 0;
}

t_ast *eval_ref(t_ast *root, t_ast *elem)
{
	char *name;
	t_ast *arr;

	if (!elem || !elem->n_children || !ft_strstr(elem->children[0]->tag, "|ref"))
		return elem;
	name = elem->children[0]->value;
	arr = find_aa_with_name(root, name);
	return get_value(arr, elem->children[2]->value);
}

int str_arr_find(const char **a, const char *s)
{
	int i;

	i = 0;
	while (a[i])
		if (ft_strcmp(a[i], s) == 0)
			return i;
		else
			++i;
	return -1;
}

t_generror *gen_scalar(float *a, t_ast *elem)
{
	int n;

	if (!strstr(elem->tag, "|int") && !strstr(elem->tag, "|float"))
		return new_gerror(elem, "Expected scalable type, got: ", elem->tag);
	if (strstr(elem->tag, "|int"))
		*a = ft_atoi(elem->value);
	else
	{
		n = elem->children[0]->value[0] == '-';
		*a = ft_atoi(elem->children[0]->value + n);
		*a += ((float)ft_atoi(elem->children[2]->value)) / pow(10, ft_strlen(elem->children[2]->value));
		*a = n ? -*a : *a;
	}
	return 0;
}

t_generror *gen_vec3(float *a, t_ast *elem, t_ast *root)
{
	int i;
	t_ast *e;
	void *tmp;

	if (!strstr(elem->tag, "|array"))
		return new_gerror(elem, "Expected type array, got: ", elem->tag);
	if (elem->n_children != 7)
		return new_gerror(elem, "Got mismatched number of elements in array: ", "3 elements were required");
	i = 1;
	while (i < elem->n_children)
	{
		e = eval_ref(root, elem->children[i]);
		if ((tmp = gen_scalar(&a[(i - 1) / 2], e)))
			return tmp;
		i += 2;
	}
	return (0);
}

t_generror *gen_camera(t_iscene *ret, t_ast *sink, t_ast *r)
{
	t_ast *pos;
	void *e;

	if (ret->camset)
		return new_gerror(sink->children[0], "Duplicate sink found: ", "camera");
	ret->camset = 1;
	pos = eval_ref(r, get_value(sink->children[2], "pos"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in camera: ", "pos");
	if ((e = gen_vec3(ret->cam_pos, pos, r)))
		return e;
	pos = eval_ref(r, get_value(sink->children[2], "dir"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in camera: ", "dir");
	if ((e = gen_vec3(ret->cam_dir, pos, r)))
		return e;
	pos = eval_ref(r, get_value(sink->children[2], "up"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in camera: ", "up");
	if ((e = gen_vec3(ret->cam_up, pos, r)))
		return e;
	float kek = a3_dot(ret->cam_up, ret->cam_dir);
	if (fabs(kek) >= 0.0001f)
		return new_gerror(sink->children[2], "Up and Direction vector aren't perpendicular: ", "You fucked up");
	return (0);
}

t_generror *gen_spot(t_iscene *ret, t_ast *sink, t_ast *r)
{
	t_ast *pos;
	void *tmp;

	tmp = ret->spots;
	ret->spots = malloc(sizeof(t_spot) * (ret->n_spots + 1));
	ft_memcpy(ret->spots, tmp, sizeof(t_spot) * ret->n_spots);
	free(tmp);
	pos = eval_ref(r, get_value(sink->children[2], "pos"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in spot: ", "pos");
	if ((tmp = gen_vec3(ret->spots[ret->n_spots].pos.v, pos, r)))
		return tmp;
	ret->n_spots++;
	return (0);
}

t_generror *gen_type(t_prim_type *ret, t_ast *elem)
{
	const char *types[] = {"plane", "sphere", "cone", "cylinder", 0};
	int i;

	if (!strstr(elem->tag, "|string"))
		return new_gerror(elem, "Expected string type, got: ", elem->tag);
	i = str_arr_find(types, elem->value);
	if (i == -1)
		return new_gerror(elem, "Unknown primitive type: ", elem->value);
	*ret = i;
	return (0);
}

t_generror *gen_material(t_imaterial *ret, t_ast *ass, t_ast *r)
{
	t_ast *pos;
	void *e;

	pos = eval_ref(r, get_value(ass, "diffuse"));
	if (!pos)
		return new_gerror(ass, "Couldn't find attribute in material: ", "diffuse");
	if ((e = gen_vec3(ret->diffuse, pos, r)))
		return e;
	ret->spec_intensity = 999999.9f;
	pos = eval_ref(r, get_value(ass, "ambiant"));
	if (pos && (e = gen_vec3(ret->ambiant, pos, r)))
		return e;
	pos = eval_ref(r, get_value(ass, "spec"));
	if (pos && (e = gen_scalar(&ret->spec_intensity, pos)))
		return e;
	return (0);
}

t_generror *gen_trans(t_itrans *ret, t_ast *ass, t_ast *r)
{
	t_ast *pos;
	void *e;

	pos = eval_ref(r, get_value(ass, "position"));
	if (!pos)
		return new_gerror(ass, "Couldn't find attribute in transform: ", "position");
	if ((e = gen_vec3(ret->pos.v, pos, r)))
		return e;
	ft_memcpy(ret->rot_axis.v, (float[]){1.0, 0.0, 0.0}, sizeof(ret->rot_axis));
	ft_memcpy(ret->scale.v, (float[]){1.0, 1.0, 1.0}, sizeof(ret->scale));
	ret->rot_angle = 0.0f;
	pos = eval_ref(r, get_value(ass, "rot_axis"));
	if (pos && (e = gen_vec3(ret->rot_axis.v, pos, r)))
		return e;
	pos = eval_ref(r, get_value(ass, "rot_angle"));
	if (pos && (e = gen_scalar(&ret->rot_angle, pos)))
		return e;
	pos = eval_ref(r, get_value(ass, "scale"));
	if (pos && (e = gen_vec3(ret->scale.v, pos, r)))
		return e;
	return (0);
}

t_generror *gen_prim(t_iscene *ret, t_ast *sink, t_ast *r)
{
	t_ast *pos;
	void *tmp;

	tmp = ret->primitives;
	ret->primitives = ft_memalloc(sizeof(t_iprimitive) * (ret->n_primitives + 1));
	ft_memcpy(ret->primitives, tmp, sizeof(t_iprimitive) * ret->n_primitives);
	free(tmp);
	pos = eval_ref(r, get_value(sink->children[2], "type"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in primitive: ", "type");
	if ((tmp = gen_type(&ret->primitives[ret->n_primitives].type, pos)))
		return tmp;
	pos = eval_ref(r, get_value(sink->children[2], "material"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in primitive: ", "material");
	if ((tmp = gen_material(&ret->primitives[ret->n_primitives].mat, pos, r)))
		return tmp;
	pos = eval_ref(r, get_value(sink->children[2], "transform"));
	if (!pos)
		return new_gerror(sink->children[2], "Couldn't find attribute in primitive: ", "transform");
	if ((tmp = gen_trans(&ret->primitives[ret->n_primitives].trans, pos, r)))
		return tmp;
	ret->n_primitives++;
	return (0);
}

t_generror *gen_sink(t_iscene *ret, t_ast *sink, t_ast *root)
{
	const char *sinks[] = {"camera", "spots", "prims", 0};
	const t_sgen sinkf[] = {&ukwn_sink, &gen_camera, &gen_spot, &gen_prim};

	if (!strstr(sink->tag, "|sink"))
		return new_gerror(sink, "Not a sink: ", sink->value);
	return sinkf[str_arr_find(sinks, sink->children[0]->value) + 1]
		(ret, sink, root);
}

void print_gerror(t_generror *e, const char *i)
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

t_iscene *gen_iscene(t_ast *parsed, const char *input)
{
	t_iscene *ret;
	t_generror *e;
	int i;

	ret = ft_memalloc(sizeof(*ret));
	i = 0;
	while (i < parsed->n_children)
		if((e = gen_sink(ret, parsed->children[i++], parsed)))
		{
			print_gerror(e, input);
			free(e->message);
			free(e->miss);
			free(ret->primitives);
			free(ret->spots);
			free(ret);
			return (0);
		}
	return (ret);
}
