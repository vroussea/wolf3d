/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:48:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/07 17:02:41 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf.h"
#include <stdlib.h>
#include <math.h>

static void	zoom(t_env *env, int keycode)
{
	if (keycode == 69)
		env->smap += (env->smap < 90 ? 12 : 0);
	if (keycode == 78)
		env->smap -= (env->smap > 20 ? 12 : 0);
}

/*static void	pos(t_env *env, int keycode)
{
	if (keycode == 125)
	{
		env->pos_x += 0.075 * cos(env->angle);
		env->pos_y += 0.075 * sin(env->angle);
	}
	else if (keycode == 126)
	{
		env->pos_x -= 0.075 * cos(env->angle);
		env->pos_y -= 0.075 * sin(env->angle);
	}
}*/

void        collisions(t_env *env, int keycode)
{
	double  move_x;
	double  move_y;

	if (keycode == 125)
	{
		move_x = 0.075 * cos(env->angle);
		move_y = 0.075 * sin(env->angle);
	}
	else
	{
		move_x = -0.075 * cos(env->angle);
		move_y = -0.075 * sin(env->angle);
	}
	if (env->map[(int)env->pos_y][(int)(env->pos_x + 3 * move_x) + 1] <= 0)
		env->pos_x += move_x;
	if (env->map[(int)(env->pos_y + 3 * move_y)][(int)(env->pos_x) + 1] <= 0)
		env->pos_y += move_y;
}

static void	rotation(t_env *env, int keycode)
{
	env->angle += (keycode == 124 ? 0.1 : 0.1 * (-1));
	env->dir_x = cos(env->angle) * (-1);
	env->dir_y = sin(env->angle) * (-1);
	env->plane_x = -env->dir_y * 0.66;
	env->plane_y = env->dir_x * 0.66;
}

int			key_funct(int keycode, t_env *env)
{
	if (keycode == 53)
		quit_funct(env);
	if (keycode == 69)
		zoom(env, keycode);
	if (keycode == 78)
		zoom(env, keycode);
	if (keycode == 125 || keycode == 126)
		collisions(env, keycode);
	//	if (keycode == 125 || keycode == 126)
	//		pos(env, keycode);
	if (keycode == 123 || keycode == 124)
		rotation(env, keycode);
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
