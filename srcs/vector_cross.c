/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cross.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 08:13:53 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/18 17:01:15 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = (v1.y * v2.z) - (v1.z * v2.y);
	ret.y = (v1.z * v2.x) - (v1.x * v2.z);
	ret.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (ret);
}
