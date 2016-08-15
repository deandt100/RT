/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 09:29:51 by daviwel           #+#    #+#             */
/*   Updated: 2016/07/15 23:41:05 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		set_temp(int fd)
{
	char	*line;
	char	*temp;
	int		val;

	get_next_line(fd, &line);
	while (*line == '#')
	{
		free(line);
		get_next_line(fd, &line);
	}
	temp = ft_strchr(line, ':');
	if (temp == NULL)
	{
		ft_putstr_fd("File input error - primitive count not specified\n", 2);
		exit(-1);
	}
	temp++;
	val = ft_atoi(temp);
	free(line);
	return (val);
}

void	set_arrays(t_env *env, t_obj temp, int fd)
{
	OBJ.num_mats = set_temp(fd);
	OBJ.num_lights = set_temp(fd);
	OBJ.num_spheres = set_temp(fd);
	OBJ.num_tri = set_temp(fd);
	OBJ.num_cyl = set_temp(fd);
	OBJ.num_cone = set_temp(fd);
	val_types(env, temp);
	OBJ.mats = (t_material *)malloc(sizeof(t_material) *
			env->obj.num_mats);
	OBJ.lights = (t_light *)malloc(sizeof(t_light) * OBJ.num_lights);
	OBJ.spheres = (t_sphere *)malloc(sizeof(t_sphere)
			* OBJ.num_spheres);
	OBJ.triangles = (t_triangle*)malloc(sizeof(t_triangle) * OBJ.num_tri);
	OBJ.cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * OBJ.num_cyl);
	OBJ.cones = (t_cone*)malloc(sizeof(t_cone) * OBJ.num_cone);
}

void	init_obj(t_obj *obj)
{
	obj->num_mats = 0;
	obj->num_lights = 0;
	obj->num_spheres = 0;
	obj->num_tri = 0;
	obj->num_cyl = 0;
	obj->num_cone = 0;
}

/*
** Reads input from a scene file
*/

void	get_input(t_env *env, char *file)
{
	int		fd;
	int		fdc;
	t_obj	temp;

	fdc = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("Error reading file\n");
		exit(0);
	}
	init_obj(&temp);
	fdc = open(file, O_RDONLY);
	count_types(&temp, fdc);
	set_arrays(env, temp, fd);
	get_cam(env, fd);
	fill_materials(env, fd);
	fill_lights(env, fd);
	fill_spheres(env, fd);
	fill_triangles(env, fd);
	fill_cylinders(env, fd);
	fill_cone(env, fd);
	close(fd);
	close(fdc);
}
