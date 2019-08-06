/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:25:21 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/28 17:26:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat3	matrices_multi(const t_mat3_ptr m1, const t_mat3_ptr m2)
{
	t_mat3 rt;

	rt.elems[0][0] = m1->elems[0][0] * m2->elems[0][0] +
		m1->elems[0][1] * m2->elems[1][0] + m1->elems[0][2] * m2->elems[2][0];
	rt.elems[0][1] = m1->elems[0][0] * m2->elems[0][1] +
		m1->elems[0][1] * m2->elems[1][1] + m1->elems[0][2] * m2->elems[2][1];
	rt.elems[0][2] = m1->elems[0][0] * m2->elems[0][2] +
		m1->elems[0][1] * m2->elems[1][2] + m1->elems[0][2] * m2->elems[2][2];
	rt.elems[1][0] = m1->elems[1][0] * m2->elems[0][0] +
		m1->elems[1][1] * m2->elems[1][0] + m1->elems[1][2] * m2->elems[2][0];
	rt.elems[1][1] = m1->elems[1][0] * m2->elems[0][1] +
		m1->elems[1][1] * m2->elems[1][1] + m1->elems[1][2] * m2->elems[2][1];
	rt.elems[1][2] = m1->elems[1][0] * m2->elems[0][2] +
		m1->elems[1][1] * m2->elems[1][2] + m1->elems[1][2] * m2->elems[2][2];
	rt.elems[2][0] = m1->elems[2][0] * m2->elems[0][0] +
		m1->elems[2][1] * m2->elems[1][0] + m1->elems[2][2] * m2->elems[2][0];
	rt.elems[2][1] = m1->elems[2][0] * m2->elems[0][1] +
		m1->elems[2][1] * m2->elems[1][1] + m1->elems[2][2] * m2->elems[2][1];
	rt.elems[2][2] = m1->elems[2][0] * m2->elems[0][2] +
		m1->elems[2][1] * m2->elems[1][2] + m1->elems[2][2] * m2->elems[2][2];
	return (rt);
}

t_vec3	mat_vec_multi(const t_mat3_ptr m, const t_vec3_ptr v)
{
	return ((t_vec3){
		v->x * m->elems[0][0] + v->y * m->elems[0][1] + v->z * m->elems[0][2],
		v->x * m->elems[1][0] + v->y * m->elems[1][1] + v->z * m->elems[1][2],
		v->x * m->elems[2][0] + v->y * m->elems[2][1] + v->z * m->elems[2][2]});
}

t_mat3	get_scaling_matrix(double c)
{
	return ((t_mat3){{{c, 0, 0}, {0, c, 0}, {0, 0, c}}});
}
