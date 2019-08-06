/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:50:09 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 16:51:20 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1. : (placement / distance));
}

static int		get_light(int start, int end, double percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

int				get_color(t_point current, t_point start, t_point end,
														t_point delta)
{
	int		r;
	int		g;
	int		b;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.crd.x > delta.crd.y)
		percentage = percent(start.crd.x, end.crd.x, current.crd.x);
	else
		percentage = percent(start.crd.y, end.crd.y, current.crd.y);
	r = get_light((start.color >> 16) & 0xFF,
		(end.color >> 16) & 0xFF, percentage);
	g = get_light((start.color >> 8) & 0xFF,
		(end.color >> 8) & 0xFF, percentage);
	b = get_light(start.color & 0xFF,
		end.color & 0xFF, percentage);
	return ((r << 16) | (g << 8) | b);
}

int				rgba_to_rgb(int color, double a)
{
	int r;
	int g;
	int b;

	if (a >= 1 || a <= 0)
		return (color);
	r = (color >> 16) & 0x000000ff;
	g = (color >> 8) & 0x000000ff;
	b = (color) & 0x000000ff;
	r = a * r;
	g = a * g;
	b = a * b;
	return ((r << 16) | (g << 8) | b);
}
