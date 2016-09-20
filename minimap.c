/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 15:59:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 19:14:05 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

void	minimap(t_env *env)
{
	int		i;
	int		j;

	i = 11;
	while (env->map[(int)(i / 10) - 1] != NULL)
	{
		j = 11;
		while ((int)(j / 10) - 1 < env->map[0][0])
		{
			if (i % 10 != 0 && j % 10 != 0)
			{
				if (env->map[(int)(i / 10) - 1][(int)(j / 10)] == 1)
					pixel(j, i, 0x08FFFFFF, env);
				else
					pixel(j, i, 0x08666666, env);
			}
			j++;
		}
		i++;
	}
}
