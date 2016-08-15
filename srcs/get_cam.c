/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 11:09:03 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/07/15 23:42:30 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static char		*set_temp(char *ptr, char c)
{
	char	*temp;

	temp = ft_strchr(ptr, c);
	if (temp == NULL)
	{
		ft_putstr_fd("File input error - Problem reading camera data\n", 2);
		exit(-1);
	}
	return (temp);
}

void			rotate_cam(t_env *env)
{
	rotate_vec_x(OBJ.cam_rot.x, &OBJ.cam_dir);
	rotate_vec_y(OBJ.cam_rot.y, &OBJ.cam_dir);
	rotate_vec_z(OBJ.cam_rot.z, &OBJ.cam_dir);
}

void			get_cam(t_env *env, int fd)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < 1)
	{
		if (*line != '#')
		{
			temp = line;
			temp = set_temp(++temp, 'R');
			set_vector(&OBJ.cam_rot, temp);
			temp = set_temp(temp, 'D');
			set_vector(&OBJ.cam_dir, temp);
			temp = set_temp(temp, 'P');
			set_vector(&OBJ.cam_s, ++temp);
			rotate_cam(env);
			i++;
		}
		free(line);
	}
}
