/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:10:35 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/13 04:01:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <core/core.h>
#include <unistd.h>

void usage()
{
	ft_putstr("Usage: ./rtv1 [scene file]");
	exit(1);
}

float angle;

int main(int argc, char **argv)
{
/*	t_iscene *scene;
	t_display *display;
*/
	if (argc != 2)
		usage();
	unsigned long size;
	void *buff = from_file(argv[1], &size, scene_file_check);
	if (!buff)
		return !!write(2, "An error occured.\n", 18);
	t_lexer *lex = new_lexer((t_lexer_init_params) {
			buff, size, 6,
				(const char *[]){"<-", "{", "}", ",", ".", ":"},
				(int[]){SYM_WELL, SYM_LBRA, SYM_RBRA, SYM_COM, SYM_DOT, SYM_SCOL}
		});
	t_dlisthead *tokens = lexer_pass(lex);
	t_scene_parser *parsed_scene = parser_pass(tokens);
	print_tokens(tokens);
	free(buff);
	delete_lexer(lex);
	delete_scene(parsed_scene);
/*	angle = atof(argv[1]);
	scene = load_iscene(argv[1]);
	display = new_display((t_display_init_param)
						  {
							1280,
							720,
							CPU_DRIVER,
							scene
						});
	register_display(display);
	run_display(display);
*/
	return 0;
}
