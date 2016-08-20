/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_compare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 09:52:52 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/20 09:59:00 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		vector_comp(t_vector v1, t_vector v2)
{
	return (!(v1.x != v2.x || v1.y != v2.y || v1.z != v2.z));
}


