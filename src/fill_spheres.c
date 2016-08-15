/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 11:09:03 by daviwel           #+#    #+#             */
/*   Updated: 2016/07/11 12:53:59 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static char		*set_temp(char *ptr, char c)
{
	char	*temp;

	temp = ft_strchr(ptr, c);
	if (temp == NULL)
	{
		ft_putstr_fd("File input error - Problem reading sphere data\n", 2);
		exit(-1);
	}
	return (temp);
}

void			fill_spheres(t_env *env, int fd)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < env->obj.num_spheres)
	{
		if (*line != '#')
		{
			temp = line;
			temp = set_temp(temp, 'x');
			env->obj.spheres[i].shape.pos.x = ft_atoi(++temp);
			temp = set_temp(line, 'y');
			env->obj.spheres[i].shape.pos.y = ft_atoi(++temp);
			temp = set_temp(++temp, 'z');
			env->obj.spheres[i].shape.pos.z = ft_atoi(++temp);
			temp = set_temp(++temp, 'r');
			env->obj.spheres[i].radius = ft_atoi(++temp);
			temp = set_temp(++temp, 'm');
			env->obj.spheres[i].shape.material = ft_atoi(++temp);
			i++;
		}
		free(line);
	}
}
