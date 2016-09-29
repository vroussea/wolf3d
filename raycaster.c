/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:29:18 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/29 15:40:13 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycaster(t_env *env)
{
	int		x;
	double	crtray;

	x = 0;
	while(x < env->sx)
	{
		currentray = 2 * x / (double)(env->sx) - 1;
		
		x++;
	}
}
