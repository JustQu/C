/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:34:36 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 16:48:57 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap1(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	point_wuline(t_param *p, t_point *c, int steep)
{
	if (steep)
	{
		put_pixel(&p->img, c->crd.y, c->crd.x,
			rgba_to_rgb(c->color, 1 - (c->crd.y - (int)c->crd.y)));
		put_pixel(&p->img, c->crd.y + 1, c->crd.x,
			rgba_to_rgb(c->color, (c->crd.y - (int)c->crd.y)));
	}
	else
	{
		put_pixel(&p->img, c->crd.x, c->crd.y,
			rgba_to_rgb(c->color, 1 - (c->crd.y - (int)c->crd.y)));
		put_pixel(&p->img, c->crd.x, c->crd.y + 1,
			rgba_to_rgb(c->color, (c->crd.y - (int)c->crd.y)));
	}
}

void	plot_wuline(t_param *p, t_point p1, t_point p2, int steep)
{
	t_point delta;
	t_point c;
	double	gradient;

	delta.crd = (t_vec3){p2.crd.x - p1.crd.x, p2.crd.y - p1.crd.y, 0};
	gradient = delta.crd.y / delta.crd.x;
	c.crd = (t_vec3){p1.crd.x, p1.crd.y + gradient, 0};
	c.color = p1.color;
	while (++c.crd.x < p2.crd.x)
	{
		if (c.crd.x > WIDTH || c.crd.x < 0 || c.crd.y < 0 || c.crd.y > HEIGHT)
		{
			c.crd.y += gradient;
			continue;
		}
		c.color = get_color(c, p1, p2, delta);
		point_wuline(p, &c, steep);
		c.crd.y += gradient;
	}
}

void	draw_line(t_point p1, t_point p2, t_param *p)
{
	int steep;

	steep = ABS(p2.crd.y - p1.crd.y) > ABS(p2.crd.x - p1.crd.x);
	if (steep)
	{
		swap1(&p1.crd.x, &p1.crd.y);
		swap1(&p2.crd.x, &p2.crd.y);
	}
	if (p1.crd.x > p2.crd.x)
	{
		swap1(&p1.crd.x, &p2.crd.x);
		swap1(&p1.crd.y, &p2.crd.y);
		ft_swap(&p1.color, &p2.color);
	}
	if (steep)
	{
		put_pixel(&p->img, p1.crd.y, p1.crd.x, p1.color);
		put_pixel(&p->img, p2.crd.y, p2.crd.x, p2.color);
	}
	else
	{
		put_pixel(&p->img, p1.crd.x, p1.crd.y, p1.color);
		put_pixel(&p->img, p2.crd.x, p2.crd.y, p2.color);
	}
	plot_wuline(p, p1, p2, steep);
}
