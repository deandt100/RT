/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroener <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 08:57:43 by ggroener          #+#    #+#             */
/*   Updated: 2016/08/26 10:24:22 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector	ft_obj_vector(char *line)
{
	(void)line;
	return ((t_vector){0, 0, 0});
}

void		create_obj_arrays(t_object *obj)
{
	obj->vectors = (t_vector *)malloc(sizeof(t_vector) * obj->num_vecs);
	obj->normals = (t_vector *)malloc(sizeof(t_vector) * obj->num_norms);
	obj->faces = (t_face *)malloc(sizeof(t_face) * obj->num_faces);
	obj->count.vecs = -1;
	obj->count.norms = -1;
	obj->count.faces = -1;
}

void		read_obj(t_object *obj)
{
	int		fd;
	char	*line;

	if (obj->path == NULL)
		exit(-1);
	ft_obj_vec_count(obj);
	create_obj_arrays(obj);
	if ((fd = open(ft_trim(obj->path), O_RDONLY)) == -1)
		exit(-1);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			obj->vectors[(++obj->count.vecs)] = ft_obj_vector(line);
		else if (line[0] == 'v' && line[1] == 'n')
			obj->normals[(++obj->count.norms)] = ft_obj_vector(line);
		free(line);
	}
	close(fd);
}
