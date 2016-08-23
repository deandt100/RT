/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 06:56:36 by oexall            #+#    #+#             */
/*   Updated: 2016/08/23 11:51:47 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	ft_init_arrays(t_env *env)
{
	ft_printf("==INITIALIZING ARRAYS==\n"); //DEBUG
	OBJ.mats = (t_material *)malloc(sizeof(t_material) * OBJ.num_mats);
	OBJ.lights = (t_light *)malloc(sizeof(t_light) * OBJ.num_lights);
	OBJ.spheres = (t_sphere *)malloc(sizeof(t_sphere) * OBJ.num_spheres);
	OBJ.triangles = (t_triangle *)malloc(sizeof(t_triangle) * OBJ.num_tri);
	OBJ.cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * OBJ.num_cyl);
	OBJ.cones = (t_cone *)malloc(sizeof(t_cone) * OBJ.num_cone);
	//Initialize more shape below as we go along
}

void	ft_init_env(t_env *env)
{
	env->ambient_level = 0;
	env->ref_level = 0;
	OBJ.num_mats = 0;
	OBJ.num_lights = 0;
	OBJ.num_spheres = 0;
	OBJ.num_tri = 0;
	OBJ.num_cyl = 0;
	OBJ.num_cone = 0;
	env->count.mats = -1;
	env->count.lights = -1;
	env->count.spheres = -1;
	env->count.triangles = -1;
	env->count.cylinders = -1;
	env->count.cones = -1;
}

void	ft_check_1(int fd, t_env *env, char *line)
{
	if (ft_strncmp(line, "CAMERA", 6) == 0)
		ft_fill_camera(fd, env);
	else if (ft_strncmp(line, "REFLECTION", 10) == 0 && ft_strchr(line, ':'))
		env->ref_level = ft_atoi(&ft_strchr(line, ':')[1]);
	else if (ft_strncmp(line, "AMBIENT", 7) == 0 && ft_strchr(line, ':'))
		env->ambient_level = (ft_atoi(&ft_strchr(line, ':')[1]) * 1.0f) / 100;
	else if (ft_strncmp(line, "MATERIAL", 8) == 0)
		ft_fill_material(fd, env);
	else if (ft_strncmp(line, "LIGHT", 5) == 0)
		ft_fill_light(fd, env);
	else if (ft_strncmp(line, "SPHERE", 6) == 0)
		ft_fill_sphere(fd, env);
	else if (ft_strncmp(line, "TRIANGLE", 8) == 0)
		ft_fill_triangle(fd, env);
	else if (ft_strncmp(line, "CONE", 4) == 0)
		ft_fill_cone(fd, env);
	else if (ft_strncmp(line, "CYLINDER", 8) == 0)
		ft_fill_cylinder(fd, env);
	//ADD more checks below
}

void	ft_get_input(t_env *env, char *file)
{
	int		fd;
	char	*line;

	printf("READING\n"); //DEBUG
	ft_init_env(env);
	ft_count_objs(env, file);
	ft_init_arrays(env);
	if ((fd = open(file, O_RDONLY)) == -1)
		exit(-1);
	while (get_next_line(fd, &line))
	{
		if (line && *line != '#' && ft_strlen(line) > 0)
			ft_check_1(fd, env, line);
		free(line);
	}
	close(fd);
	//DEBUG
	printf("REFLECTION: %i\n", env->ref_level);
	printf("AMBIENCE: %f\n", env->ambient_level);
	printf("END OF READ\n");
}
