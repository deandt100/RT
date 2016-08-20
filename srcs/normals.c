/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 08:53:57 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/20 15:08:22 by ddu-toit         ###   ########.fr       */
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
	t_vector	proj;
	t_vector	n;
	t_vector	p_par;
	t_vector	p_orth;
	t_vector	p_orth1;

	proj = vector_project(vector_sub(p, cone.p), cone.v);
	n = vector_unit(vector_sub(vector_sub(p, cone.p), proj));

	v = (vector_comp(vector_unit(vector_sub(proj, cone.p)), cone.v)) ?
		vector_unit(vector_cross(n, cone.v)) :  vector_unit(vector_cross(cone.v, n)); //get v
//	printf("\n");
//	print_vector("v :", v);
//	printf("	");
//	print_vector("n :", n);
//	printf("	");
	p_par = vector_unit(vector_project(n, v)); //p|| = (p, v)v
//	print_vector("par :", p_par);
//	printf("\n");
	p_orth = vector_sub(n, p_par); //p⊥ = p − (p, v)v

	p_orth1 = vector_add(vector_scale(cos(cone.alpha), p_orth),
				vector_scale(sin(cone.alpha), vector_cross(v, p_orth)));
	return (vector_add(p_orth1, p_par));//p'	= p⊥ + p||
}
