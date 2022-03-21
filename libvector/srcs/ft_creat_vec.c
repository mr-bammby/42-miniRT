/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 19:49:36 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Calculates the unit vector out of three fixed-point numbers.
	@param x First fixed-point number.
	@param y Second fixed-point number.
	@param z Third fixed-point number.
	@return Returns a unit vector.
 */
t_vec	ft_creat_vec(t_fixed x, t_fixed y, t_fixed z)
{
	double	distance;
	t_vec	out;
	double	distance_inv;

	distance = sqrt(pow(fxtod(x), 2) + \
		pow(fxtod(y), 2) + pow(fxtod(z), 2));
	out.size = dtofx(distance);
	if (distance < 0.0000001)
	{
		out.n_vec.x = dtofx(0);
		out.n_vec.y = dtofx(0);
		out.n_vec.z = dtofx(0);
	}
	else
	{	
		distance_inv = 1 / distance;
		out.n_vec.x = dtofx(fxtod(x) * distance_inv);
		out.n_vec.y = dtofx(fxtod(y) * distance_inv);
		out.n_vec.z = dtofx(fxtod(z) * distance_inv);
	}
	return (out);
}
