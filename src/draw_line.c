/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 15:22:07 by daviwel           #+#    #+#             */
/*   Updated: 2016/06/17 15:17:39 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_line(t_env *env, int x, t_col *col)
{
	t_coordint	pixel;
	t_col		flrsky;

	pixel.x = x;
	env->img.data = mlx_get_data_addr(env->img.img,
			&env->img.bpp, &env->img.s, &env->img.e);
	set_col(&flrsky, 102, 178, 255);
	pixel.y = 0;
	while (pixel.y < env->ray.draw_s)
	{
		mlx_image_put_pixel(env, &(env->img), pixel, &flrsky);
		pixel.y++;
	}
	pixel.y = env->ray.draw_s;
	while (pixel.y < env->ray.draw_e)
	{
		mlx_image_put_pixel(env, &(env->img), pixel, col);
		pixel.y++;
	}
	set_col(&flrsky, 64, 64, 64);
	pixel.y = env->ray.draw_e - 1;
	while (++pixel.y < WIN_Y)
		mlx_image_put_pixel(env, &(env->img), pixel, &flrsky);
}
