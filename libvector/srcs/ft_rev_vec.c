/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/15 15:50:00 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_vec	ft_rev_vec(t_vec vec)
{
	vec.n_vec.x = double2fixed(-fixed2double(vec.n_vec.x));
	vec.n_vec.y = double2fixed(-fixed2double(vec.n_vec.y));
	vec.n_vec.z = double2fixed(-fixed2double(vec.n_vec.z));
	return(vec);
}
