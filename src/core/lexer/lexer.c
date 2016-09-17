#include <core/core.h>

int get_tok_idx(char **toks, int max, char *k)
{
	int i;

	i = 0;
	while (i < max)
		if (ft_strncmp(toks[i], k, ft_strlen(toks[i])) == 0)
			return i;
		else
			++i;
	return -1;
}

int get_sym(t_lexer *lex, char *v)
{
	int i;

	if ((i = get_tok_idx(lex->tokens, lex->n_tokens, v)) != -1)
		return lex->syms[i];
	return SYM_STRING;
}

void emit_token(t_lexer *lex, char *s, char *e)
{
	t_token *t;

	t = malloc(sizeof(*t));
	t->value = ft_memcpy(ft_memalloc(e - s + 1), s, e - s);
	t->line = lex->line;
	t->col = lex->col;
	t->sym = get_sym(lex, t->value);
	ftext_lstpush_back(lex->token_list, ftext_lstnewelemown(t, sizeof(*t)));
	lex->col += e - s;
	lex->cur += e - s;
}

void emit_eof(t_lexer *lex)
{
	t_token *t;

	t = malloc(sizeof(*t));
	t->value = ft_memcpy(ft_memalloc(4), "EOF", 4);
	t->line = lex->line;
	t->col = lex->col;
	t->sym = SYM_EOF;
	ftext_lstpush_back(lex->token_list, ftext_lstnewelemown(t, sizeof(*t)));
}

int is_token(t_lexer *lex, char *s)
{
	int i;

	if (ft_isspace(*s))
		return 0;
	i = get_tok_idx(lex->tokens, lex->n_tokens, s);
	return i != -1;
}

int make_token(t_lexer *lex)
{
	char *e;
	int i;

	if (lex->file[lex->cur] == '\n')
	{
		lex->line++;
		lex->col = 0;
	}
	if (ft_isspace(lex->file[lex->cur]))
		return !(lex->col += lex->file[lex->cur] == '\t' ? 8 : 1);
	if ((i = get_tok_idx(lex->tokens, lex->n_tokens, &lex->file[lex->cur])) != -1)
		emit_token(lex, &lex->file[lex->cur], &lex->file[lex->cur +
														ft_strlen(lex->tokens[i])]);
	if (i != -1)
		return 1;
	e = &lex->file[lex->cur];
	while (!is_token(lex, e) && !ft_isspace(*e))
	{
		++e;
	}
	emit_token(lex, &lex->file[lex->cur], e);
	return 1;
}

t_dlisthead *lexer_pass(t_lexer *lex)
{
	while (lex->file[lex->cur])
		while (lex->file[lex->cur] && !make_token(lex))
			++lex->cur;
	emit_eof(lex);
	return lex->token_list;
}

t_lexer *new_lexer(t_lexer_init_params params)
{
	int i;
	t_lexer *ret;

	ret = malloc(sizeof(*ret));
	ret->token_list = ftext_lstnew();
	ret->cur = 0;
	ret->line = 1;
	ret->col = 0;
	ret->size = params.size;
	ret->file = memcpy(ft_memalloc(params.size + 1), params.buffer, params.size);
	ret->tokens = malloc((params.n_tokens + 1) * sizeof(const char *));
	ret->n_tokens = params.n_tokens;
	ret->syms = malloc(params.n_tokens * sizeof(int));
	ft_memcpy(ret->syms, params.syms, params.n_tokens * sizeof(int));
	i = 0;
	while (i < params.n_tokens)
	{
		ret->tokens[i] = ft_strdup(params.tokens[i]);
		++i;
	}
	ret->tokens[i] = 0;
	return ret;
}

#include <stdio.h>

void print_token(t_dlist *token)
{
	t_token *tok;

	tok = token->content;
	printf("%s", tok->value);
}

void print_tokens(t_dlisthead *tokens)
{
	ftext_lstiter(tokens, print_token);
}

void delete_token(t_token *tok, size_t ign)
{
	(void)ign;
	free(tok->value);
	free(tok);
}

void delete_lexer(t_lexer *lex)
{
	int i;

	i = 0;
	while (i < lex->n_tokens)
		free(lex->tokens[i++]);
	free(lex->tokens);
	free(lex->file);
	free(lex->syms);
	ftext_lstdel(&lex->token_list, (void*)delete_token);
	free(lex);
}
