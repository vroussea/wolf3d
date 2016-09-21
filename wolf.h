/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:56:19 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/21 21:14:59 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"

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
	int		**map;
	int		sizel;
	int		pos_x;
	int		pos_y;
	double	move[2];
	double	angle;
	int		smap;
}				t_env;

void			caller(t_env *env);
int				quit_funct(t_env *env);
int				key_funct(int keycode, t_env *env);
//void			text(t_env *env);
//void			special_text(t_env *env);
//void			hud_text(t_env *env);
void			pixel(int x, int y, int col, t_env *env);
int				file_reader(char *file, int ***map);
void			minimap(t_env *env);
void			line(t_pt pt1, t_pt pt2, t_env *env);
int				start_loc(t_env *env, int ti, int tj);

#endif
