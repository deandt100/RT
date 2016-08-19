/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 13:09:19 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/19 07:47:15 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	vector_scale(double c, t_vector v)
{
	t_vector	ret;

	ret.x = v.x * c;
	ret.y = v.y * c;
	ret.z = v.z * c;
	return (ret);
}
