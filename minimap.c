/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:59:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 21:20:30 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

/*static void	beta_char(t_env *env)
{

}*/

static void	pixel_grid(t_env *env, int i, int j)
{
	int	size;

	size = env->smap;
	if (i % size != 0 && j % size != 0)
	{
		if (env->map[(int)((i - size) / size)][(int)(j / size)] == 1)
			pixel(j - (size - 10), i - (size - 10), ((i + j) % 2 == 0 ? 0x08FFFFFF : 0x08333333), env);
		else
			pixel(j - (size - 10), i - (size - 10), ((i + j) % 2 == 0 ? 0x08333333 : 0x08666666), env);
	}
}

void		minimap(t_env *env)
{
	int		i;
	int		j;
	int		size;

	size = env->smap;
	i = 1 + size;
	while (env->map[(int)((i - size) / size)] != NULL)
	{
		j = 1 + size;
		while ((int)((j++ - size) / size) < env->map[0][0])
			pixel_grid(env, i, (j - 1));
		i++;
	}
//	beta_char(env);
}
