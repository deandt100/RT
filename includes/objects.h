/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 14:14:34 by oexall            #+#    #+#             */
/*   Updated: 2016/08/26 09:30:32 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct	s_face
{
	int			v1;
	int			v2;
	int			v3;
	int			nor;
}				t_face;

typedef struct	s_object
{
	char		*path;
	t_vector	pos;
	int			material;
	double		dist;
	t_vector	*vectors;
	int			num_vecs;
	t_vector	*normals;
	int			num_norms;
	t_face		*faces;
	int			num_faces;
}				t_object;

#endif
