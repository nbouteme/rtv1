#include <core/core.h>

void array_dtor(t_object *o)
{
	t_array *arr;

	arr = (void*)o;
	ftext_lstdel(&arr->values, (void*)delete_object);
	free(o);
}

void delete_pair(t_pair *pair, size_t ign)
{
	(void) ign;

	free(pair->key);
	delete_object(pair->value, 0);
	free(pair);
}

void assarray_dtor(t_object *o)
{
	t_assarray *arr;

	arr = (void*)o;
	ftext_lstdel(&arr->pairs, (void*)delete_pair);
	free(o);
}

void ref_dtor(t_object *o)
{
	t_reference *ref;

	ref = (void*)o;
	free(ref->target_name);
	free(ref->member_name);
	free(o);
}

void string_dtor(t_object *o)
{
	t_string *str;

	str = (void*)o;
	free(str->value);
	free(o);
}
