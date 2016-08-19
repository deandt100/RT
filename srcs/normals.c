/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 08:53:57 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/19 11:37:17 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

/*
** Will get normal vector for cylinder based where p is the point of
** intersection.
*/

t_vector	get_cyl_normal(t_cylinder cyl, t_vector p)
{
	t_vector	proj;

	proj = vector_project(p, cyl.v);
	return (vector_dir(proj, p));
}

t_vector	get_cone_normal(t_cone cone, t_vector p)
{
	t_vector	v;
	t_vector	n;
	t_vector	p_par;
	t_vector	p_orth;
	t_vector	p_orth1;

//	vector_norm(&cone.v);
//	n = vector_sub(p, vector_project(p, cone.v));
	n = vector_dir(vector_project(p, cone.v), p); //normal
	vector_norm(&n);
	print_vector("n ;", n);
	print_vector("cone.v ;", cone.v);

	v = vector_cross(n, cone.v); //get v
	print_vector("v ;", v);
	p_par = vector_project(p, v); //p|| = (p, v)v
	print_vector("p_par ;", p_par);
	p_orth = vector_sub(p, p_par); //p⊥ = p − (p, v)v
	p_orth1 = vector_add(vector_scale(cos(cone.alpha * 0.01745329252), p_orth),
				vector_scale(sin(cone.alpha * 0.01745329252), vector_cross(v, p_orth)));
	//p⊥ = p⊥ cosθ + (a × p⊥)sinθ
	return (vector_add(p_orth1, p_par));//p'	= p⊥ + p||
//	return (vector_add(vector_add(vector_scale(cos(cone.alpha * 0.01745329252),p),
//				vector_scale(1 - cos(cone.alpha * 0.01745329252), vector_project(p, v))), vector_scale(sin(cone.alpha * 0.01745329252), vector_cross(v, p))));

}
