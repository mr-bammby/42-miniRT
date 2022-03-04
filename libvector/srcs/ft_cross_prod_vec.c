/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cross_prod_vec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/04 23:39:51 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_vec	ft_cross_prod(t_vec vec1, t_vec vec2)
{
	t_fixed out[3];

	out[0] = (vec1.size * vec1.n_vec.y) * (vec2.size * vec2.n_vec.z) - (vec1.size * vec1.n_vec.z) * (vec2.size * vec2.n_vec.y);
	out[1] = (vec1.size * vec1.n_vec.z) * (vec2.size * vec2.n_vec.x) - (vec1.size * vec1.n_vec.x) * (vec2.size * vec2.n_vec.z);
	out[2] = (vec1.size * vec1.n_vec.x) * (vec2.size * vec2.n_vec.y) - (vec1.size * vec1.n_vec.y) * (vec2.size * vec2.n_vec.x);
	return(ft_creat_vec(out[0], out[1], out[2]));
}
