/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:48:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/22 21:27:27 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf.h"
#include <stdlib.h>
#include <math.h>

static void	search_start(t_env *env, int *ti, int *tj)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*ti = 0;
	while (env->map[*ti] != NULL)
	{
		*tj = 1;
		while (*tj <= env->map[0][0])
		{
			if (env->map[*ti][*tj] == 2)
				return ;
			if (env->map[*ti][*tj] == 1 && i == 0 && j == 0)
			{
				i = *ti;
				j = *tj;
			}
			(*tj)++;
		}
		(*ti)++;
	}
	*ti = i;
	*tj = j;
}

static void	zoom(t_env *env, int keycode)
{
	int	i;
	int	j;

	search_start(env, &i, &j);
	env->move[1] -= env->smap / 2 + env->smap * i + 10;
	env->move[0] -= env->smap / 2 + env->smap * (j - 1) + 10;
	env->move[1] /= env->smap;
	env->move[0] /= env->smap;
	if (keycode == 69)
		env->smap += (env->smap < 90 ? 12 : 0);
	if (keycode == 78)
		env->smap -= (env->smap > 20 ? 12 : 0);
	env->move[1] *= env->smap;
	env->move[0] *= env->smap;
	env->move[1] += env->smap / 2 + env->smap * i + 10;
	env->move[0] += env->smap / 2 + env->smap * (j - 1) + 10;
}

int			key_funct(int keycode, t_env *env)
{
	if (keycode == 53)
		quit_funct(env);
	if (keycode == 69)
		zoom(env, keycode);
	if (keycode == 78)
		zoom(env, keycode);
	env->angle += (keycode == 123 ? 0.15 : 0);
	env->angle += (keycode == 124 ? -0.15 : 0);
	if (keycode == 125 || keycode == 126)
		collisions(env, keycode);
	/*	env->move[1] += 0.05 * cos(env->angle) * env->smap;
		env->move[0] += 0.05 * sin(env->angle) * env->smap;
	}
	if (keycode == 126)
	{
		collisions(env, keycode);
		env->move[1] -= 0.05 * cos(env->angle) * env->smap;
		env->move[0] -= 0.05 * sin(env->angle) * env->smap;
	}*/
	caller(env);
	return (1);
}

int			quit_funct(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	ft_tabdel((void ***)&(env->map));
	ft_memdel((void **)&env);
	ft_putendl("Program Closed");
	exit(0);
	return (1);
}
