/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_unit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 08:40:09 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/16 14:44:01 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector	vector_unit(t_vector v)
{
	t_vector	v_n;

	v_n = v;
	print_vector("v_n :", v_n);
	vector_norm(&v_n);
	print_vector("v_n :", v_n);
	return (vector_div(&v, &v_n));
}
