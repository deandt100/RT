/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_objs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 07:09:37 by oexall            #+#    #+#             */
/*   Updated: 2016/08/22 07:30:57 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void	ft_count_1(t_env *env, char *line)
{
	if (ft_strncmp(line, "MATERIAL", 8) == 0)
		OBJ.num_mats += 1;
	else if (ft_strncmp(line, "LIGHT", 5) == 0)
		OBJ.num_lights += 1;
	else if (ft_strncmp(line, "SPHERE", 6) == 0)
		OBJ.num_spheres += 1;
	else if (ft_strncmp(line, "TRIANGLE", 8) == 0)
		OBJ.num_tri += 1;
	else if (ft_strncmp(line, "CYLINDER", 8) == 0)
		OBJ.num_cyl += 1;
	else if (ft_strncmp(line, "CONE", 4) == 0)
		OBJ.num_cone += 1;
	//More shapes can be added below or in another function that runs after
	//this one.
}

void	ft_count_objs(t_env *env, char *file)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		exit(0);
	while (get_next_line(fd, &line))
	{
		if (*line != '#' && ft_strlen(line) > 0)
			ft_count_1(env, line);
		free(line);
	}
	close(fd);
	//DEBUG DEBUG
	ft_printf("MATERIALS\t=> %i\n", OBJ.num_mats);
	ft_printf("LIGHTS\t\t=> %i\n", OBJ.num_lights);
	ft_printf("SPHERE\t\t=> %i\n", OBJ.num_spheres);
	ft_printf("TRIANGLE\t=> %i\n", OBJ.num_tri);
	ft_printf("CYLINDER\t=> %i\n", OBJ.num_cyl);
	ft_printf("CONES\t\t=> %i\n", OBJ.num_cone);
}
