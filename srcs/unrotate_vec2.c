/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unrotate_vec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 23:11:58 by daviwel           #+#    #+#             */
/*   Updated: 2016/07/15 23:27:44 by daviwel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	unrotate_vec2(t_env *env, int i, t_vector *vec)
{
	rotate_vec_x(-CONES[i].rot.x, vec);
	rotate_vec_y(-CONES[i].rot.y, vec);
	rotate_vec_z(-CONES[i].rot.z, vec);
}
