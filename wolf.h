/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:56:19 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/06 22:27:06 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"
# define ANGLE 0.66

typedef struct	s_pt
{
	int		x;
	int		y;
	int		col;
}				t_pt;

typedef	struct	s_env
{
	void	*mlx;
	void	*win;
	int		sx;
	int		sy;
	void	*img;
	char	*meml;
	int		sizel;
	int		**map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	int		smap;
	double	distnext_x;
	double	distnext_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	ray_x;
	double	ray_y;
}				t_env;

void			caller(t_env *env);
int				quit_funct(t_env *env);
int				key_funct(int keycode, t_env *env);
void			pixel(int x, int y, int col, t_env *env);
int				file_reader(char *file, int ***map);
void			minimap(t_env *env);
void			line(t_pt *pt1, t_pt *pt2, t_env *env);
int				start_loc(t_env *env, int ty, int tx);
void			raycaster(t_env *env);
void			dda(t_env *env);
int				test_map_closed(t_env *env);

#endif
