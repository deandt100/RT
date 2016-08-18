/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 08:29:09 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/16 14:42:15 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector	vector_div(t_vector *v1, t_vector *v2)
{
	t_vector	ret;

	print_vector("v1 :", *v1);
	print_vector("v2 :", *v2);
	if (v2->x != 0)
		ret.x = v1->x / v2->x;
	else
		ret.x = v1->x;
	if (v2->y != 0)
		ret.y = v1->y / v2->y;
	else
		ret.y = v1->y;
	if (v2->z != 0)
		ret.z = v1->z / v2->z;
	else
		ret.z = v1->z;
	return (ret);
}
