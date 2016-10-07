/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 18:40:34 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/07 17:33:09 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>
#include <math.h>

void    pixel(int x, int y, int col, t_env *env)
{
	if (x > 0 && x < env->sx && y > 0 && y < env->sy)
		ft_memcpy(&env->meml[(x - 1) * 4 + (y - 1) * env->sizel], &col, 4);
}

static int	fill_loc(t_env *env, int y, int x)
{
	env->pos_x = 0.5 + (x - 1);
	env->pos_y = 0.5 + y;
	env->dir_x = cos(env->angle) * (-1);
	env->dir_y = sin(env->angle) * (-1);
	env->plane_x = -env->dir_y * 0.66;
	env->plane_y = env->dir_x * 0.66;
	return (1);
}

int			start_loc(t_env *env, int ty, int tx)
{
	int	y;
	int	x;

	y = 0;
	while (env->map[y] != NULL)
	{
		x = 1;
		while (x <= env->map[0][0])
		{
			if (env->map[y][x] == -1)
				return (fill_loc(env, y, x));
			if (env->map[y][x] == 0 && ty == -1 && tx == -1)
			{
				ty = y;
				tx = x;
			}
			x++;
		}
		y++;
	}
	if (ty != -1 && tx != -1)
		return (fill_loc(env, ty, tx));
	return (0);
}

int			test_map_closed(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (env->map[i] != NULL)
	{
		if (env->map[i][1] <= 0 || env->map[i][env->map[0][0]] <= 0)
			return (1);
		i++;
	}
	j = 1;
	while (j <= env->map[0][0])
	{
		if (env->map[0][j] <= 0 || env->map[i - 1][j] <= 0)
			return (1);
		j++;
	}
	return (0);
}

void		sky_ground(t_env *env)
{
	int	x;
	int	y;

	y = 0;
	while (y < env->sy)
	{
		x = 0;
		while (x < env->sx)
		{
			pixel(x, y, (y < env->sy / 2.5 ? 0x0066CC : 0x606060), env);
			x++;
		}
		y++;
	}
}
