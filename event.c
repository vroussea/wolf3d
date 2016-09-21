/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:48:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/21 21:29:45 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf.h"
#include <stdlib.h>
#include <math.h>

int	key_funct(int keycode, t_env *env)
{
	if (keycode == 53)
		quit_funct(env);
	if (keycode == 69)
		env->smap += (env->smap < 90? 12 : 0);
	if (keycode == 78)
		env->smap -= (env->smap > 20 ? 12 : 0);
	if (keycode == 123 || keycode == 124)
		env->angle += (keycode == 123 ? 0.15 : -0.15);
	if (keycode == 125)
	{
		env->move[1] += cos(env->angle);
		env->move[0] += sin(env->angle);
	}
	if (keycode == 126)
	{
		env->move[1] -= cos(env->angle);
		env->move[0] -= sin(env->angle);
	}
	ft_putstr("move x : ");
	ft_putendl(ft_itoa(env->move[0]));
	ft_putstr("move y : ");
	ft_putendl(ft_itoa(env->move[1]));
	/*if (keycode == 125 || keycode == 126)
		env->move[1] += (keycode == 125 ? env->smap / 10 : -env->smap / 10);*/
	caller(env);
	return (1);
}

int	quit_funct(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	ft_tabdel((void ***)&(env->map));
	ft_memdel((void **)&env);
	ft_putendl("Program Closed");
	exit(0);
	return (1);
}
