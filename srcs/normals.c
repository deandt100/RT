/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 08:53:57 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/18 14:48:00 by ddu-toit         ###   ########.fr       */
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
	return (vector_dir(&proj, &p));
}

t_vector	get_cone_normal(t_cone cone, t_vector p)
{
	t_vector	n;
	t_vector	u;
	t_vector	v;
	t_vector	p_par;
	t_vector	p_perp;

	n = vector_project(p, cone.v);
	p_par = n;
	n = vector_dir(&n, &p);
	u = vector_cross(&cone.v, &n);
	v = vector_cross(&u, &n);
	p_perp = vector_sub(&p, &p_par);
	p_perp = vector_scale(cos(cone.alpha), &p_perp);
	return (n);
}
