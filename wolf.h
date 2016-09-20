/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:56:19 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 21:13:51 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"

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

#endif
