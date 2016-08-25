/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 14:14:34 by oexall            #+#    #+#             */
/*   Updated: 2016/08/25 14:49:03 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct	s_face
{
	int			vec_1;
	int			vec_2;
	int			vec_3;
	int			nor;
}				t_face;

typedef struct	s_object
{
	t_vector	*vectors;
	int			num_vecs;
	t_vector	*normals;
	int			num_norms;
	t_face		*faces;
	int			num_faces;
}				t_object;

#endif
