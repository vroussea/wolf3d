/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:40:59 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/21 21:21:30 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdlib.h>

void		caller(t_env *env)
{
	ft_bzero(env->meml, env->sizel * env->sy);
	minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 1, 1);
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
	env->smap = 20;
	if (start_loc(env, 0, 0) == 0)
	{
		ft_putendl("No starting location on map");
		quit_funct(env);
	}
	env->angle = 0;
	env->meml = mlx_get_data_addr(env->img, &bpp, &(env->sizel), &edan);
	mlx_hook(env->win, 2, 0, key_funct, env);
	mlx_hook(env->win, 17, 0, quit_funct, env);
	caller(env);
	mlx_loop(env->mlx);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	env = (t_env *)ft_memalloc(sizeof(t_env));
	env->sx = 1900;
	env->sy = 1080;
	if (argc < 2 || !(env->mlx = mlx_init()) ||
		!(env->win = mlx_new_window(env->mlx, env->sx, env->sy, "Wolf3D")) ||
		!(env->img = mlx_new_image(env->mlx, env->sx, env->sy)))
		ft_putendl("Error : Please enter valid map file.");
	else
		init_val(env, argv[1]);
	return (0);
}
