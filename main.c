/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:40:59 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/07 17:27:59 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdlib.h>

void		caller(t_env *env)
{
	ft_bzero(env->meml, env->sizel * env->sy);
	sky_ground(env);
	raycaster(env);
	minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 1, 1);
}

static void	init_val(t_env *env, char *file)
{
	int		bpp;
	int		edan;

	if (!(file_reader(file, &(env->map))) || test_map_closed(env))
	{
		ft_putendl("Error Map");
		quit_funct(env);
	}
	env->smap = 10;
	env->angle = 0;
	if (start_loc(env, -1, -1) == 0)
	{
		ft_putendl("No starting location on map");
		quit_funct(env);
	}
	env->meml = mlx_get_data_addr(env->img, &bpp, &(env->sizel), &edan);
	mlx_hook(env->win, 2, 0, key_funct, env);
	mlx_hook(env->win, 17, 0, quit_funct, env);
	caller(env);
	mlx_loop(env->mlx);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		quit_funct(env);
	env->sx = 1280;
	env->sy = 720;
	if (argc < 2 || !(env->mlx = mlx_init()) ||
		!(env->win = mlx_new_window(env->mlx, env->sx, env->sy, "Wolf3D")) ||
		!(env->img = mlx_new_image(env->mlx, env->sx, env->sy)))
		ft_putendl("Error : Please enter valid map file.");
	else
		init_val(env, argv[1]);
	return (0);
}
