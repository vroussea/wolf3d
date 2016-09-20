/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 18:59:06 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 21:07:37 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	pixel(int x, int y, int col, t_env *env)
{
	if (x > 0 && x < env->sx && y > 0 && y < env->sy)
		ft_memcpy(&env->meml[(x - 1) * 4 + (y - 1) * env->sizel], &col, 4);
}
