/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 11:43:07 by oexall            #+#    #+#             */
/*   Updated: 2016/08/23 12:52:19 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector	ft_get_vector(char *line)
{
	t_vector	tmp;

	if (ft_strchr(line, 'x'))
		tmp.x = ft_atoi(&ft_strchr(line, 'x')[1]) * 1.0f;
	if (ft_strchr(line, 'y'))
		tmp.y = ft_atoi(&ft_strchr(line, 'y')[1]) * 1.0f;
	if (ft_strchr(line, 'z'))
		tmp.z = ft_atoi(&ft_strchr(line, 'z')[1]) * 1.0f;
	return (tmp);
}

void		ft_new_cam(t_env *env)
{
	CAM.rot = (t_vector){0, 0, 0};
	CAM.pos = (t_vector){0, 0, 0};
	CAM.dir = (t_vector){0, 0, 0};
	CAM.v_up = (t_vector){0, 0, 0};
}

void		ft_rotate_cam(t_env *env)
{
	rotate_vec_x(CAM.rot.x, &CAM.dir);
	rotate_vec_x(CAM.rot.x, &CAM.u);
	rotate_vec_x(CAM.rot.x, &CAM.pos);
	rotate_vec_y(CAM.rot.y, &CAM.dir);
	rotate_vec_y(CAM.rot.y, &CAM.u);
	rotate_vec_y(CAM.rot.y, &CAM.pos);
	rotate_vec_z(CAM.rot.z, &CAM.dir);
	rotate_vec_z(CAM.rot.z, &CAM.u);
	rotate_vec_z(CAM.rot.z, &CAM.pos);
}

void		ft_init_cam(t_env *env, t_vector rot)
{

	CAM.d = 2.1675;
	CAM.h = 18.0 * CAM.d / 35;
	CAM.w = CAM.h * ((double)WIN_X / (double)WIN_Y);
	CAM.n = vector_unit(vector_sub(CAM.pos, CAM.dir));
	print_vector("rotation : ", rot);
	rotate_vec_x(rot.x, &CAM.n);
	rotate_vec_y(rot.y, &CAM.n);
	rotate_vec_z(rot.z, &CAM.n);
	CAM.u = vector_unit(vector_cross(CAM.v_up, CAM.n));
	CAM.v = vector_cross(CAM.n, CAM.u);
	CAM.c = vector_sub(CAM.pos, vector_scale(CAM.d, CAM.n));
	CAM.l = vector_sub(CAM.c, vector_scale(CAM.w / 2.0, CAM.u));
	CAM.l = vector_add(CAM.l, vector_scale(CAM.h / 2.0, CAM.v));
}

void		ft_fill_camera(int fd, t_env *env)
{
	int		r;
	char	*line;
	
	r = 1;
	ft_new_cam(env);
	while (r && get_next_line(fd, &line))
	{
		if (*line == '#')
			r = 1;
		else if (ft_strchr(line, 'R') != NULL)
			CAM.rot = ft_get_vector(line);
		else if (ft_strchr(line, 'D') != NULL)
			CAM.dir = ft_get_vector(line);
		else if (ft_strchr(line, 'P') != NULL)
			CAM.pos = ft_get_vector(line);
		else if (ft_strchr(line, 'U') != NULL)
			CAM.v_up = ft_get_vector(line);
		else
			r = 0;
		free(line);
	}
//	ft_rotate_cam(env);
	ft_init_cam(env, CAM.rot);
	//DEBUG DEBUG
	/*print_vector("CAM ROT:", CAM.rot); printf("\n");
	print_vector("CAM DIR:", CAM.dir); printf("\n");
	print_vector("CAM POS:", CAM.pos); printf("\n");
	print_vector("CAM VUP:", CAM.v_up); printf("\n");*/
}
