/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 07:35:04 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/23 08:33:43 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int	key_hook(int keycode, t_env *env)
{
	if (keycode == EXIT)
		exit(0);
	ft_printf("key = %d\n", keycode);
	return (env->img.s);
}
