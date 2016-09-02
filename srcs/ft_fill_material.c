/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 08:42:14 by oexall            #+#    #+#             */
/*   Updated: 2016/09/02 13:35:46 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		ft_get_value(char *line)
{
	int	tmp;

	tmp = 0;
	if (ft_strchr(line, ':') != NULL)
		tmp = ft_atoi(&ft_strchr(line, ':')[1]);
	return (tmp);
}

void	ft_init_material(t_material *mat)
{
	set_col(&mat->diffuse, 0, 0, 0);
	mat->reflection = 0;
	mat->specular = 0;
	mat->refraction = 0;
}

int		ft_get_material(char *line, t_env *env, int obj)
{
	if (ft_strchr(line, 'R') != NULL)
		OBJ.mats[obj].diffuse.r = (ft_get_value(line) * 1.0f) / 255;
	else if (ft_strchr(line, 'G') != NULL)
		OBJ.mats[obj].diffuse.g = (ft_get_value(line) / 1.0f) / 255;
	else if (ft_strchr(line, 'B') != NULL)
		OBJ.mats[obj].diffuse.b = (ft_get_value(line) / 1.0f) / 255;
	else if (ft_strchr(line, 'S') != NULL)
		OBJ.mats[obj].specular = (ft_get_value(line) * 1.0f) / 10.0f;
	else if (ft_strchr(line, '*') != NULL)
		OBJ.mats[obj].reflection = (ft_get_value(line) * 1.0f) / 10.0f;
	else if (ft_strchr(line, '%') != NULL && ft_strchr(line, ':'))
		OBJ.mats[obj].refraction = ft_atod(&ft_strchr(line, ':')[1]);
	else
		return (0);
	return (1);
}

void	ft_fill_material(int fd, t_env *env)
{
	int		r;
	int		i;
	char	*line;

	i = (++env->count.mats);
	ft_init_material(&OBJ.mats[i]);
	r = 1;
	while (r && get_next_line(fd, &line))
	{
		r = ft_get_material(line, env, i);
		free(line);
	}
}
