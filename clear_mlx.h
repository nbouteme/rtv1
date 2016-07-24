/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 04:58:14 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 05:04:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CLEAR_MLX_H
# define	CLEAR_MLX_H

# include <OpenGL/gl3.h>

void	*mlx_init();
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
void	*mlx_new_image(void *mlx_ptr,int width,int height);
int		mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
							int x, int y);
int		mlx_mouse_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_expose_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
int		mlx_loop(void *mlx_ptr);
int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
int		mlx_destroy_image(void *mlx_ptr, void *img_ptr);
int		mlx_hook(void *win_ptr, int x_event, int x_mask,
				int (*funct)(), void *param);
int		mlx_do_sync(void *mlx_ptr);

#define	MAX_EVENT	32
#define MAX_PIXEL_NB	200000
#define UNIQ_BPP	4

#define FONT_WIDTH	10
#define	FONT_HEIGHT	20

typedef int (*t_func)();


typedef struct	t_glsl_info
{
  GLuint	pixel_vshader;
  GLuint	pixel_fshader;
  GLuint	pixel_program;
  GLint		loc_pixel_position;
  GLint		loc_pixel_texture;
  GLint		loc_pixel_winhalfsize;

  GLuint	image_vshader;
  GLuint	image_fshader;
  GLuint	image_program;
  GLint		loc_image_position;
  GLint		loc_image_winhalfsize;
  GLint		loc_image_texture;
  GLint		loc_image_pos;
  GLint		loc_image_size;

  GLuint	font_vshader;
  GLuint	font_fshader;
  GLuint	font_program;
  GLint		loc_font_position;
  GLint		loc_font_winhalfsize;
  GLint		loc_font_texture;
  GLint		loc_font_color;
  GLint		loc_font_posinwin;
  GLint		loc_font_posinatlas;
  GLint		loc_font_atlassize;
} t_glsl_info;


typedef struct	s_mlx_img_list
{
  int			width;
  int			height;
  char			*buffer;
  GLfloat		vertexes[8];
  struct s_mlx_img_list	*next;
} t_mlx_img_list;


typedef struct	s_mlx_img_ctx
{
  GLuint		texture;
  GLuint		vbuffer;
  t_mlx_img_list	*img;
  struct s_mlx_img_ctx	*next;
} t_mlx_img_ctx;

typedef struct	s_mlx_win_list
{
  void			*winid;
  t_mlx_img_ctx		*img_list;
  int			nb_flush;
  int			pixmgt;
  struct s_mlx_win_list	*next;
} t_mlx_win_list;


typedef struct		s_mlx_ptr
{
  void			*appid;
  t_mlx_win_list	*win_list;
  t_mlx_img_list	*img_list;
  void			(*loop_hook)(void *);
  void			*loop_hook_data;
  void			*loop_timer;
  t_mlx_img_list	*font;
  int			main_loop_active;
} t_mlx_ptr;


#endif
