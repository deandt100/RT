/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 11:09:03 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/20 11:15:26 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static char		*set_temp(char *ptr, char c)
{
	char	*temp;

	temp = ft_strchr(ptr, c);
	if (temp == NULL)
	{
		ft_putstr_fd("File input error - Problem reading cone data\n", 2);
		exit(-1);
	}
	return (temp);
}

void			rotate_cone(t_env *env, int i)
{
	rotate_vec_x(CONES[i].rot.x, &CONES[i].v);
	rotate_vec_y(CONES[i].rot.y, &CONES[i].v);
	rotate_vec_z(CONES[i].rot.z, &CONES[i].v);
	CONES[i].shape.pos = CONES[i].p;
}

void			fill_cone(t_env *env, int fd)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < OBJ.num_cone)
	{
		if (*line != '#')
		{
			temp = line;
			temp = set_temp(++temp, 'R');
			set_vector(&CONES[i].rot, temp);
			temp = set_temp(temp, 'P');
			set_vector(&CONES[i].p, ++temp);
			temp = set_temp(++temp, 'V');
			set_vector(&CONES[i].v, ++temp);
			vector_norm(&CONES[i].v);
			rotate_cone(env, i);
			temp = set_temp(++temp, 'a');
			CONES[i].alpha = (((double)ft_atoi(++temp)) *  M_PI) / 180;
			temp = set_temp(++temp, 'm');
			CONES[i].shape.material = ft_atoi(++temp);
			i++;
		}
		free(line);
	}
}
