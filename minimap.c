/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:59:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/05 21:53:47 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>
#include <math.h>

static void	ping(t_env *env, t_pt pt1)
{
	pixel(pt1.x + 1, pt1.y, 0xFF0000, env);
	pixel(pt1.x - 1, pt1.y, 0xFF0000, env);
	pixel(pt1.x, pt1.y + 1, 0xFF0000, env);
	pixel(pt1.x, pt1.y - 1, 0xFF0000, env);
	pixel(pt1.x + 1, pt1.y + 1, 0xFF0000, env);
	pixel(pt1.x - 1, pt1.y - 1, 0xFF0000, env);
	pixel(pt1.x + 1, pt1.y - 1, 0xFF0000, env);
	pixel(pt1.x - 1, pt1.y + 1, 0xFF0000, env);
	pixel(pt1.x + 2, pt1.y, 0xFF0000, env);
	pixel(pt1.x - 2, pt1.y, 0xFF0000, env);
	pixel(pt1.x, pt1.y + 2, 0xFF0000, env);
	pixel(pt1.x, pt1.y - 2, 0xFF0000, env);
}

static void	map_character(t_env *env)
{
	t_pt	pt1;
	t_pt	pt2;
	double	tmpplane_x;
	double	tmpplane_y;

	pt1.col = 0xFF0000;
	pt2.col = 0xFF0000;
	tmpplane_x = env->plane_x * 0.5;
	tmpplane_y = env->plane_y * 0.5;
	pt1.x = env->pos_x * env->smap + 10;
	pt1.y = env->pos_y * env->smap + 10;
	ping(env, pt1);
	pt2.x = (env->dir_x * 0.5 + env->pos_x + tmpplane_x) * env->smap + 10;
	pt2.y = (env->dir_y * 0.5 + env->pos_y + tmpplane_y) * env->smap + 10;
	line(pt1, pt2, env);
	pt2.x = (env->dir_x * 0.5 + env->pos_x - tmpplane_x) * env->smap + 10;
	pt2.y = (env->dir_y * 0.5 + env->pos_y - tmpplane_y) * env->smap + 10;
	line(pt1, pt2, env);
	pixel(pt1.x, pt1.y, 0x000000, env);
}

static void	pixel_grid(t_env *env, int y, int x)
{
	int	size;

	size = env->smap;
	if (y % size != 0 && x % size != 0)
	{
		if (env->map[(int)((y - size) / size)][(int)(x / size)] <= 0)
			pixel(x - (size - 10), y - (size - 10), ((y + x) % 2 == 0 ?
						0x08FFFFFF : 0x08999999), env);
		else
			pixel(x - (size - 10), y - (size - 10), ((y + x) % 2 > 0 ?
						0x08333333 : 0x08666666), env);
	}
}

void		minimap(t_env *env)
{
	int		y;
	int		x;
	int		size;

	size = env->smap;
	y = 1 + size;
	while (env->map[(int)((y - size) / size)] != NULL)
	{
		x = 1 + size;
		while ((int)((x - size) / size) < env->map[0][0])
		{
			pixel_grid(env, y, x);
			x++;
		}
		y++;
	}
	map_character(env);
}
