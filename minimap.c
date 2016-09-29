/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:59:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/29 21:12:21 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>
#include <math.h>

static void	map_character(t_env *env)
{
	t_pt	pt1;
	t_pt	pt2;
	double	value[2];

	value[0] = env->pos[0] * env->smap + 10;
	value[1] = env->pos[1] * env->smap + 10;
	pixel(value[0] + 1, value[1], 0xFF0000, env);
	pixel(value[0] - 1, value[1], 0xFF0000, env);
	pixel(value[0], value[1] + 1, 0xFF0000, env);
	pixel(value[0], value[1] - 1, 0xFF0000, env);
	pixel(value[0] + 1, value[1] + 1, 0xFF0000, env);
	pixel(value[0] - 1, value[1] - 1, 0xFF0000, env);
	pixel(value[0] + 1, value[1] - 1, 0xFF0000, env);
	pixel(value[0] - 1, value[1] + 1, 0xFF0000, env);
	pixel(value[0] + 2, value[1], 0xFF0000, env);
	pixel(value[0] - 2, value[1], 0xFF0000, env);
	pixel(value[0], value[1] + 2, 0xFF0000, env);
	pixel(value[0], value[1] - 2, 0xFF0000, env);
	pt1.x = value[0];
	pt1.y = value[1];
	pt1.col = 0xFF0000;
	pt2.x = (env->dir[0] * 0.5 + env->pos[0] + env->plane[0] * 0.66) * env->smap + 10;
	pt2.y = (env->dir[1] * 0.5 + env->pos[1] - env->plane[1] * 0.66) * env->smap + 10;
	pt2.col = 0xFF0000;
	line(pt1, pt2, env);
	pt2.x = (env->dir[0] * 0.5 + env->pos[0] - env->plane[0] * 0.66) * env->smap + 10;
	pt2.y = (env->dir[1] * 0.5 + env->pos[1] + env->plane[1] * 0.66) * env->smap + 10;
	line(pt1, pt2, env);
	pixel(value[0], value[1], 0x000000, env);
}

static void	pixel_grid(t_env *env, int i, int j)
{
	int	size;

	size = env->smap;
	if (i % size != 0 && j % size != 0)
	{
		if (env->map[(int)((i - size) / size)][(int)(j / size)] <= 0)
			pixel(j - (size - 10), i - (size - 10), ((i + j) % 2 == 0 ?
						0x08FFFFFF : 0x08999999), env);
		else
			pixel(j - (size - 10), i - (size - 10), ((i + j) % 2 > 0 ?
						0x08333333 : 0x08666666), env);
	}
}

void		minimap(t_env *env)
{
	int		i;
	int		j;
	int		size;

	size = env->smap;
	i = 1 + size;
	while (env->map[(int)((i - size) / size)] != NULL)
	{
		j = 1 + size;
		while ((int)((j++ - size) / size) < env->map[0][0])
			pixel_grid(env, i, (j - 1));
		i++;
	}
	map_character(env);
}
