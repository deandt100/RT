/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 10:03:23 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/07/07 10:05:14 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** Extract material information from file.
*/

static char	*set_temp(char *ptr, char c)
{
	char *temp;

	temp = ft_strchr(ptr, c);
	if (temp == NULL)
	{
		ft_putstr_fd("File input error - Problem reading material data\n", 2);
		exit(-1);
	}
	return (temp);
}

static void	set_material(t_env *env, char *temp, int i)
{
	temp = set_temp(temp, 'r');
	env->obj.mats[i].diffuse.r = 1.0f * ft_atoi(++temp);
	if (env->obj.mats[i].diffuse.r != 0)
		env->obj.mats[i].diffuse.r /= 255;
	temp = set_temp(++temp, 'g');
	env->obj.mats[i].diffuse.g = 1.0f * ft_atoi(++temp);
	if (env->obj.mats[i].diffuse.g != 0)
		env->obj.mats[i].diffuse.g /= 255;
	temp = set_temp(++temp, 'b');
	env->obj.mats[i].diffuse.b = 1.0f * ft_atoi(++temp);
	if (env->obj.mats[i].diffuse.b != 0)
		env->obj.mats[i].diffuse.b /= 255;
	temp = ft_strchr(++temp, '*');
	env->obj.mats[i].reflection = 1.0f * ft_atoi(++temp);
	if (env->obj.mats[i].reflection != 0)
		env->obj.mats[i].reflection /= 10.0f;
}

void		fill_materials(t_env *env, int fd)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < env->obj.num_mats)
	{
		if (*line != '#')
		{
			temp = line;
			set_material(env, temp, i);
			i++;
		}
		free(line);
	}
}
