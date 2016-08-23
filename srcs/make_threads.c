/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 10:11:28 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/23 10:29:56 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	make_threads(t_env *env)
{
	t_rt_thread bounds[4];

	bounds[0] = (t_rt_thread){0, WIN_X, 0, WIN_Y / 4, env};
	bounds[1] = (t_rt_thread){0, WIN_X, WIN_Y / 4, WIN_Y / 4 * 2, env};
	bounds[2] = (t_rt_thread){0, WIN_X, WIN_Y / 4 * 2, WIN_Y / 4 * 3, env};
	bounds[3] = (t_rt_thread){0, WIN_X, WIN_Y / 4 * 3, WIN_Y, env};

	raytrace(bounds[0]);
	raytrace(bounds[1]);
	raytrace(bounds[2]);
	raytrace(bounds[3]);
	
}
