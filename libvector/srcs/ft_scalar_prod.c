/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scalar_prod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/11 23:55:59 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_fixed	ft_scalar_prod(t_vec vec1, t_vec vec2)
{
	t_fixed out[3];

	out[0] = double2fixed((fixed2double(vec1.size) * fixed2double(vec1.n_vec.x)) * (fixed2double(vec2.size) * fixed2double(vec2.n_vec.x)));
	out[1] = double2fixed((fixed2double(vec1.size) * fixed2double(vec1.n_vec.y)) * (fixed2double(vec2.size) * fixed2double(vec2.n_vec.y)));
	out[2] = double2fixed((fixed2double(vec1.size) * fixed2double(vec1.n_vec.z)) * (fixed2double(vec2.size) * fixed2double(vec2.n_vec.z)));
	return(double2fixed(fixed2double(out[0]) + fixed2double(out[1]) + fixed2double(out[2])));
}
