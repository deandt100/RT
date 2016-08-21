/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 08:53:57 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/21 09:47:55 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

/*
** Will get normal vector for cylinder where p is the point of
** intersection.
*/

t_vector	get_cyl_normal(t_cylinder cyl, t_vector p)
{
	t_vector	proj;

	proj = vector_project(p, cyl.v);
	return (vector_dir(proj, p));
}

/*
** Will get normal vector for cone where p is the point of
** intersection.
*/

t_vector	get_cone_normal(t_cone cone, t_vector p)
{
	t_vector	v;
//	t_vector	proj;
	t_vector	n;
	t_vector	p_par;
	t_vector	p_orth;

//	proj = vector_project(vector_sub(p, cone.p), cone.v);
	n = vector_unit(vector_sub(vector_sub(p, cone.p),
				vector_project(vector_sub(p, cone.p), cone.v)));
	v = (vector_comp(vector_dir(
		vector_project(vector_unit(p), cone.v), cone.p), cone.v)) ?
		vector_unit(vector_cross(n, cone.v)) :
		vector_unit(vector_cross(cone.v, n));
	p_par = vector_unit(vector_project(n, v));
	p_orth = vector_sub(n, p_par);
	p_orth = vector_add(vector_scale(cos(cone.alpha), p_orth),
		vector_scale(sin(cone.alpha), vector_cross(v, p_orth)));
	return (vector_add(p_orth, p_par));
}
