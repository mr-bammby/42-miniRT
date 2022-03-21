/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:45:42 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Substracts one vector from another vector.
	@param vec1 First vector.
	@param vec2 Second vector.
	@return Returns the new vector.
 */
t_vec	ft_sub_vec(t_vec vec1, t_vec vec2)
{
	double	out[3];

	out[0] = (fxtod(vec1.size) * fxtod(vec1.n_vec.x)) - \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.x));
	out[1] = (fxtod(vec1.size) * fxtod(vec1.n_vec.y)) - \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.y));
	out[2] = (fxtod(vec1.size) * fxtod(vec1.n_vec.z)) - \
		(fxtod(vec2.size) * fxtod(vec2.n_vec.z));
	return (ft_creat_vec(dtofx(out[0]), dtofx(out[1]), dtofx(out[2])));
}
