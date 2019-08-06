/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:26:43 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/28 17:26:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat3	get_rotate_mat_z(double angle)
{
	double sin_a;
	double cos_a;

	sin_a = sin(angle * RAD);
	cos_a = cos(angle * RAD);
	return ((t_mat3) {{{
			cos_a, sin_a, 0},
			{-sin_a, cos_a, 0},
			{0, 0, 1}}});
}

t_mat3	get_rotate_mat_y(double angle)
{
	double sin_a;
	double cos_a;

	sin_a = sin(angle * RAD);
	cos_a = cos(angle * RAD);
	return ((t_mat3) {
			{{cos_a, 0, -sin_a},
			{0, 1, 0},
			{sin_a, 0, cos_a}}});
}

t_mat3	get_rotate_mat_x(double angle)
{
	double sin_a;
	double cos_a;

	sin_a = sin(angle * RAD);
	cos_a = cos(angle * RAD);
	return ((t_mat3) {
			{{1, 0, 0},
			{0, cos_a, sin_a},
			{0, -sin_a, cos_a}}});
}

t_mat3	get_rot_mat_xyz(double x, double y, double z)
{
	t_mat3 a;
	t_mat3 b;
	t_mat3 c;
	t_mat3 pr;
	t_mat3 r;

	a = get_rotate_mat_x(x);
	b = get_rotate_mat_y(y);
	c = get_rotate_mat_z(z);
	pr = matrices_multi(&a, &b);
	r = matrices_multi(&pr, &c);
	return (r);
}
