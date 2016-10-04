/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 18:40:34 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/04 17:05:54 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>

/*void	text(t_env *env)
  {
  mlx_string_put(env->mlx, env->win, 11, 1, 0, "Quit : Esc");
  mlx_string_put(env->mlx, env->win, 10, 0, 0xDDDDDD, "Quit : Esc");
  mlx_string_put(env->mlx, env->win, 11, 21, 0, "pos : arrows");
  mlx_string_put(env->mlx, env->win, 10, 20, 0xDDDDDD, "pos : arrows");
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
  mlx_string_put(env->mlx, env->win, env->sx - 184, 1, 0, "pos end:");
  mlx_string_put(env->mlx, env->win, env->sx - 185, 0, 0xDDDDDD, "pos end:");
  if (env->is_pos == 1)
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

static int	fill_loc(t_env *env, int y, int x)
{
	env->pos_x = 0.5 + (x - 1);
	env->pos_y = 0.5 + y;
	env->dir_x = cos(env->angle) * (-1);
	env->dir_y = sin(env->angle) * (-1);
	env->plane_y = cos(env->angle) * (-0.66);
	env->plane_x = sin(env->angle) * (-0.66);
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
			if (env->map[y][x] == 0 && ty == 0 && tx == 0)
			{
				ty = y;
				tx = x;
			}
			x++;
		}
		y++;
	}
	if (ty != 0 && tx != 0)
		return (fill_loc(env, ty, tx));
	return (0);
}

void		collisions(t_env *env, int keycode)
{
	double	add_x;
	double	add_y;

	add_x = (0.05 * sin(env->angle));
	add_y = (0.05 * cos(env->angle));
	if (env->map[(int)(env->pos_x + add_x)][(int)env->pos_y] != 0)
		env->pos_x += (keycode == 125 ? add_x : -add_x);
	if (env->map[(int)env->pos_x][(int)(env->pos_y + add_y)] != 0)
		env->pos_y += (keycode == 125 ? add_y : -add_y);
}
