/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:30:43 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/18 10:30:43 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

const char	*g_error_msg[] = {
	": camera",
	": ambient light",
	": light",
	": sphere",
	": plane",
	": cylinder",
	": values out of number range",
	": coordinate value out of valid range",
	": vector value out of valid range",
	": vector size invalid",
	": RGB value out of valid range",
	": angle value out of valid range",
	": bad line read",
	": ratio value out of valid range",
	": diameter value out of valid range",
	": height value out of valid range",
	": memory allocation failed"
};

/**
	@brief Error writing function. Concationates error message according
		to error flags. Messages can be found in ft_perror.c g_error_msg.
	@param Error Error flags for error messages.
	@return None.
 */
void	ft_perror(t_error_flags error)
{
	int	max_list;
	int	i;

	max_list = sizeof(g_error_msg) / sizeof(g_error_msg[0]);
	i = 0;
	write(2, "Error", 5);
	while (i < max_list)
	{
		if ((error >> i & 1))
			write(2, g_error_msg[i], ft_strlen(g_error_msg[i]));
		i++;
	}
	write(2, "\n", 1);
	return ;
}
