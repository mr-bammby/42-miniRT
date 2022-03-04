/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:20:12 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 13:20:12 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	main(int argc, char **argv)
{
	int			error;

	error = argument_check(argc, argv);
	if(error)
		return (error);
	//error = list_builder
	ft_mlx();


}

//export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0