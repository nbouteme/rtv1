#ifndef PARSER_H
# define PARSER_H

enum
{
	ARRAY, ASSARRAY, REF, STRING
};

typedef struct	s_object
{
	int type;
}				t_object;

typedef struct	s_scalar
{
	t_object base;
	float value;
}				t_scalar;

typedef struct	s_array
{
	t_object base;
	t_dlisthead *values;
}				t_array;

typedef struct	s_pair
{
	char *key;
	t_object *value;
}				t_pair;

typedef struct	s_assarray
{
	t_object base;
	t_dlisthead *pairs;
}				t_assarray;

typedef struct	s_reference
{
	t_object base;
	t_object *lazy_reference;
	char *target_name;
	char *member_name;
}				t_reference;

typedef struct	s_string
{
	t_object base;
	char *value;
}				t_string;

typedef struct	s_sink
{
	char *name;
	t_object *value;
}				t_sink;

typedef struct  s_scene_parser
{
	t_dlisthead *sinks;
	int valid;
}				t_scene_parser;

typedef void (*t_pobj_dtor)(t_object *obj);
void delete_object(t_object *obj, size_t ign);

t_object *parse_object(t_dlist **elem);
t_object *parse_assarray(t_dlist **elem);

t_scene_parser *parser_pass(t_dlisthead *tokens);
t_scene_parser *second_pass(t_scene_parser *in);

void delete_scene(t_scene_parser *scene);

void array_dtor(t_object *o);
void assarray_dtor(t_object *o);
void ref_dtor(t_object *o);
void string_dtor(t_object *o);

#endif
