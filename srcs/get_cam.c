/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 11:09:03 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/18 11:07:38 by ddu-toit         ###   ########.fr       */
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
	rotate_vec_x(OBJ.cam_rot.x, &CAM.dir);
	rotate_vec_y(OBJ.cam_rot.y, &CAM.dir);
	rotate_vec_z(OBJ.cam_rot.z, &CAM.dir);
}

void			init_cam(t_env *env)
{
	t_vector	uw2;
	t_vector	vh2;

	CAM.d = 2.1675;
//	CAM.d = WIN_Y / (2.0 * (double)tan(VFOV / 2));
//	CAM.h = (double)tan(VFOV / 2) * CAM.d;
	CAM.h = 18.0 * CAM.d / 35;
	printf("h = %F\n", CAM.h);
	CAM.w = CAM.h * ((double)WIN_X / (double)WIN_Y);
	CAM.v_up = new_vector(0.0, 0.0, 1.0); //to change to file input
	print_vector("v_up : ", CAM.v_up);

	CAM.n = vector_sub(&CAM.pos, &CAM.dir); //n = (eye – COI) / | eye – COI| 
	print_vector("n : ", CAM.n);
	vector_norm(&CAM.n);
	print_vector("n : ", CAM.n);
	print_vector("pos : ", CAM.pos);
	print_vector("u : ", CAM.u);
	CAM.u = vector_cross(&CAM.v_up, &CAM.n);
	print_vector("u : ", CAM.u);
	vector_norm(&CAM.u);

	CAM.v = vector_cross(&CAM.n, &CAM.u);
	print_vector("v : ", CAM.v);

	CAM.c = vector_scale(CAM.d, &CAM.n);
	CAM.c = vector_sub(&CAM.pos, &CAM.c); //e - n * d

	uw2 = vector_scale(CAM.w / 2.0, &CAM.u);
	vh2 = vector_scale(CAM.h / 2.0, &CAM.v);
	CAM.l = vector_sub(&CAM.c, &uw2);
	CAM.l =  vector_add(&CAM.l, &vh2);//C - u * W/2 - v * H/2
	print_vector("L : ", CAM.l);
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
			print_vector("rotation : ", OBJ.cam_rot);
			temp = set_temp(temp, 'D');
			set_vector(&CAM.dir, temp);
			vector_norm(&CAM.dir);
			temp = set_temp(temp, 'P');
			set_vector(&CAM.pos, ++temp);
			i++;
		}
		free(line);
	}
	print_vector("cam dir vector : ", CAM.dir);
	rotate_cam(env);
	print_vector("cam dir vector : ", CAM.dir);
	init_cam(env);
}
