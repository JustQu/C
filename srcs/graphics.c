/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:00:35 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 16:53:02 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*p;

	p = img->addr;
	if (x <= 0 || y <= 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	p = (p + img->size_line * y) + x * img->bpp / 8;
	*(int *)p = color;
}

t_vec3	get_transformed(const t_vec3_ptr v)
{
	return ((t_vec3){
		(v->x + 1.0f) * X_FACTOR,
		(-v->y + 1.0f) * Y_FACTOR,
		v->z});
}

t_vec3	perspective_transforamtion(const t_vec3_ptr v)
{
	float z_inv;

	z_inv = 1.0f / v->z;
	return ((t_vec3){
		(v->x * (double)z_inv + 1.0f) * X_FACTOR,
		(-v->y * (double)z_inv + 1.0f) * Y_FACTOR,
		v->z});
}

void	draw_axes(t_param_ptr p)
{
	t_point p1;

	p1.crd = get_transformed(&p->map.axes[ox]);
	p1.color = 0x00ff0000;
	draw_line((t_point){{WIDTH / 2, HEIGHT / 2, 0}, 0x00ff0000}, p1, p);
	p1.crd = get_transformed(&p->map.axes[oy]);
	p1.color = 0x0000ff00;
	draw_line((t_point){{WIDTH / 2, HEIGHT / 2, 0}, 0x0000ff00}, p1, p);
	p1.crd = get_transformed(&p->map.axes[oz]);
	p1.color = 0x000000ff;
	draw_line((t_point){{WIDTH / 2, HEIGHT / 2, 0}, 0x000000ff}, p1, p);
}
