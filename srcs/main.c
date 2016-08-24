/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/01 08:32:34 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/24 14:04:41 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	cleanup2(t_env *env)
{
	if (OBJ.triangles && OBJ.num_tri >= 1)
	{
		free(OBJ.triangles);
		OBJ.num_tri = 0;
	}
	if (OBJ.cylinders && OBJ.num_cyl >= 1)
	{
		free(OBJ.cylinders);
		OBJ.num_cyl = 0;
	}
	if (OBJ.cones && OBJ.num_cone >= 1)
	{
		free(OBJ.cones);
		OBJ.num_cone = 0;
	}
}

void	cleanup(t_env *env)
{
	if (OBJ.mats && OBJ.num_mats >= 1)
	{
		free(OBJ.mats);
		OBJ.num_mats = 0;
	}
	if (OBJ.lights && OBJ.num_lights >= 1)
	{
		free(OBJ.lights);
		OBJ.num_lights = 0;
	}
	if (OBJ.spheres && OBJ.num_spheres >= 1)
	{
		free(OBJ.spheres);
		OBJ.num_spheres = 0;
	}
	cleanup2(env);
}

int		expose(t_env *env)
{
	ft_printf("drawing\n");
	if (env->win && env->img.img)
		mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	//cleanup(env);
	return (0);
}

int		main(int argc, char **argv)
{
	t_env		env;

	if (argc != 2)
	{
		ft_printf("Please include a scene file\n");
		return (0);
	}
	ft_get_input(&env, argv[1]);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_X, WIN_Y, "rtv1");
	env.img.img = mlx_new_image(env.mlx, WIN_X, WIN_Y);
	env.img.data = mlx_get_data_addr(env.img.img, &env.img.bpp,
	&env.img.s, &env.img.e);
	clock_t start = clock();
	make_threads(&env);
	clock_t diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000/4, msec%1000/4);
//	exit(1);
	mlx_key_hook(env.win, key_hook, &env);
	mlx_expose_hook(env.win, expose, &env);
	mlx_hook(env.win, 17, 0L, &close_window, &env);
	mlx_loop(env.mlx);
	return (0);
}
