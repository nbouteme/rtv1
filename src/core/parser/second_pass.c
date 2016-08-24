#include <core/core.h>
#include <stdio.h>

void find_ref_in_object(t_dlist *elem, t_scene_parser *in);

typedef void (*t_finder)(t_dlist *, t_scene_parser *);

int pairkey_cmp(t_dlist *elem, char *k)
{
	t_pair *p;

	p = elem->content;
	return (ft_strcmp(p->key, k) == 0);
}

t_object *get_prop(t_assarray *arr, char *key)
{
	t_dlist *ret;

	ret = ftext_lstfind(arr->pairs, (void*)pairkey_cmp, key);
	if (ret)
		return ret->content;
	return (0);
}

t_assarray *find_assarray_with_prop(t_assarray *root_node, char *key, char *val)
{
	t_dlist *l;
	t_object *str;

	l = ftext_lstfind(root_node->pairs, (void*)pairkey_cmp, key);
	if (l)
		str = ((t_pair*)l->content)->value;
	if (l && str->type == STRING && ft_strcmp(val, ((t_string *)str)->value) == 0)
		return root_node;
	l = root_node->pairs->next;
	while (l != (t_dlist *)root_node->pairs)
	{
		str = l->content;
		if (str->type == ASSARRAY)
		{
			str = (t_object *)find_assarray_with_prop((t_assarray*)str, key, val);
			if (str)
				return (t_assarray*)str;
		}
		l = l->next;
	}
	return (0);
}

t_object *get_value(t_scene_parser *scene, char *name, char *prop)
{
	t_dlist *sink;
	t_assarray *arr;
	t_object *ret;

	sink = scene->sinks->next;
	arr = 0;
	while (sink != (t_dlist *)scene->sinks && !arr)
	{
		arr = find_assarray_with_prop(
			(t_assarray*)((t_sink*)sink->content)->value, "name", name);
		sink = sink->next;
	}
	if (!arr)
	{
		printf("Undefined reference to object %s\n", name);
		return 0;
	}
	else if (!(ret = get_prop(arr, prop)))
	{
		printf("Undefined property %s to object %s\n", prop, name);
		return 0;
	}
	return (ret);
}

void found_ref(t_dlist *elem, t_scene_parser *in)
{
	t_reference *ref;

	ref = elem->content;
	ref->lazy_reference = get_value(in, ref->target_name, ref->member_name);
}

void do_nothing(t_dlist *elem, t_scene_parser *in)
{
	(void) elem;
	(void) in;
}

void find_ref_in_pair(t_dlist *elem, t_scene_parser *in)
{
	t_pair *pair;

	pair = elem->content;
	if (pair)
		find_ref_in_object(&(t_dlist){.content = pair->value}, in);
	else
		in->valid = false;
}

void find_ref_in_assarray(t_dlist *elem, t_scene_parser *in)
{
	t_assarray *arr;

	arr = elem->content;
	if (arr)
		ftext_lstiterup(arr->pairs, (void*)find_ref_in_pair, in);	
	else
		in->valid = false;
}

void find_ref_in_array(t_dlist *elem, t_scene_parser *in)
{
	t_array *arr;

	arr = elem->content;
	if (arr)
		ftext_lstiterup(arr->values, (void*)find_ref_in_object, in);	
	else
		in->valid = false;
}

void find_ref_in_object(t_dlist *elem, t_scene_parser *in)
{
	const t_finder finders[] = {find_ref_in_array, find_ref_in_assarray, found_ref,
								do_nothing};
	t_object *obj;

	obj = elem->content;
	if (obj)
		finders[obj->type](elem, in);
	else
		in->valid = false;
}

void find_ref_in_sink(t_dlist *elem, t_scene_parser *in)
{
	t_dlist tmp;
	t_sink *sink;

	sink = elem->content;
	tmp.content = sink->value;
	if (sink)
		find_ref_in_object(&tmp, in);
	else
		in->valid = false;
}

t_scene_parser *second_pass(t_scene_parser *in)
{
	ftext_lstiterup(in->sinks, (void*)find_ref_in_sink, in);
	return in;
}
