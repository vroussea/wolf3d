/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:48:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 21:26:02 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf.h"
#include <stdlib.h>

int	key_funct(int keycode, t_env *env)
{
	if (keycode == 53)
		quit_funct(env);
	if (keycode == 69)
		env->smap += (env->smap < 90? 12 : 0);
	if (keycode == 78)
		env->smap -= (env->smap > 20 ? 12 : 0);
//	if (keycode == 126 || keycode == 125)
	//	env->move[1] += (keycode == 126 ? 10 / env->zoom : -(10 / env->zoom));
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
