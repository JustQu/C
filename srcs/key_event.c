/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:01:25 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 18:01:20 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static void	reset_map(t_param_ptr p)
{
	ft_memcpy(p->map.pts, p->map.pts_org,
			p->map.n_elems * sizeof(t_point));
	ft_memcpy(&p->map.axes[ox], &(t_vec3){1, 0, 0}, sizeof(t_vec3));
	ft_memcpy(&p->map.axes[oy], &(t_vec3){0, 1, 0}, sizeof(t_vec3));
	ft_memcpy(&p->map.axes[oz], &(t_vec3){0, 0, 1}, sizeof(t_vec3));
}

static void	switch_key3(int keycode, t_param_ptr p)
{
	int i;

	if (keycode == KEY_I)
		map_rot_y(&p->map, 180);
	if (keycode == KEY_O)
		map_rot_z(&p->map, 180);
	if (keycode == KEY_ZERO)
		p->map.scaling = 1;
	i = -1;
	if (keycode == 126)
		while (++i < p->map.n_elems)
			(p->map.pts + i)->crd.y += 0.05;
	i = -1;
	if (keycode == 125)
		while (++i < p->map.n_elems)
			(p->map.pts + i)->crd.y -= 0.05;
	i = -1;
	if (keycode == 123)
		while (++i < p->map.n_elems)
			(p->map.pts + i)->crd.x -= 0.05;
	i = -1;
	if (keycode == 124)
		while (++i < p->map.n_elems)
			(p->map.pts + i)->crd.x += 0.05;
	p->axes_flag = (keycode == KEY_F) ? !p->axes_flag : p->axes_flag;
}

static void	switch_key2(int keycode, t_param_ptr p)
{
	if (keycode == KEY_R)
		reset_map(p);
	if (keycode == KEY_ONE)
	{
		reset_map(p);
		map_rot_x(&p->map, 90);
		map_rot_y(&p->map, 45);
		map_rot_x(&p->map, -35.264);
	}
	if (keycode == KEY_J)
	{
		reset_map(p);
		map_rot_x(&p->map, -90);
	}
	if (keycode == KEY_U)
		map_rot_x(&p->map, 180);
	if (keycode == KEY_K)
	{
		reset_map(p);
		map_rot_y(&p->map, 90);
	}
	switch_key3(keycode, p);
}

static void	switch_key1(int keycode, t_param_ptr p)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		mlx_destroy_image(p->mlx_ptr, p->img.img_ptr);
		free(p->map.pts);
		free(p->map.pts_org);
		exit(0);
	}
	if (keycode == KEY_Q)
		map_rot_z(&p->map, -5);
	else if (keycode == KEY_E)
		map_rot_z(&p->map, 5);
	else if (keycode == KEY_W)
		map_rot_x(&p->map, 5);
	else if (keycode == KEY_S)
		map_rot_x(&p->map, -5);
	else if (keycode == KEY_A)
		map_rot_y(&p->map, 5);
	else if (keycode == KEY_D)
		map_rot_y(&p->map, -5);
	else if (keycode == KEY_PLUS)
		p->map.scaling += 0.05;
	else if (keycode == KEY_MINUS)
		p->map.scaling -= 0.05;
	switch_key2(keycode, p);
}

int			key_event(int keycode, void *pr)
{
	t_mat3		b;
	t_map_ptr	m;
	t_param_ptr	p;
	int			i;

	p = (t_param_ptr)pr;
	m = &p->map;
	switch_key1(keycode, p);
	b = get_scaling_matrix(m->scaling);
	m->scaling = 1;
	i = -1;
	while (++i < m->n_elems)
	{
		m->pts[i].crd = mat_vec_multi(&b, &m->pts[i].crd);
	}
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	ft_memset(p->img.addr, 0, p->img.size_line * HEIGHT);
	draw_map(p, p->map.pts);
	return (0);
}
