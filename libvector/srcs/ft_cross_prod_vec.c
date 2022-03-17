/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cross_prod_vec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:45:21 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Calculates the cross product of two vectors.
	@param vec1 First vector.
	@param vec2 Second vector.
	@return Returns a vector that is perpendicular to the both given vectors.
 */
t_vec	ft_cross_prod_vec(t_vec vec1, t_vec vec2)
{
	double	out[3];

	out[0] = (((fxtod(vec1.size) * fxtod(vec1.n_vec.y)) * (fxtod(vec2.size) * \
		fxtod(vec2.n_vec.z))) - ((fxtod(vec1.size) * fxtod(vec1.n_vec.z)) * \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.y))));
	out[1] = (((fxtod(vec1.size) * fxtod(vec1.n_vec.z)) * (fxtod(vec2.size) * \
		fxtod(vec2.n_vec.x))) - ((fxtod(vec1.size) * fxtod(vec1.n_vec.x)) * \
			(fxtod(vec2.size) * fxtod(vec2.n_vec.z))));
	out[2] = (((fxtod(vec1.size) * fxtod(vec1.n_vec.x)) * (fxtod(vec2.size) * \
		fxtod(vec2.n_vec.y))) - ((fxtod(vec1.size) * fxtod(vec1.n_vec.y)) * \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.x))));
	return (ft_creat_vec(dtofx(out[0]), dtofx(out[1]), dtofx(out[2])));
}
