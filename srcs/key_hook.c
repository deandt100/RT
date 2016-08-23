/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 07:35:04 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/23 11:36:37 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	change_cam(t_env *env, t_vector rot)
{
	print_vector("bef", CAM.dir);
	ft_printf("ROTATING CAM\n");
//	rotate_vec_x(-rot.x, &CAM.dir);
//	rotate_vec_x(rot.x, &CAM.u);
	rotate_vec_x(rot.x, &CAM.pos);

//	rotate_vec_y(-rot.y, &CAM.dir);
//	rotate_vec_y(rot.y, &CAM.u);
	rotate_vec_y(rot.y, &CAM.pos);

	rotate_vec_z(-rot.z, &CAM.dir);
//	rotate_vec_z(rot.z, &CAM.u);
	rotate_vec_z(rot.z, &CAM.pos);
//	print_vector("aft", CAM.dir);
}


int	key_hook(int keycode, t_env *env)
{
	ft_printf("key = %d\n", keycode);
	if (keycode == EXIT)
		exit(0);
	if (keycode == KEY_DOWN)
	{
		change_cam(env, (t_vector){1.0F, 0.0F, 0.0F});
		init_cam(env);
	
		mlx_destroy_image(env->mlx, env->img.img);
		env->img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
		env->img.data = mlx_get_data_addr(env->img.img, &env->img.bpp, &env->img.s, &env->img.e);
		make_threads(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);

	}
	return (env->img.s);
}
