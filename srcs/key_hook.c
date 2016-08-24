/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 07:35:04 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/24 12:10:23 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	re_render(t_env *env)
{
	ft_init_cam(env, OBJ.cam_rot);
	mlx_destroy_image(env->mlx, env->img.img);
	env->img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	env->img.data = mlx_get_data_addr(env->img.img, &env->img.bpp, &env->img.s, &env->img.e);
	make_threads(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
}

void	move_cam(t_env *env)
{
	t_vector	n;

	n = CAM.n;
	print_vector("Xrot = ", OBJ.cam_rot);
	rotate_vec_x(OBJ.cam_rot.x, &n);
	rotate_vec_y(OBJ.cam_rot.y, &n);
	rotate_vec_z(OBJ.cam_rot.z, &n);
//	rotate_vec_x(OBJ.cam_rot.x, &CAM.dir);
//	rotate_vec_y(OBJ.cam_rot.y, &CAM.dir);
//	rotate_vec_z(OBJ.cam_rot.z, &CAM.dir);
	print_vector("Xn = ", n);
//	n = vector_sub((t_vector){0.0F, 0.0F, 0.0F}, CAM.n);
	print_vector("cam before ",CAM.pos);
	OBJ.cam.pos = vector_sub(CAM.pos, vector_scale(25.0F, n));
	print_vector("cam after ", CAM.pos);
	re_render(env);
}

int	key_hook(int keycode, t_env *env)
{
	ft_printf("key = %d\n", keycode);
	if (keycode == EXIT)
		exit(0);
	if (keycode == KEY_UP)
	{
		OBJ.cam_rot.x -= ROT_DELTA;
		re_render(env);
	}
	if (keycode == KEY_DOWN)
	{
		OBJ.cam_rot.x += ROT_DELTA;
		re_render(env);
	}
	if (keycode == KEY_LEFT)
	{
		OBJ.cam_rot.z -= ROT_DELTA;
		re_render(env);
	}
	if (keycode == KEY_RIGHT)
	{
		OBJ.cam_rot.z += ROT_DELTA;
		re_render(env);
	}
	if (keycode == 13)
	{
		move_cam(env);
	}
	if (keycode == 1)
	{
		OBJ.cam.pos = vector_scale(1.5F, OBJ.cam.pos);//, vector_sub((t_vector){0.0F, 0.0F, 0.0F}, CAM.n));
//		OBJ.cam.pos.z += 20;
		re_render(env);
	}
	return (env->img.s);
}
