/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/05 01:53:32 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_vec	ft_sub_vec(t_vec vec1, t_vec vec2)
{
	double out[3];

	out[0] = (fixed2double(vec1.size) * fixed2double(vec1.n_vec.x)) - (fixed2double(vec2.size) * fixed2double(vec2.n_vec.x));
	out[1] = (fixed2double(vec1.size) * fixed2double(vec1.n_vec.y)) - (fixed2double(vec2.size) * fixed2double(vec2.n_vec.y));
	out[2] = (fixed2double(vec1.size) * fixed2double(vec1.n_vec.z)) - (fixed2double(vec2.size) * fixed2double(vec2.n_vec.z));
	return(ft_creat_vec(double2fixed(out[0]), double2fixed(out[1]), double2fixed(out[2])));
}
