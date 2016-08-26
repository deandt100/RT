/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 07:24:50 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/26 09:48:57 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

/*
** Reflect ray around normal.
*/

static void			reflect_ray(t_env *env, t_ray *ray)
{
	env->ref_coef *= OBJ.cur_mat.reflection;
	env->ambient_coef *= env->ambient_level;
	env->spec_coef = 0.0;
	ray->start = OBJ.new_start;
	ray->dir = vector_sub(ray->dir,
		vector_scale(2.0f * vector_dot(ray->dir, OBJ.normal), OBJ.normal));
}

/*
** Shoot ray and calculate color value based on reflection, shadows
** and materials.
*/

static t_col		shoot_ray(t_ray ray, int level_max, t_env *env)
{
	double		t;

	env->ref_coef = 1.0F;
	env->spec_coef = 1.0F; 
	env->ambient_coef = 1.0F; 
	while (env->ref_coef > 0.0F && level_max--)
	{
		t = 20000.0f;
		get_intersections(env, &ray, &t);
		if (OBJ.cur_sphere != -1)
			set_val_sphere(env, t, ray);
		else if (OBJ.cur_tri != -1)
			set_val_tri(env, t, ray);
		else if (OBJ.cur_cyl != -1)
			set_val_cyl(env, t, ray);
		else if (OBJ.cur_cone != -1)
			set_val_cone(env, t, ray);
		else if (OBJ.cur_plane != -1)
			set_val_plane(env, t, ray);
		else
			break ;
		if (env->br == 1)
			break ;
		calc_lighting(env);
		reflect_ray(env, &ray);
	}
	return (OBJ.col);
}

/*
** Save color value to image.
*/

static void			save_to_img(t_env *env, t_col col, int x, int y)
{
	t_col temp;


	if (col.r * 255.0f < 255.0f)
		temp.r = col.r * 255.0f;
	else
		temp.r = 255.0f;
	if (col.g * 255.0f < 255.0f)
		temp.g = col.g * 255.0f;
	else
		temp.g = 255.0f;
	if (col.b * 255.0f < 255.0f)
		temp.b = col.b * 255.0f;
	else
		temp.b = 255.0f;
	env->img.data[(x + y * WIN_X) * 4 + 2] = (unsigned char)temp.r;
	env->img.data[(x + y * WIN_X) * 4 + 1] = (unsigned char)temp.g;
	env->img.data[(x + y * WIN_X) * 4 + 0] = (unsigned char)temp.b;
}

void	create_ray(double x, double y, t_ray *ray, t_env *env)
{
	t_vector	s;

	s = vector_add(CAM.l, vector_scale(x * CAM.w / (double)WIN_X, CAM.u));
	s = vector_sub(s, vector_scale(y * CAM.h / (double)WIN_Y, CAM.v));
	ray->dir = vector_sub(s, CAM.pos);
	vector_norm(&ray->dir);
}


t_col	create_fragments(t_rt_thread *t, int x, int y)
{
	double	frag_x;
	double	frag_y;
	double	frag_step;
	t_ray	ray;
	t_col	ret = {0.0F , 0.0F , 0.0F};
	double	fragments;

	fragments = pow(t->env->sampling_level, 2);
	frag_step = 1.0F / (fragments / t->env->sampling_level);
	frag_y = frag_step / 2;
	while (frag_y < 1.0)
	{
		frag_x = frag_step / 2;
		while (frag_x < 1.0F)
		{
			create_ray(x + frag_x, y + frag_y, &ray, t->env);
			t->env->obj.col = (t_col){0.0, 0.0, 0.0};
			color_add(&ret, shoot_ray(ray, t->env->ref_level, t->env));
			frag_x += frag_step;
		}
		frag_y += frag_step;
	}
	color_div(&ret, fragments);
	return (ret);
}

/*
** Iterate through each pixel, shoot ray into scene for each and save returned
** colour value to image.
*/

void				*raytrace(void *p)
{
	int		x;
	t_ray	ray;
	t_rt_thread	*t;

	t = (t_rt_thread*)p;
	ray.start = t->env->obj.cam.pos;
	t->env->sampling_level = 2;
	while (t->y_s < t->y_e)
	{
		x = t->x_s - 1;
		while (++x < t->x_e)
		{
			create_ray(x, t->y_s, &ray, t->env);
			t->env->ray = ray;
			t->env->obj.col = (t_col){0.0, 0.0, 0.0};
			t->env->br = 0;
			if (t->env->sampling_level > 1)
				save_to_img(t->env, create_fragments(t, x, t->y_s), x, t->y_s);	
			else
				save_to_img(t->env, shoot_ray(ray, t->env->ref_level, t->env), x, t->y_s);
		}
		t->y_s++;
	}
	pthread_exit(NULL);
}
