/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:59:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/22 16:31:43 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>
#include <math.h>

static void	map_character(t_env *env)
{
	t_pt	pt1;
	t_pt	pt2;

	pixel(env->move[0] + 1, env->move[1], 0xFF0000, env);
	pixel(env->move[0] - 1, env->move[1], 0xFF0000, env);
	pixel(env->move[0], env->move[1] + 1, 0xFF0000, env);
	pixel(env->move[0], env->move[1] - 1, 0xFF0000, env);
	pixel(env->move[0] + 1, env->move[1] + 1, 0xFF0000, env);
	pixel(env->move[0] - 1, env->move[1] - 1, 0xFF0000, env);
	pixel(env->move[0] + 1, env->move[1] - 1, 0xFF0000, env);
	pixel(env->move[0] - 1, env->move[1] + 1, 0xFF0000, env);
	pixel(env->move[0] + 2, env->move[1], 0xFF0000, env);
	pixel(env->move[0] - 2, env->move[1], 0xFF0000, env);
	pixel(env->move[0], env->move[1] + 2, 0xFF0000, env);
	pixel(env->move[0], env->move[1] - 2, 0xFF0000, env);
	pt1.x = env->move[0];
	pt1.y = env->move[1];
	pt1.col = 0xFF0000;
	pt2.x = env->move[0] - sin(env->angle) * 8;
	pt2.y = env->move[1] - cos(env->angle) * 8;
	pt2.col = 0xFF0000;
	line(pt1, pt2, env);
	pixel(env->move[0], env->move[1], 0x000000, env);
}

static void	pixel_grid(t_env *env, int i, int j)
{
	int	size;

	size = env->smap;
	if (i % size != 0 && j % size != 0)
	{
		if (env->map[(int)((i - size) / size)][(int)(j / size)] != 0)
			pixel(j - (size - 10), i - (size - 10), ((i + j) % 2 == 0 ?
						0x08FFFFFF : 0x08999999), env);
		else
			pixel(j - (size - 10), i - (size - 10), ((i + j) % 2 == 0 ?
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
