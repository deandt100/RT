/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 08:51:30 by oexall            #+#    #+#             */
/*   Updated: 2016/08/26 15:41:27 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

/*int		intersect_ray_obj(t_ray *ray, t_object *obj, double *t, int face)
{
	t_ray_tri	r;

	r.e1 = vector_sub(obj->vectors[obj->faces[face].v2],
			obj->vectors[obj->faces[face].v1]);
	r.e2 = vector_sub(obj->vectors[obj->faces[face].v3],
			obj->vectors[obj->faces[face].v1]);
	r.s1 = vector_cross(ray->dir, r.e2);
	r.d = vector_dot(r.e1, r.s1);
	if (r.d > -EPSILON && r.d < EPSILON)
		return (0);
	r.inv_d = 1 / r.d;
	r.s2 = vector_sub(ray->start, obj->vectors[obj->faces[face].v1]);
	r.u = vector_dot(r.s2, r.s1) * r.inv_d;
	if (r.u < EPSILON || r.u > 1)
		return (0);
	r.s3 = vector_cross(r.s2, r.e1);
	r.v = vector_dot(ray->dir, r.s3) * r.inv_d;
	if (r.v < 0 || (r.u + r.v) > 1)
		return (0);
	r.tmp = vector_dot(r.e2, r.s3) * r.inv_d;
	if (r.tmp < EPSILON)
		return (0);
	*t = r.tmp - 0.05F;
//	obj->normals[obj->faces[face].nor] = vector_cross(r.e1, r.e2);
	return (1);
}*/

void	empty_others(t_env *env)
{
	OBJ.cur_cone = -1;
	OBJ.cur_sphere = -1;
	OBJ.cur_tri = -1;
	OBJ.cur_cyl = -1;
	OBJ.cur_plane = -1;
}

void	set_val_object(t_env *env, double t, t_ray ray)
{
	OBJ.new_start = vector_add(ray.start, vector_scale(t, ray.dir));
	OBJ.normal = OBJ.objects[OBJ.cur_object[0]].faces[OBJ.cur_object[1]].normal;
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), OBJ.normal);
	vector_norm(&OBJ.normal);
	if (vector_dot(ray.dir, OBJ.normal) > 0.0F)
		OBJ.normal = vector_sub((t_vector){0, 0, 0}, OBJ.normal);
	OBJ.cur_mat = OBJ.mats[OBJ.objects[OBJ.cur_object[0]].material];
}

void	gi_object(t_env *env, t_ray *ray, double *t, double *ref_dist)
{
	int			i;
	int			j;
	double		t6;
	t_vector	n;

	t6 = *t;
	i = -1;
	OBJ.cur_object[0] = -1;
	OBJ.cur_object[1] = -1;
	while (++i < OBJ.num_objects)
	{
		j = -1;
		while (++j < OBJ.objects[i].num_faces)
			if (intersect_ray_tri(ray, &OBJ.objects[i].faces[j], &t6, &n))
			{
				OBJ.objects[i].faces[j].shape.dist = vector_dist(vector_add(
					ray->start, vector_scale(t6, ray->dir)), ray->start);
				if (OBJ.objects[i].faces[j].shape.dist < *ref_dist)
				{
					*t = t6;
					*ref_dist = OBJ.objects[i].faces[j].shape.dist;
					OBJ.cur_object[0] = i;
					OBJ.cur_object[1] = j;
					OBJ.objects[i].faces[j].normal = n;
					empty_others(env);
				}
			}
	}
}
