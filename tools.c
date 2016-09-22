/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 18:40:34 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/22 22:10:47 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h> ////

/*void	text(t_env *env)
  {
  mlx_string_put(env->mlx, env->win, 11, 1, 0, "Quit : Esc");
  mlx_string_put(env->mlx, env->win, 10, 0, 0xDDDDDD, "Quit : Esc");
  mlx_string_put(env->mlx, env->win, 11, 21, 0, "Move : arrows");
  mlx_string_put(env->mlx, env->win, 10, 20, 0xDDDDDD, "Move : arrows");
  mlx_string_put(env->mlx, env->win, 11, 41, 0, "Zoom : mouse or / *");
  mlx_string_put(env->mlx, env->win, 10, 40, 0xDDDDDD, "Zoom : mouse or / *");
  mlx_string_put(env->mlx, env->win, 11, 61, 0, "Iteration : page up down");
  mlx_string_put(env->mlx, env->win, 10, 60, 0xDDDDDD,
  "Iteration : page up down");
  mlx_string_put(env->mlx, env->win, 11, 81, 0, "Color : + -");
  mlx_string_put(env->mlx, env->win, 10, 80, 0xDDDDDD, "Color : + -");
  mlx_string_put(env->mlx, env->win, 10, env->sy - 20, 0, "Color:");
  mlx_string_put(env->mlx, env->win, 70, env->sy - 20, 0,
  ft_itoa(env->colmod));
  mlx_string_put(env->mlx, env->win, 11, env->sy - 21, 0xDDDDDD, "Color:");
  mlx_string_put(env->mlx, env->win, 71, env->sy - 21, 0xDDDDDD,
  ft_itoa(env->colmod));
  mlx_string_put(env->mlx, env->win, 10, env->sy - 40, 0, "Iterations:");
  mlx_string_put(env->mlx, env->win, 120, env->sy - 40, 0,
  ft_itoa(env->i_max));
  mlx_string_put(env->mlx, env->win, 11, env->sy - 41, 0xDDDDDD,
  "Iterations:");
  mlx_string_put(env->mlx, env->win, 121, env->sy - 41, 0xDDDDDD,
  ft_itoa(env->i_max));
  }

  void	hud_text(t_env *env)
  {
  if (env->is_text == 1)
  {
  mlx_string_put(env->mlx, env->win, env->sx - 151, env->sy - 21, 0,
  "Hide HUD : Del");
  mlx_string_put(env->mlx, env->win, env->sx - 150, env->sy - 20,
  0xDDDDDD, "Hide HUD : Del");
  }
  else
  {
  mlx_string_put(env->mlx, env->win, env->sx - 151, env->sy - 21, 0,
  "Show HUD : Del");
  mlx_string_put(env->mlx, env->win, env->sx - 150, env->sy - 20,
  0xDDDDDD, "Show HUD : Del");
  }
  }

  void	special_text(t_env *env)
  {
  mlx_string_put(env->mlx, env->win, env->sx - 184, 1, 0, "Move end:");
  mlx_string_put(env->mlx, env->win, env->sx - 185, 0, 0xDDDDDD, "Move end:");
  if (env->is_move == 1)
  {
  mlx_string_put(env->mlx, env->win, env->sx - 32, 1, 0x55BB55, "ON");
  mlx_string_put(env->mlx, env->win, env->sx - 33, 0, 0x00FF00, "ON");
  }
  else
  {
  mlx_string_put(env->mlx, env->win, env->sx - 32, 1, 0xBB5555, "OFF");
  mlx_string_put(env->mlx, env->win, env->sx - 33, 0, 0xFF0000, "OFF");
  }
  mlx_string_put(env->mlx, env->win, env->sx - 184, 21, 0, "Indent home:");
  mlx_string_put(env->mlx, env->win, env->sx - 185, 20, 0xDDDDDD,
  "Indent home:");
  if (env->is_indent == 0)
  {
  mlx_string_put(env->mlx, env->win, env->sx - 32, 21, 0x55BB55, "ON");
  mlx_string_put(env->mlx, env->win, env->sx - 33, 20, 0x00FF00, "ON");
  }
  else
  {
  mlx_string_put(env->mlx, env->win, env->sx - 32, 21, 0xBB5555, "OFF");
mlx_string_put(env->mlx, env->win, env->sx - 33, 20, 0xFF0000, "OFF");
}
}*/

static int	fill_loc(t_env *env, int i, int j)
{
	env->move[1] = env->smap / 2 + env->smap * i + 10;
	env->move[0] = env->smap / 2 + env->smap * (j - 1) + 10;
	return (1);
}

int			start_loc(t_env *env, int ti, int tj)
{
	int	i;
	int	j;

	i = 0;
	while (env->map[i] != NULL)
	{
		j = 1;
		while (j <= env->map[0][0])
		{
			if (env->map[i][j] == 2)
				return (fill_loc(env, i, j));
			if (env->map[i][j] == 1 && ti == 0 && tj == 0)
			{
				ti = i;
				tj = j;
			}
			j++;
		}
		i++;
	}
	if (ti != 0 && tj != 0)
		return (fill_loc(env, ti, tj));
	return (0);
}

void		collisions(t_env *env, int keycode)
{
	double	pos_x;
	double	pos_y;
	double	add_x;
	double	add_y;

	pos_x = ((env->move[0] - 10)) / env->smap;
	pos_y = ((env->move[1] - 10)) / env->smap + 1;
	add_x = (0.05 * sin(env->angle));
	add_y = (0.05 * cos(env->angle));
	printf("pos_y + add_y =: %.3f + %.3f = %.3f\npos x + add_x : %.3f + %.3f = %.3f\nint pos_x + add_x : %d\nint pos_y + add_y : %d\n", pos_y, add_y, pos_y + add_y, pos_x, add_x, pos_x + add_x, (int)(pos_x + add_x), (int)(pos_y + add_y));
	ft_putstr("valeur map x : ");
	ft_putendl(ft_itoa(env->map[(int)(pos_x + add_x)][(int)pos_y]));
	if (env->map[(int)(pos_x + add_x)][(int)pos_y] != 0)
		env->move[0] += (keycode == 125 ? add_x * env->smap : -add_x * env->smap);
	if (env->map[(int)pos_x][(int)(pos_y + add_y)] != 0)
		env->move[1] += (keycode == 125 ? add_y * env->smap : -add_y * env->smap);
}
