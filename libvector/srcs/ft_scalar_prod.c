/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scalar_prod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:19:03 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Calculates the scalar product of two vectors.
	@param vec1 First vector.
	@param vec2 Second vector.
	@return Returns the calculated scalar-product as fixed-point value.
 */
t_fixed	ft_scalar_prod(t_vec vec1, t_vec vec2)
{
	t_fixed	out[3];

	out[0] = dtofx((fxtod(vec1.size) * fxtod(vec1.n_vec.x)) * \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.x)));
	out[1] = dtofx((fxtod(vec1.size) * fxtod(vec1.n_vec.y)) * \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.y)));
	out[2] = dtofx((fxtod(vec1.size) * fxtod(vec1.n_vec.z)) * \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.z)));
	return (dtofx(fxtod(out[0]) + fxtod(out[1]) + fxtod(out[2])));
}
