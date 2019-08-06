/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:49:45 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 17:33:44 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "mlx.h"
# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53

# define KEY_O_L 111

# define WIDTH 800
# define HEIGHT 800
# define X_FACTOR (float)x_factor
# define Y_FACTOR (float)y_factor
# define PI 3.14159265359
# define RAD 0.01745329252

# ifndef ULONG_MAX
#  define ULONG_MAX ((unsigned long)(~0L))
# endif
# ifndef LONG_MAX
#  define LONG_MAX ((long)(ULONG_MAX >> 1))
# endif
# ifndef LONG_MIN
#  define LONG_MIN ((long)(~LONG_MAX))
# endif

enum
{
	x_factor = WIDTH >> 1,
	y_factor = HEIGHT >> 1
};

typedef struct s_point	t_point;
typedef struct s_image	t_image;
typedef struct s_map	t_map;
typedef struct s_param	t_param;
typedef struct s_vec3	t_vec3;
typedef struct s_mat3	t_mat3;

typedef struct s_point	*t_point_ptr;
typedef struct s_image	*t_image_ptr;
typedef struct s_map	*t_map_ptr;
typedef struct s_param	*t_param_ptr;
typedef struct s_mat3	*t_mat3_ptr;
typedef struct s_vec3	*t_vec3_ptr;

typedef enum	e_axis
{
	ox,
	oy,
	oz
}				t_axis;

struct			s_vec3
{
	double		x;
	double		y;
	double		z;
};

struct			s_mat3
{
	double		elems[3][3];
};

struct			s_point
{
	t_vec3		crd;
	int			color;
};

struct			s_image
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
};

struct			s_map
{
	t_point		*pts;
	t_point		*pts_org;
	double		scaling;
	int			n_cols;
	int			n_rows;
	int			n_elems;
	t_vec3		axes[3];
	int			colored;
};

struct			s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	t_map		map;
	int			axes_flag;
};

typedef struct	s_tok
{
	int value;
	int color;
}				t_tok;

int				get_color(t_point current, t_point start, t_point end,
							t_point delta);
int				rgba_to_rgb(int color, double a);
void			draw_line(t_point p1, t_point p2, t_param *p);
void			draw_brline(t_point start, t_point end, void *p_params);
int				read_map(t_map_ptr map, int fd);
int				key_event(int keycode, void *pr);
void			put_pixel(t_image *img, int x, int y, int color);
t_mat3			matrices_multi(const t_mat3_ptr m1, const t_mat3_ptr m2);
t_vec3			mat_vec_multi(const t_mat3_ptr m, const t_vec3_ptr v);
t_mat3			get_rotate_mat_z(double angle);
t_mat3			get_rotate_mat_y(double angle);
t_mat3			get_rotate_mat_x(double angle);
void			map_rot_x(t_map_ptr m, double x);
void			map_rot_y(t_map_ptr m, double y);
void			map_rot_z(t_map_ptr m, double z);
t_mat3			get_scaling_matrix(double c);
void			put_pixel(t_image *img, int x, int y, int color);
t_vec3			get_transformed(const t_vec3_ptr v);
t_vec3			perspective_transforamtion(const t_vec3_ptr v);
void			draw_map(t_param_ptr param, t_point *points);
void			draw_axes(t_param_ptr p);

#endif
