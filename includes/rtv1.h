/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/01 08:09:54 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/25 14:49:20 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <complex.h>
# include <mlx.h>
# include <vector.h>
# include <objects.h>
# include <colours.h>
# include <light.h>
# include <libft.h>
# include <pthread.h>
# define NO_THREADS 4
# define EPSILON (double)0.000001F
# define WIN_X 1280
# define WIN_Y 720
# define WIN_RATIO WIN_X / WIN_Y
# define VFOV (double) 60
# define EXIT 53
# define OBJ env->obj
# define LIGHTS OBJ.lights
# define CAM OBJ.cam
# define SPHERES env->obj.spheres
# define CYLINDERS env->obj.cylinders
# define CONES env->obj.cones
# define TRI env->obj.triangles
# define SP_POS(X) SPHERES[X].shape.pos
# define TR_POS(X) TRI[X].shape.pos
# define CYL_POS(X) CYLINDERS[X].p
# define CN_POS(X) CONES[X].p
# define ABSV(X) sqrt(vector_dot(X, X))
# define SQR(X) (X * X)
# define V ray->dir
# define P ray->start
# define PA cyl->p
# define VA cyl->v
# define DEL_P vector_sub(&P, &PA)
# define VEC_SQR(X) vector_dot(X, X)
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_W 13
# define KEY_S 1
# define ROT_DELTA 5.0F
# define SPEC_POWER 42

typedef struct	s_count
{
	int			mats;
	int			lights;
	int			spheres;
	int			triangles;
	int			cylinders;
	int			cones;
	int			planes;
}				t_count;

typedef struct	s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			s;
	int			e;
	char		id;
	int			x;
	int			y;
}				t_img;

typedef struct	s_obj
{
	int			num_mats;
	t_material	*mats;
	int			num_lights;
	t_light		*lights;
	int			num_spheres;
	t_sphere	*spheres;
	int			num_tri;
	t_triangle	*triangles;
	int			cur_sphere;
	int			cur_tri;
	t_cylinder	*cylinders;
	int			num_cyl;
	int			cur_cyl;
	t_cone		*cones;
	int			cur_cone;
	int			num_cone;
	t_plane		*planes;
	int			num_planes;
	int			cur_plane;
	t_material	cur_mat;
	t_vector	normal;
	t_vector	new_start;
	t_col		col;
	t_cam		cam;
	t_vector	cam_rot;
	float		ref_dist;
	int			in_shadow;
}				t_obj;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_obj		obj;
	int			br;
	t_ray		ray;
	int			spec_n;
	double		spec_coef;
	t_count		count;
	double      ambient_coef;
	double      ambient_level;
	int			ref_level;
	double		fov;
}				t_env;

typedef struct	s_rt_thread
{
	int		x_s;
	int		x_e;
	int		y_s;
	int		y_e;
	t_env	*env;
}				t_rt_thread;

typedef struct	s_ray_sphere
{
	double		a;
	double		b;
	double		c;
	double		sqrtdiscr;
	double		t0;
	double		t1;
	double		discr;
	t_vector	dist;
}				t_ray_sphere;

typedef struct	s_ray_tri
{
	float		d;
	float		inv_d;
	double		u;
	double		v;
	double		tmp;
	t_vector	e1;
	t_vector	e2;
	t_vector	s1;
	t_vector	s2;
	t_vector	s3;
}				t_ray_tri;

int				in_epsilon(double val);

int				solve_quadratic(t_ray_sphere *rs, double *t);

void			unrotate_vec2(t_env *env, int i, t_vector *vec);

void			print_vector(char *des, t_vector v);

void			mlx_image_put_pixel(void *mlx, t_img *i, t_vector p,
					t_col *c);

void			set_tri_pos(t_triangle *tri);

int				key_hook(int keycode, t_env *env);

int				close_window(t_env *env);

void			sphere_raytrace(t_env *env);

/*
** File Input
*/

void			get_cam(t_env *env, int fd);

void			fill_cone(t_env *env, int fd);

void			fill_materials(t_env *env, int fd);

void			fill_lights(t_env *env, int fd);

void			fill_spheres(t_env *env, int fd);

void			fill_triangles(t_env *env, int fd);

void			fill_cylinders(t_env *env, int fd);

void			set_vector(t_vector *v, char *temp);

void			get_input(t_env *env, char *file);

void			count_types(t_obj *temp, int fd);

void			val_types(t_env *env, t_obj temp);

void			rotate_cam(t_env *env);

void			init_cam(t_env *env);

/*
** New file input.
*/

t_vector		ft_get_vector(char *line);
int				ft_val_col(t_col *col);
int				ft_val_mat(t_env *env, int mat, char *obj);
int				ft_input_error(char *obj, char *msg);
void			ft_init_cam(t_env *env, t_vector rot, int r);
void			ft_get_input(t_env *env, char *file);
void			ft_count_objs(t_env *env, char *file);
void			ft_fill_camera(int fd, t_env *env);
void			ft_fill_material(int fd, t_env *env);
void			ft_fill_light(int fd, t_env *env);
void			ft_fill_sphere(int fd, t_env *env);
void			ft_fill_triangle(int fd, t_env *env);
void			ft_fill_cone(int fd, t_env *env);
void			ft_fill_cylinder(int fd, t_env *env);
void			ft_fill_plane(int fd, t_env *env);

/*
** Primitive Intersection & raytracing
*/

void    		print_col(t_col col);

void			calc_lighting(t_env *env, float coef);

void			*raytrace(void *p);

void			make_threads(t_env *env);

void			set_val_sphere(t_env *env, double t, t_ray ray);

void			set_val_tri(t_env *env, double t, t_ray ray);

void			set_val_cyl(t_env *env, double t, t_ray ray);

void			set_val_cone(t_env *env, double t, t_ray ray);

void			set_val_plane(t_env *env, double t, t_ray ray);

void			get_intersections(t_env *env, t_ray *ray, double *t);

int				intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t);

int				intersect_ray_cylinder(t_ray *ray, t_cylinder *cyl, double *t);

int				intersect_ray_tri(t_ray *r, t_triangle *tri, double *res,
					t_vector *n);

int				intersect_ray_cone(t_ray *ray, t_cone *cone, double *t);

int				intersect_ray_plane(t_ray *ray, t_plane *pla, double *t5);
void			gi_plane(t_env *env, t_ray *ray, double *t, double *ref_dist);
/*
** Light & shadows
*/

int				sh_spheres(t_env *env, t_ray *light_ray, double t);

int				sh_tri(t_env *env, t_ray *light_ray, double t);

int				sh_cylinder(t_env *env, t_ray *light_ray, double t);

int				sh_cone(t_env *env, t_ray *light_ray, double t);
#endif
