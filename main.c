/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:40:59 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 19:02:59 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdlib.h>

static void	caller(t_env *env)
{
//	mlx_hook(env->win, 6, 0, motion_funct, env);
//	mlx_hook(env->win, 4, 0, zoom_funct, env);
	mlx_hook(env->win, 2, 0, key_funct, env);
	mlx_hook(env->win, 17, 0, quit_funct, env);
	minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 1, 1);
	mlx_loop(env->mlx);
}

static void	init_val(t_env *env, char *file)
{
	int		bpp;
	int		edan;
	int		i;
	int		j;

	if (!(file_reader(file, &(env->map))))
	{
		ft_putendl("Error Map");
		quit_funct(env);
	}
	i = 0;
	while (env->map[i] != NULL)
	{
		j = 1;
		while (j <= env->map[i][0])
		{
			ft_putnbr(env->map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	env->pos_x = 0;
	env->pos_y = 0;
	env->meml = mlx_get_data_addr(env->img, &bpp, &(env->sizel), &edan);
	caller(env);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	env = (t_env *)ft_memalloc(sizeof(t_env));
	env->sx = 750;
	env->sy = 600;
	if (argc < 2 || !(env->mlx = mlx_init()) ||
		!(env->win = mlx_new_window(env->mlx, env->sx, env->sy, "Wolf3D")) ||
		!(env->img = mlx_new_image(env->mlx, env->sx, env->sy)))
		ft_putendl("Error");
	else
		init_val(env, argv[1]);
	return (0);
}
