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

void ft_exit_on_arg_error(char *msg, char **split, int fd, char *line)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	if (split)
		ft_free_split(split);
	if (fd != -1)
		close(fd);
	ft_smart_free((void **)&line);
	exit(FT_EXIT_ON_ERROR);
}

void ft_exit_on_built_error(char *msg, char **split, int fd, char *line)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	if (split)
		ft_free_split(split);
	if (fd != -1)
		close(fd);
	ft_smart_free((void **)&line);
	exit(FT_EXIT_ON_ERROR);
}