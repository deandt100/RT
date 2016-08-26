/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 06:59:08 by oexall            #+#    #+#             */
/*   Updated: 2016/08/26 10:03:35 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void	ft_init_object(t_object *obj)
{
	obj->path = NULL;
	obj->pos = (t_vector){0, 0, 0};
	obj->material = 0;
	obj->num_vecs = 0;
	obj->vectors = NULL;
	obj->num_norms = 0;
	obj->normals = NULL;
	obj->num_faces = 0;
	obj->faces = NULL;
}

int		ft_get_obj(char *line, t_env *env, int i)
{
	if (*line == '#')
		return (1);
	else if (ft_strchr(line, 'F'))
		OBJ.objects[i].path = ft_strdup(&ft_strchr(line, ':')[1]); //FREE THIS
	else if (ft_strchr(line, 'P'))
		OBJ.objects[i].pos = ft_get_vector(line);
	else if (ft_strchr(line, 'M'))
		OBJ.objects[i].material = ft_atoi(&ft_strchr(line, ':')[1]);
	else
		return (0);
	return (1);
}

void	ft_fill_object(int fd, t_env *env)
{
	int		r;
	int		i;
	char	*line;

	i = (++env->count.objects);
	ft_init_object(&OBJ.objects[i]);
	r = 1;
	while (r && get_next_line(fd, &line))
	{
		r = ft_get_obj(line, env, i);
		free(line);
	}
	if (ft_val_mat(env, OBJ.objects[i].material, "OBJECT") == -1)
		exit(-1);
	read_obj(&OBJ.objects[i]);
	//DEBUG
	/*printf("OBJECT:\n");
	printf("Path: %s\n", OBJ.objects[i].path);
	print_vector("POS:", OBJ.objects[i].pos);
	printf("MAT: %i\n", OBJ.objects[i].material);*/
}
