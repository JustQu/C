/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:52:08 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/05 16:38:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_token(t_tok *tok, char **str, int *colored)
{
	char	*p;

	if (!str || !*str || !**str || !tok)
		return (0);
	p = *str;
	if (!(!*p || ft_isspace(*p) || ft_isdigit(*p) || *p == '-' || *p == '+'))
		return (-1);
	tok->value = ft_strtol(p, &p, 10);
	if (*p && !ft_isspace(*p) && *p != ',')
		return (-1);
	while (ft_isspace(*p))
		p++;
	tok->color = 0x00FFFFFF;
	if (*p == ',' && p++)
	{
		while (ft_isspace(*p))
			p++;
		if (*p)
			*colored = (tok->color += ft_strtol(p, &p, 0) - 0x00FFFFFF) ? 1 : 1;
		else
			return (-1);
	}
	if (!(!*p || ft_isspace(*p) || ft_isdigit(*p) || *p == '-' || *p == '+'))
		return (-1);
	return ((*str = p) ? 1 : 1);
}

static void	*tokscpy(t_point_ptr p, t_tok *t, int row, int n)
{
	int			i;
	t_point_ptr	new;

	if (!(new = malloc(sizeof(t_point) * row * n)))
		return (NULL);
	ft_memcpy(new, p, (row - 1) * n * sizeof(t_point));
	if (p != NULL)
		free(p);
	i = -1;
	while (++i < n)
	{
		*(new + (row - 1) * n + i) =
			(t_point){{i, row - 1, t->value}, t->color};
		t++;
	}
	return (new);
}

static void	pts_normalization(t_map_ptr m)
{
	int		i;
	double	max;
	double	min;
	double	n1;
	double	n2;

	if (!m->pts)
		return ;
	min = m->pts->crd.z;
	max = min;
	i = -1;
	n1 = 2. / (m->n_cols - (m->n_cols == 1 ? 0 : 1));
	n2 = 2. / (m->n_rows - (m->n_rows == 1 ? 0 : 1));
	while (++i < m->n_elems)
	{
		(m->pts + i)->crd.z > max ? max = (m->pts + i)->crd.z : 0;
		(m->pts + i)->crd.z < min ? min = (m->pts + i)->crd.z : 0;
		(m->pts + i)->crd.x = (m->pts + i)->crd.x * n1 - 1;
		(m->pts + i)->crd.y = ABS((m->pts + i)->crd.y - m->n_rows + 1) * n2 - 1;
	}
	i = -1;
	n1 = ABS(max) > ABS(min) ? 1. / max : 1. / min;
	n1 = (n1 == INFINITY || n1 == -INFINITY) ? 0 : n1;
	while (++i < m->n_elems)
		(m->pts + i)->crd.z = (m->pts + i)->crd.z * n1;
}

static int	parse_str(t_tok **tokens, char *str, int *colored)
{
	char	*p;
	t_tok	*s;
	int		i;

	if ((i = ft_wc(str)) == 0)
		return (0);
	*tokens = (t_tok *)malloc(sizeof(t_tok) * i);
	if (!(s = *tokens))
		return (-1);
	p = str;
	while (ft_isspace(*p))
		p++;
	while ((i = get_token(s, &p, colored)) == 1)
	{
		while (ft_isspace(*p))
			p++;
		s++;
	}
	if (i == -1)
	{
		free(*tokens);
		return (0);
	}
	return (*tokens ? s - *tokens : -1);
}

int			read_map(t_map_ptr map, int fd)
{
	char	*line;
	t_tok	*tokens;
	int		i;

	while ((i = get_next_line(fd, &line) == 1))
	{
		i = parse_str(&tokens, line, &map->colored);
		map->n_cols == 0 ? map->n_cols = i : 0;
		if (i < 1 || i != map->n_cols)
		{
			free(line);
			free(map->pts);
			if (i > 1)
				free(tokens);
			return (i > 1 ? 0 : -1);
		}
		map->n_elems = i * ++map->n_rows;
		map->pts = tokscpy(map->pts, tokens, map->n_rows, i);
		free(line);
		free(tokens);
		if (!map->pts)
			return (-1);
	}
	pts_normalization(map);
	return (i == -1 ? -1 : !!map->n_cols);
}
