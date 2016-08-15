/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 11:09:03 by daviwel           #+#    #+#             */
/*   Updated: 2016/07/15 21:13:28 by daviwel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static char		*set_temp(char *ptr, char c)
{
	char	*temp;

	temp = ft_strchr(ptr, c);
	if (temp == NULL)
	{
		ft_putstr_fd("File input error - Problem reading cylinder data\n", 2);
		exit(-1);
	}
	return (temp);
}

void			rotate_cyl(t_env *env, int i)
{
	rotate_vec_x(CYLINDERS[i].rot.x, &CYLINDERS[i].v);
	rotate_vec_x(CYLINDERS[i].rot.x, &CYLINDERS[i].p);
	rotate_vec_y(CYLINDERS[i].rot.y, &CYLINDERS[i].v);
	rotate_vec_y(CYLINDERS[i].rot.y, &CYLINDERS[i].p);
	rotate_vec_z(CYLINDERS[i].rot.z, &CYLINDERS[i].v);
	rotate_vec_z(CYLINDERS[i].rot.z, &CYLINDERS[i].p);
	vector_norm(&CYLINDERS[i].v);
	CYLINDERS[i].shape.pos = CYLINDERS[i].p;
}

void			fill_cylinders(t_env *env, int fd)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < env->obj.num_cyl)
	{
		if (*line != '#')
		{
			temp = line;
			temp = set_temp(++temp, 'R');
			set_vector(&CYLINDERS[i].rot, temp);
			temp = set_temp(temp, 'P');
			set_vector(&CYLINDERS[i].p, ++temp);
			temp = set_temp(temp, 'V');
			set_vector(&CYLINDERS[i].v, ++temp);
			rotate_cyl(env, i);
			temp = set_temp(++temp, 'r');
			CYLINDERS[i].radius = ft_atoi(++temp);
			temp = set_temp(++temp, 'm');
			CYLINDERS[i].shape.material = ft_atoi(++temp);
			i++;
		}
		free(line);
	}
}
