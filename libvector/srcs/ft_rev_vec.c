/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:08:39 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Reverses the direction of a vector.
	@param vec Vector to be reversed.
	@return Returns the reversed vector.
 */
t_vec	ft_rev_vec(t_vec vec)
{
	vec.n_vec.x = dtofx(-fxtod(vec.n_vec.x));
	vec.n_vec.y = dtofx(-fxtod(vec.n_vec.y));
	vec.n_vec.z = dtofx(-fxtod(vec.n_vec.z));
	return (vec);
}
