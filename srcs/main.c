/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:02:33 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 17:46:50 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_map(t_param_ptr param, t_point *points)
{
	int			i;
	t_param_ptr	p;

	p = (t_param *)param;
	i = -1;
	while (++i < p->map.n_elems)
	{
		if (((i + 1) % (p->map.n_cols)))
		{
			draw_line((t_point){get_transformed(&points[i].crd),
				points[i].color}, (t_point){get_transformed(&points[i + 1].crd),
				points[i + 1].color}, p);
		}
		if ((i + (p->map.n_cols)) < (p->map.n_elems))
			draw_line((t_point){get_transformed(&points[i].crd),
				points[i].color},
				(t_point){get_transformed(&points[i + p->map.n_cols].crd),
				points[i + p->map.n_cols].color}, p);
	}
	if (p->axes_flag)
		draw_axes(p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

static int	init_param(t_param_ptr p)
{
	if (!(p->mlx_ptr = mlx_init()))
		return (-1);
	if (!(p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH + 100, HEIGHT, "FDF")))
		return (-1);
	p->img.img_ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT);
	p->img.addr = mlx_get_data_addr(p->img.img_ptr, &p->img.bpp,
									&p->img.size_line, &p->img.endian);
	p->axes_flag = 1;
	p->map.n_cols = 0;
	p->map.n_elems = 0;
	p->map.n_rows = 0;
	p->map.pts = NULL;
	p->map.pts_org = NULL;
	p->map.scaling = 1;
	p->map.colored = 0;
	ft_memcpy(&p->map.axes[ox], &(t_vec3){1, 0, 0}, sizeof(t_vec3));
	ft_memcpy(&p->map.axes[oy], &(t_vec3){0, 1, 0}, sizeof(t_vec3));
	ft_memcpy(&p->map.axes[oz], &(t_vec3){0, 0, 1}, sizeof(t_vec3));
	return (0);
}

static void	die(const char *message, int nerror)
{
	if (!message)
	{
		ft_putendl_fd("invalid file! Amounts of elements in every line must be\
equal.\nForm of every element \"position of elem, [colour]\"", 2);
		exit(nerror);
	}
	if (ft_strcmp("", message) == 0)
		exit(nerror);
	ft_putendl_fd(message, 2);
	exit(nerror);
}

static void	set_vars(t_param_ptr p)
{
	int	i;

	i = -1;
	if (!p->map.colored)
		while (++i < p->map.n_elems)
		{
			if (p->map.pts[i].crd.z > 0.66)
				p->map.pts[i].color = 0x00ffffff;
			else if (p->map.pts[i].crd.z > 0.33)
				p->map.pts[i].color = 0x00503726;
			else if (p->map.pts[i].crd.z >= 0.0)
				p->map.pts[i].color = 0x0000ff00;
			else
				p->map.pts[i].color = 0x000000ff;
		}
	if (!(p->map.pts_org = malloc(sizeof(t_point) * p->map.n_elems)))
	{
		free(p->map.pts);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		mlx_destroy_image(p->mlx_ptr, p->img.img_ptr);
		die("Not enough memory", 0);
	}
	ft_memcpy(p->map.pts_org, p->map.pts, p->map.n_elems * sizeof(t_point));
}

int			main(int ac, char **av)
{
	t_param p;
	int		fd;
	int		a;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(av[0], 2);
		die(" input_file", -1);
	}
	if (init_param(&p) == -1)
		die("Oopsie, something went wrong.", -3);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		die("No such file!", -2);
	a = fd;
	if (((fd = read_map(&p.map, fd)) == 0))
		die(NULL, -4);
	close(a);
	if (fd == -1)
		die(NULL, -3);
	set_vars(&p);
	draw_map(&p, p.map.pts);
	mlx_hook(p.win_ptr, 2, 0, key_event, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
