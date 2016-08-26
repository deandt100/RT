/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroener <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 08:57:43 by ggroener          #+#    #+#             */
/*   Updated: 2016/08/26 13:43:40 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector	ft_obj_vector(char *line)
{
	t_vector	vec;
	char		*tmp;

	vec = (t_vector){0, 0, 0};
	tmp = ft_strchr(line, ' ');
	vec.x = ft_atod(tmp);
	tmp = ft_strchr(&tmp[1], ' ');
	vec.y = ft_atod(tmp);
	tmp = ft_strchr(&tmp[1], ' ');
	vec.z = ft_atod(tmp);
	return (vec);
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

t_face		ft_face(char *line)
{
	t_face	face;
	char	*tmp;

	tmp = ft_strchr(line, ' ');
	face.v1 = ft_atoi(tmp) - 1;
	tmp = ft_strchr(&tmp[1], '/');
	while (*tmp == '/')
		tmp++;
	face.nor = ft_atoi(tmp) - 1;
	tmp = ft_strchr(tmp, ' ');
	face.v2 = ft_atoi(tmp) - 1;
	tmp = ft_strchr(&tmp[1], '/');
	while (*tmp == '/')
		tmp++;
	if (ft_atoi(tmp) - 1 != face.nor)
		exit(-1);
	tmp = ft_strchr(tmp, ' ');
	face.v3 = ft_atoi(tmp) - 1;
	tmp = ft_strchr(&tmp[1], '/');
	while (*tmp == '/')
		tmp++;
	if (ft_atoi(tmp) - 1 != face.nor)
		exit(-1);
	return (face);
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
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			obj->normals[(++obj->count.norms)] = ft_obj_vector(line);
		else if (line[0] == 'f' && line[1] == ' ')
			obj->faces[(++obj->count.faces)] = ft_face(line);
		free(line);
	}
	close(fd);
	
	//DEBUG
	int	i;
	//for (i = 0; i < obj->num_vecs; i++)
	//	print_vector("v", obj->vectors[i]);
	//for (i = 0; i < obj->num_norms; i++)
	//	print_vector("vn", obj->normals[i]);
	for (i = 0; i < obj->num_faces; i++)
		printf("%i\t%i\t%i\tN: %i\n",
			obj->faces[i].v1,
			obj->faces[i].v2,
			obj->faces[i].v3,
			obj->faces[i].nor);
	//END
}
