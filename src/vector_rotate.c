/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 07:50:46 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/07/15 16:09:13 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	rotate_vec_x(float angle, t_vector *v)
{
	float	y1;
	float	z1;

	angle = angle * 0.01745329252;
	z1 = v->z * cos(angle) - v->y * sin(angle);
	y1 = v->y * cos(angle) + v->z * sin(angle);
	v->y = y1;
	v->z = z1;
}

void	rotate_vec_y(float angle, t_vector *v)
{
	float	x1;
	float	z1;

	angle = angle * 0.01745329252;
	z1 = v->z * cos(angle) + v->x * sin(angle);
	x1 = v->x * cos(angle) - v->z * sin(angle);
	v->x = x1;
	v->z = z1;
}

void	rotate_vec_z(float angle, t_vector *v)
{
	float	x1;
	float	y1;

	angle = angle * 0.01745329252;
	y1 = v->y * cos(angle) - v->x * sin(angle);
	x1 = v->y * sin(angle) + v->x * cos(angle);
	v->x = x1;
	v->y = y1;
}
