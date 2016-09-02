/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 08:59:41 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/09/02 13:10:11 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

typedef struct	s_col
{
	float	r;
	float	g;
	float	b;
}				t_col;

typedef struct	s_material
{
	double		refraction;
	t_col		diffuse;
	double		reflection;
	double		specular;
}				t_material;

void			set_col(t_col *col, float r, float g, float b);

#endif
