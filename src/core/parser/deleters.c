#include <core/core.h>

void delete_object(t_object *obj, size_t ign)
{
	const t_pobj_dtor dtor[] = {array_dtor, assarray_dtor,
								ref_dtor, string_dtor, scalar_dtor};

	(void) ign;
	if (obj)
		dtor[obj->type](obj);
}

void delete_sink(t_sink *sink, size_t ign)
{
	(void) ign;
	if (!sink)
		return ;
	free(sink->name);
	delete_object(sink->value, 0);
	free(sink);
}

void delete_scene(t_scene_parser *scene)
{
	int i;
	i = 0;

	ftext_lstdel(&scene->sinks, (void*)delete_sink);
	while (scene->file[i])
		free(scene->file[i++]);
	free(scene->file);
	free(scene);
}
