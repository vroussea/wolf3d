/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:29:18 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/02 20:30:18 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	print_wall(t_env *env)
{
	if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
	else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
	int lineHeight = (int)(h / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + h / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if(drawEnd >= h)drawEnd = h - 1;
}

void		raycaster(t_env *env)
{
	int		x;
	double	crtray;
	double ray_x;
	double ray_y;

	x = 0;
	while(x < env->sx)
	{
		currentray = 2 * x / (double)(env->sx) - 1;
		ray_x = env->dir_x + env->plane_x * cameraX;
		ray_y = env->dir_y + env->plane_y * cameraX;
		env->ray_x = ray_x;
		env->ray_y = ray_y;
		env->distnext_x = sqrt(1 + (ray_y * ray_y) / (ray_x * ray_x));
		env->distnext_y = sqrt(1 + (ray_x * ray_x) / (ray_y * ray_y));
		dda(env);
		print_wall(env);
		x++;
	}
}

static void	init_dist(t_env *env, double *dist_x, double *dist_y)
{
	if (env->ray_x < 0)
	{
		env->step_x = -1;
		*dist_x = (env->pos_x - env->map_x) * env->distnext_x;
	}
	else
	{
		env->step_x = 1;
		*dist_x = (env->map_x + 1.0 - env->pos_x) * env->distnext_x;
	}
	if (env->ray_y < 0)
	{
		env->step_y = -1;
		*dist_y = (env->pos_y - env->map_y) * env->distnext_y;
	}
	else
	{
		env->step_y = 1;
		*dist_y = (env->map_y + 1.0 - env->pos_y) * env->distnext_y;
	}
}

void	 	dda(t_env *env, int dist_x, int dist_y)
{
	int		hit;
	double	dist_x;
	double	dist_y;

	init_dist(env, &dist_x, &dist_y);
	env->map_x = (int)env->pos_x;
	env->map_y = (int)env->pos_y;
	hit = 0;
	while (hit == 0)
	{
		if (dist_x < dist_y)
		{
			dist_x += env->distnext_x;
			env->map_xx += env->step_x;
			env->side = 0;
		}
		else
		{
			dist_y += env->distnext_y;
			env->map_y += env->step_y;
			env->side = 1;
		}
		if (worldMap[env->map_x][env->map_y] > 0)
			hit = 1;
	}
}
