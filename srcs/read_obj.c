/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroener <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 08:57:43 by ggroener          #+#    #+#             */
/*   Updated: 2016/08/26 10:10:44 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		create_obj_arrays(t_object *obj)
{
	obj->vectors = (t_vector *)malloc(sizeof(t_vector) * obj->num_vecs);
	obj->normals = (t_vector *)malloc(sizeof(t_vector) * obj->num_norms);
	obj->faces = (t_face *)malloc(sizeof(t_face) * obj->num_faces);
}

void		read_obj(t_object *obj)
{
	if (obj->path == NULL)
		exit(-1);
	ft_obj_vec_count(obj);
	create_obj_arrays(obj);
}
