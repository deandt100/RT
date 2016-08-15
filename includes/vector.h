/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 08:31:19 by daviwel           #+#    #+#             */
/*   Updated: 2016/07/15 23:00:51 by daviwel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_shape
{
	float		dist;
	t_vector	pos;
	int			material;
}				t_shape;

typedef struct	s_sphere
{
	t_shape		shape;
	float		radius;
}				t_sphere;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_triangle
{
	t_shape		shape;
	t_vector	normal;
	t_vector	rot;
	t_vector	v1;
	t_vector	v2;
	t_vector	v3;
}				t_triangle;

typedef struct	s_cylinder
{
	t_vector	p;
	t_vector	v;
	t_vector	rot;
	float		radius;
	t_shape		shape;
}				t_cylinder;

typedef struct	s_cone
{
	t_vector	p;
	t_vector	v;
	t_vector	rot;
	float		alpha;
	t_shape		shape;
}				t_cone;

float			vector_dot(t_vector *v1, t_vector *v2);

t_vector		new_vector(float x, float y, float z);

t_vector		vector_sub(t_vector *v1, t_vector *v2);

t_vector		vector_add(t_vector *v1, t_vector *v2);

t_vector		vector_scale(float c, t_vector *v);

t_vector		vector_cross(t_vector *v1, t_vector *v2);

t_vector		vector_div(t_vector *v1, t_vector *v2);

float			vector_dist(t_vector *v1, t_vector *v2);

t_vector		vector_norm(t_vector *v);

/*
** Rotation
*/

void			rotate_vec_x(float angle, t_vector *v);

void			rotate_vec_y(float angle, t_vector *v);

void			rotate_vec_z(float angle, t_vector *v);

void			rotate_tri(t_triangle *tri);

#endif
