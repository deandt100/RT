/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_compare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 09:52:52 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/21 09:34:08 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		vector_comp(t_vector v1, t_vector v2)
{
	if (in_epsilon(v1.x - v2.x) == 0)
		return (0);
	if (in_epsilon(v1.y - v2.y) == 0)
		return (0);
	if (in_epsilon(v1.z - v2.z) == 0)
		return (0);
	return (1);
}
