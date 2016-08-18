/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 08:31:19 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/16 11:09:18 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_shape
{
	double		dist;
	t_vector	pos;
	int			material;
}				t_shape;

typedef struct	s_sphere
{
	t_shape		shape;
	double		radius;
}				t_sphere;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_cam
{
	double		d;
	double		h;
	double		w;
	t_vector	pos;
	t_vector	dir;
	t_vector	v_up;
	t_vector	n;
	t_vector	u;
	t_vector	v;
	t_vector	c;
	t_vector	l;
}				t_cam;

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
	double		radius;
	t_shape		shape;
}				t_cylinder;

typedef struct	s_cone
{
	t_vector	p;
	t_vector	v;
	t_vector	rot;
	double		alpha;
	t_shape		shape;
}				t_cone;

double			vector_dot(t_vector *v1, t_vector *v2);

t_vector		new_vector(double x, double y, double z);

t_vector		vector_sub(t_vector *v1, t_vector *v2);

t_vector		vector_add(t_vector *v1, t_vector *v2);

t_vector		vector_scale(double c, t_vector *v);

t_vector		vector_cross(t_vector *v1, t_vector *v2);

t_vector		vector_div(t_vector *v1, t_vector *v2);

double			vector_dist(t_vector *v1, t_vector *v2);

t_vector		vector_norm(t_vector *v);

t_vector		vector_dir(t_vector *s, t_vector *t);

t_vector		vector_div(t_vector *v1, t_vector *v2);

t_vector		vector_unit(t_vector v);

/*
** Rotation
*/

void			rotate_vec_x(float angle, t_vector *v);

void			rotate_vec_y(float angle, t_vector *v);

void			rotate_vec_z(float angle, t_vector *v);

void			rotate_tri(t_triangle *tri);

#endif
