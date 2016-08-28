#ifndef LEXER_H
# define LEXER_H

#include <libft/std.h>

typedef struct	s_token
{
	char *value;
	int line;
	int col;
	int sym;
}				t_token;

enum {
	SYM_EOF = -2,
	SYM_STRING = -1,
	SYM_WELL, SYM_LBRA, SYM_RBRA, SYM_COM, SYM_DOT, SYM_SCOL
};

typedef struct	s_lexer t_lexer;

typedef struct	s_lexer
{
	int line;
	int col;
	int cur;
	char *file;
	unsigned long size;
	int n_tokens;
	int *syms;
	char **tokens;
	t_dlisthead *token_list;
}				t_lexer;

typedef struct s_lexer_init_params
{
	const char *buffer;
	unsigned long size;
	int n_tokens;
	const char **tokens;
	int *syms;
}t_lexer_init_params;

t_lexer *new_lexer(t_lexer_init_params params);
t_dlisthead *lexer_pass(t_lexer *lexer);
void print_tokens(t_dlisthead *tokens);
void delete_lexer(t_lexer *lex);

#endif
