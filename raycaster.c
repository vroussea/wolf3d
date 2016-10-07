/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:29:18 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/07 17:37:32 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

static void	color_wall(t_env *env, t_pt *pt1, t_pt *pt2)
{
	if (env->side == 0)
	{
		pt1->col = (env->map_x > (int)env->pos_x > 0 ? 0xDD0000
				: 0xFF8000);
		pt2->col = (env->map_x > (int)env->pos_x > 0 ? 0xDD0000
				: 0xFF8000);
	}
	else
	{
		pt1->col = (env->map_y > (int)env->pos_y > 0 ? 0x00DD00
				: 0x006600);
		pt2->col = (env->map_y > (int)env->pos_y > 0 ? 0x00DD00
				: 0x006600);
	}
}

static void	print_wall(t_env *env, int x)
{
	int		height;
	double	dist;
	t_pt	*pt1;
	t_pt	*pt2;

	pt1 = (t_pt *)ft_memalloc(sizeof(t_pt));
	pt2 = (t_pt *)ft_memalloc(sizeof(t_pt));
	if (env->side == 0)
		dist = (env->map_x - env->pos_x + (1 - env->step_x) / 2) / env->ray_x;
	else
		dist = (env->map_y - env->pos_y + (1 - env->step_y) / 2) / env->ray_y;
	height = (int)(env->sy / dist);
	color_wall(env, pt1, pt2);
	pt1->x = x;
	pt2->x = x;
	pt1->y = (double)(-height / 1.6) + (double)(env->sy / 2.5);
	pt1->y = (pt1->y > 0 ? pt1->y : 0);
	pt2->y = (double)(height / 1.6) + (double)(env->sy / 2.5);
	pt2->y = (pt2->y > 0 ? pt2->y : 0);
	line(pt1, pt2, env);
	ft_memdel((void **)&pt1);
	ft_memdel((void **)&pt2);
}

void		raycaster(t_env *env)
{
	int		x;
	double	crtray;
	double	ray_x;
	double	ray_y;

	x = 0;
	while (x < env->sx)
	{
		crtray = 2 * x / (double)(env->sx) - 1;
		ray_x = env->dir_x + env->plane_x * crtray;
		ray_y = env->dir_y + env->plane_y * crtray;
		env->ray_x = ray_x;
		env->ray_y = ray_y;
		env->distnext_x = (ray_x != 0 ?
				sqrt(1 + (ray_y * ray_y) / (ray_x * ray_x)) : 0);
		env->distnext_y = (ray_y != 0 ?
				sqrt(1 + (ray_x * ray_x) / (ray_y * ray_y)) : 0);
		dda(env);
		print_wall(env, x);
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
	*dist_x = (*dist_x > 1000000000 ? 0 : *dist_x);
	*dist_y = (*dist_y > 1000000000 ? 0 : *dist_y);
}

void		dda(t_env *env)
{
	int		hit;
	double	dist_x;
	double	dist_y;

	env->map_x = (int)env->pos_x;
	env->map_y = (int)env->pos_y;
	init_dist(env, &dist_x, &dist_y);
	hit = 0;
	while (hit == 0)
	{
		if (dist_x < dist_y || dist_y == 0)
		{
			dist_x += env->distnext_x;
			env->map_x += env->step_x;
			env->side = 0;
		}
		else
		{
			dist_y += env->distnext_y;
			env->map_y += env->step_y;
			env->side = 1;
		}
		if (env->map[env->map_y][env->map_x + 1] > 0)
			hit = 1;
	}
}
