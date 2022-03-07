/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:29:01 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/07 18:29:01 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

static void	del_gol(void *tmp)
{
	ft_smart_free((void **)(&((t_geo_object *)tmp)->s));
	ft_smart_free((void **)&tmp);
}

void ft_exit_free(t_list *gol)
{
	if (gol)
		ft_lstclear(&gol, del_gol);
	ft_smart_free((void **)(&gol));
}