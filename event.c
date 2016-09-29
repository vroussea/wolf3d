/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:48:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/29 21:05:49 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h> //////////////

static void	zoom(t_env *env, int keycode)
{
	if (keycode == 69)
		env->smap += (env->smap < 90 ? 12 : 0);
	if (keycode == 78)
		env->smap -= (env->smap > 20 ? 12 : 0);
}

static void	pos(t_env *env, int keycode)
{
	if (keycode == 125)
	{
		env->pos[1] += 0.075 * cos(env->angle);
		env->pos[0] += 0.075 * sin(env->angle);
	}
	else if (keycode == 126)
	{
		env->pos[1] -= 0.075 * cos(env->angle);
		env->pos[0] -= 0.075 * sin(env->angle);
	}
}

static void	rotation(t_env *env, int keycode)
{
	env->angle += (keycode == 123 ? 0.1 : 0);
	env->angle += (keycode == 124 ? -0.1 : 0);
	env->dir[1] = cos(env->angle) * (-1);
	env->dir[0] = sin(env->angle) * (-1);
	env->plane[0] = cos(env->angle) * (-0.5);
	env->plane[1] = sin(env->angle) * (-0.5);
}

int			key_funct(int keycode, t_env *env)
{
	if (keycode == 53)
		quit_funct(env);
	if (keycode == 69)
		zoom(env, keycode);
	if (keycode == 78)
		zoom(env, keycode);
	//	if (keycode == 125 || keycode == 126)
	//		collisions(env, keycode);
	if (keycode == 125 || keycode == 126)
		pos(env, keycode);
	if (keycode == 123 || keycode == 124)
		rotation(env, keycode);
	caller(env);
	printf("plane x : %.2f\nplane y : %.2f\n", env->plane[0] , env->plane[1]);
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
