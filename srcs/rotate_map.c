/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:26:21 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/28 17:36:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_rot_x(t_map_ptr m, double x)
{
	t_mat3	a;
	int		i;

	a = get_rotate_mat_x(x);
	i = -1;
	while (++i < m->n_elems)
	{
		(m->pts + i)->crd = mat_vec_multi(&a, &(m->pts + i)->crd);
	}
	m->axes[ox] = mat_vec_multi(&a, m->axes + ox);
	m->axes[oy] = mat_vec_multi(&a, m->axes + oy);
	m->axes[oz] = mat_vec_multi(&a, m->axes + oz);
}

void	map_rot_y(t_map_ptr m, double y)
{
	t_mat3	a;
	int		i;

	a = get_rotate_mat_y(y);
	i = -1;
	while (++i < m->n_elems)
	{
		(m->pts + i)->crd = mat_vec_multi(&a, &(m->pts + i)->crd);
	}
	m->axes[ox] = mat_vec_multi(&a, m->axes + ox);
	m->axes[oy] = mat_vec_multi(&a, m->axes + oy);
	m->axes[oz] = mat_vec_multi(&a, m->axes + oz);
}

void	map_rot_z(t_map_ptr m, double z)
{
	t_mat3	a;
	int		i;

	a = get_rotate_mat_z(z);
	i = -1;
	while (++i < m->n_elems)
	{
		(m->pts + i)->crd = mat_vec_multi(&a, &(m->pts + i)->crd);
	}
	m->axes[ox] = mat_vec_multi(&a, m->axes + ox);
	m->axes[oy] = mat_vec_multi(&a, m->axes + oy);
	m->axes[oz] = mat_vec_multi(&a, m->axes + oz);
}
