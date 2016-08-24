#include <core/core.h>
#include <stdio.h>

void next_token(t_token **t, t_dlist **elem)
{
	*elem = (*elem)->next;
	if (*t)
		*t = (*elem)->content;
}

t_scene_parser *bind_parser(t_scene_parser *in)
{
	static t_scene_parser *tsp = 0;

	if (in)
		tsp = in;
	return (tsp);
}

enum {
	TOK_EQ  = 0x0,
	TOK_NEQ = 0x1,
	TOK_DOR = 0x2
};

int assert_tok(t_dlist **elem, int tok, int op)
{
	t_scene_parser *p;
	t_token *obj;
	int cond;

	p = bind_parser(0);
	if (!p->valid)
		return (0);
	obj = (*elem)->content;
	cond = (op & 1) == TOK_EQ ? (obj->sym == tok) : (obj->sym != tok);
	if (!cond && ((op & 2) == TOK_DOR))
	{
		ft_putstr("Unexpected `");
		ft_putstr(obj->value);
		ft_putstr("` token at ");
		ft_putnbr(obj->line);
		ft_putchar(':');
		ft_putnbr(obj->col);
		ft_putchar('\n');
		p->valid = false;
		return 0;
	}
	if (!cond)
		return (0);
	return (1);
}

t_object *parse_array(t_dlist **elem)
{
	t_array *ret;
	t_token *arr;

	arr = (*elem)->content;
	if (!assert_tok(elem, SYM_LBRA, TOK_EQ | TOK_DOR))
		return (0);
	ret = malloc(sizeof(*ret));
	ret->base.type = ARRAY;
	ret->values = ftext_lstnew();
	next_token(&arr, elem);
	while (assert_tok(elem, SYM_RBRA, TOK_NEQ))
	{
		ftext_lstpush_back(ret->values, ftext_lstnewelemown(parse_object(elem), 0));
		arr = (*elem)->content;
		if (assert_tok(elem, SYM_RBRA, TOK_EQ))
			break;
		if (!assert_tok(elem, SYM_COM, TOK_EQ | TOK_DOR))
			return (0);
		next_token(&arr, elem);
	}
	*elem = (*elem)->next;
	return (t_object*)ret;
}

t_object *try_parse_array(t_dlist **elem)
{
	if (assert_tok(elem, SYM_SCOL, TOK_EQ))
		return (t_object *)parse_assarray(elem);
	return (t_object *)parse_array(elem);
}

t_object *parse_string(t_dlist **elem)
{
	t_string *ret;
	t_token *arr;

	arr = (*elem)->content;
	if (!assert_tok(elem, SYM_STRING, TOK_EQ | TOK_DOR))
		return (0);
	ret = malloc(sizeof(*ret));
	ret->base.type = STRING;
	ret->value = ft_strdup(arr->value);
	*elem = (*elem)->next;
	return (t_object*)ret;
}

t_object *parse_reference(t_dlist **elem)
{
	t_reference *ret;
	t_token *arr;

	arr = (*elem)->content;
	if (!assert_tok(elem, SYM_STRING, TOK_EQ | TOK_DOR))
		return (0);
	ret = ft_memalloc(sizeof(*ret));
	ret->base.type = REF;
	ret->target_name = ft_strdup(arr->value);
	next_token(&arr, elem);
	if (!assert_tok(elem, SYM_DOT, TOK_EQ | TOK_DOR))
		return (0);
	next_token(&arr, elem);
	if (!assert_tok(elem, SYM_STRING, TOK_EQ | TOK_DOR))
		return (0);
	*elem = (*elem)->next;
	ret->member_name = ft_strdup(arr->value);
	return (t_object*)ret;
}

t_object *try_parse_simple(t_dlist **elem)
{
	if (assert_tok(elem, SYM_DOT, TOK_EQ))
		return (t_object *)parse_reference(elem);
	return (t_object *)parse_string(elem);
}

t_object *parse_object(t_dlist **elem)
{
	if (assert_tok(elem, SYM_LBRA, TOK_EQ))
		return (try_parse_array(elem));
	else if (assert_tok(elem, SYM_STRING, TOK_EQ | TOK_DOR))
		return (try_parse_simple(elem));
	return (0);
}

t_pair *parse_pair(t_dlist **elem)
{
	t_pair *ret;
	t_token *arr;

	arr = (*elem)->content;
	if (!assert_tok(elem, SYM_STRING, TOK_EQ | TOK_DOR))
		return (0);
	ret = malloc(sizeof(*ret));
	ret->key = ft_strdup(arr->value);
	next_token(&arr, elem);
	if (!assert_tok(elem, SYM_SCOL, TOK_EQ | TOK_DOR))
		return (0);
	next_token(&arr, elem);
	ret->value = parse_object(elem);
	return ret;
}

t_object *parse_assarray(t_dlist **elem)
{
	t_assarray *ret;
	t_token *arr;

	arr = (*elem)->content;
	if (!assert_tok(elem, SYM_LBRA, TOK_EQ | TOK_DOR))
		return (0);
	ret = ft_memalloc(sizeof(*ret));
	ret->base.type = ASSARRAY;
	ret->pairs = ftext_lstnew();
	next_token(&arr, elem);
	while (assert_tok(elem, SYM_RBRA, TOK_NEQ))
	{
		ftext_lstpush_back(ret->pairs, ftext_lstnewelemown(parse_pair(elem), 0));
		arr = (*elem)->content;
		if (!assert_tok(elem, SYM_COM, TOK_NEQ | TOK_DOR) &&
			!assert_tok(elem, SYM_RBRA, TOK_NEQ | TOK_DOR))
			return (0);
		if (assert_tok(elem, SYM_COM, TOK_EQ))
			next_token(&arr, elem);
	}
	return (t_object*)ret;
}

void parse_sink(t_scene_parser *parser, t_dlist **elem)
{
	t_sink parsed;
	char *name;
	t_token *sink_name;

	sink_name = (*elem)->content;
	if (!assert_tok(elem, SYM_STRING, TOK_EQ | TOK_DOR))
		return ;
	name = sink_name->value;
	*elem = (*elem)->next;
	sink_name = (*elem)->content;
	if (!assert_tok(elem, SYM_WELL, TOK_EQ | TOK_DOR))
		return ;
	parsed.name = ft_strdup(name);
	*elem = (*elem)->next;
	parsed.value = parse_assarray(elem);
	ftext_lstpush_back(parser->sinks, ftext_lstnewelem(&parsed, sizeof(parsed)));
}

t_scene_parser *parser_pass(t_dlisthead *tokens)
{
	t_scene_parser *parser;
	t_dlist *next;

	parser = malloc(sizeof(*parser));
	bind_parser(parser);
	parser->valid = true;
	parser->sinks = ftext_lstnew();
	next = tokens->next;
	while (next != (t_dlist*)tokens
		&& ((t_token*)next->content)->sym != SYM_EOF)
	{
		parse_sink(parser, &next);
		next = next->next;
	}
	return second_pass(parser);
}
