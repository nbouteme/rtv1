#include <core/core.h>

/*
t_iscene *load_iscene(const char *fn)
{
	unsigned long size;
	void *buf;
	t_lexer *lex;
	t_scene_parser *parsed;
	t_iscene *ret;

	ret = 0;
	if (!(buf = from_file(fn, &size, scene_file_check)))
		return (0);
	lex = new_lexer((t_lexer_init_params){buf, size, 6,
				(const char *[]){"<-", "{", "}", ",", ".", ":"},
				(int[]){SYM_WELL, SYM_LBRA, SYM_RBRA, SYM_COM, SYM_DOT, SYM_SCOL}
		});
	lexer_pass(lex);
	print_tokens(lex->token_list);
	parsed = parser_pass(lex);
	if (parsed && parsed->valid)
		ret = gen_iscene(parsed);
	free(buf);
	delete_lexer(lex);
	delete_scene(parsed);
	return ret;
}
*/

t_iscene *load_iscene(const char *fn)
{
	unsigned long size;
	void *buf;
	void *desc;
	t_iscene *ret;

	buf = from_file(fn, &size, scene_file_check);
	desc = from_file("lang", &size, scene_file_check);
	t_langparser *l = lang_parser(desc);
	t_parser *p = get_parser(l, "file");
	void *out;
	ret = 0;
	if (!run_parser(p, buf, &out))
	{
		ft_putstr(((t_error*)out)->expected);
		print_error(out, buf);
		free(out);
	}
	else
	{
		ret = gen_iscene(out, buf);
		delete_ast(out);
	}
	delete_langparser(l);
	free(buf);
	free(desc);
	return (ret);
}

int scene_file_check(char *buf, int s)
{
	(void)buf;
	(void) s;
	return 1;
}
