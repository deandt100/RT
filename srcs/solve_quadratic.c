/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 23:27:50 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/22 15:32:39 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int	solve_quadratic(t_ray_sphere *rs, double *t)
{
	rs->t0 = (-rs->b - sqrt(rs->discr)) / (2 * rs->a);
	rs->t1 = (-rs->b + sqrt(rs->discr)) / (2 * rs->a);
	if (rs->t0 > rs->t1 && rs->t1 > 0.0F)
		rs->t0 = rs->t1;
	if ((rs->t0 > EPSILON) && (rs->t0 < *t))
	{
		*t = rs->t0;
		return (1);
	}
	else
		return (0);
}

int	in_limit(double t, t_cylinder *cyl, t_ray *ray)
{
	t_vector	p;

	if (cyl->cap_hit)
		return (1);
	p = vector_add(ray->start, vector_scale(t, ray->dir));
	return (vector_dot(cyl->v, vector_sub(p, cyl->p)) > 0.0F
			&& vector_dot(cyl->v, vector_sub(p, cyl->lim)) < 0.0F);
}

void	get_cyl_caps(t_ray *ray, t_cylinder *cyl, double *t_top, double *t_bot)
{
	//double	t_top;
	//double	t_bot;
	t_vector	n_top;
	t_vector	n_bot;
	t_plane		temp;

	n_top = cyl->v;
	n_bot = vector_sub((t_vector){0.0F, 0.0F, 0.0F}, cyl->v);

	temp.rot = n_top;
	temp.shape.pos = cyl->lim;
	if (intersect_ray_plane(ray, &temp, t_top) == 0)
		*t_top = 0.0F;

	temp.rot = n_bot;
	temp.shape.pos = cyl->p;
	if (intersect_ray_plane(ray , &temp, t_bot) == 0)
		*t_bot = 0.0F;
}

int	solve_quadratic_cylinder(t_ray *ray, t_cylinder *cyl,
	t_ray_sphere *rs, double *t)
{
	double	temp;

	temp = *t;
	cyl->bot = vector_scale(cyl->scale,
					vector_sub((t_vector){0, 0, 0}, cyl->v));
	cyl->top = vector_scale(cyl->scale, cyl->v);
	if (solve_quadratic(rs, &temp) == 0)
			return (0);
	t_vector p = vector_add(ray->start, vector_scale(temp, ray->dir));
	if (cyl->inf == 0 && vector_dot(cyl->v, vector_sub(p, cyl->bot)) > 0
		&& vector_dot(cyl->v, vector_sub(p, cyl->top)) < 0)
	{
		*t = temp;
		return (1);
	}
	if (cyl->inf == 1)
		*t = temp;
	return (cyl->inf);
}

int	solve_quadratic_cone(t_ray *ray, t_cone *cone,
	t_ray_sphere *rs, double *t)
{
	double	temp;

	temp = *t;
	if (cone->type == 0)
	{
		cone->bot = cone->p;
		cone->top = vector_add(vector_scale(cone->scale, cone->v), cone->p);
	}
	else
	{
		cone->bot = vector_add(
			vector_scale(cone->scale / 2, vector_sub((t_vector){0, 0, 0}, cone->v)), cone->p);
		cone->top = vector_add(vector_scale(cone->scale / 2, cone->v), cone->p);
	}
	if (solve_quadratic(rs, &temp) == 0)
			return (0);
	t_vector p = vector_add(ray->start, vector_scale(temp, ray->dir));
	if (cone->inf == 0 && vector_dot(cone->v, vector_sub(p, cone->bot)) > 0
		&& vector_dot(cone->v, vector_sub(p, cone->top)) < 0)
	{
		*t = temp;
		return (1);
	}
	if (cone->inf == 1)
		*t = temp;
	return (cone->inf);
}

/*
int	solve_quadratic_cylinder(t_ray *ray, t_cylinder *cyl, t_ray_sphere *rs, double *t)
{
	int			i;
	double		tr;
	double		t_bot;
	double		t_top;
	t_vector	p;

	i = 0;
	rs->t0 = (-rs->b - sqrt(rs->discr)) / (2 * rs->a);
	rs->t1 = (-rs->b + sqrt(rs->discr)) / (2 * rs->a);
	get_cyl_caps(ray, cyl, &t_top, &t_bot);
	
	p  = vector_add(ray->start, vector_scale(t_bot, ray->dir));
	if (vector_dot(vector_sub(p, cyl->p), vector_sub(p, cyl->p)) > cyl->radius * cyl->radius)
		t_bot = 20000.0F;
	p  = vector_add(ray->start, vector_scale(t_top, ray->dir));
	if (vector_dot(vector_sub(p, cyl->lim), vector_sub(p, cyl->lim)) > cyl->radius * cyl->radius)
		t_bot = 20000.0F;
	printf("t0 %f t1 %f\n", rs->t0, rs->t1);
	printf("bot %f top %f\n", t_bot, t_top);
	cyl->cap_hit = 0;
	if (rs->t0 > 0.0F && rs->t0 < rs->t1 && rs->t0 < t_bot && rs->t0 < t_top)
		tr = rs->t0;
	else if (rs->t1 > 0.0F && rs->t1 < rs->t0 && rs->t1 < t_bot && rs->t1 < t_top)
		tr = rs->t1;
	else if (t_top > 0.0F && t_top < rs->t0 && t_top < rs->t1 && t_top < t_bot)
	{
		tr = t_top;
		cyl->cap_hit = 1;
	}
	else if (t_bot > 0.0F && t_bot < rs->t0 && t_bot < rs->t1 && t_bot < t_top)
	{
		tr = t_top;
		cyl->cap_hit = 2;
	}
	else
		tr = -1.0F;
	printf("tr %f\n in lim = %d\n", tr, in_limit(tr , cyl, ray));
	if (tr > EPSILON && tr < *t && in_limit(tr , cyl, ray))
	{
		*t = tr;
		//exit(1);
		return (1);
	}
	else
		return (0);
}*/