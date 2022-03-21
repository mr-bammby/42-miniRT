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

/**
	@brief Function to properly free assigned memory of a node in list with
		geometric objects.
	@param tmp The node to be freed.
	@return None.
*/
static void	del_gol(void *tmp)
{
	ft_smart_free((void **)(&((t_geo_object *)tmp)->s));
	ft_smart_free((void **)&tmp);
}

/**
	@brief Function that frees allocated memory of the liked list for
		geometric objects.
	@param gol Pointer to list of objects (sphere, plane, cylinder).
	@return  None.
*/
void	ft_exit_free(t_list *gol)
{
	if (gol)
		ft_lstclear(&gol, del_gol);
	ft_smart_free((void **)(&gol));
}

/**
	@brief Writes an error message, frees allocated memory and closes open file
		descriptor before exiting the programm on error.
	@param msg Error message to be printed.
	@param split Null-terminated array of strings that need to be freed..
	@param fd File descriptor of input file.
	@param line Pointer to line that was read from input file.
	@return None.
*/
void	ft_exit_on_arg_error(char *msg, char **split, int fd, char *line)
{
	if (msg != NULL)
	{
		write(2, "Error: ", 7);
		write(2, msg, ft_strlen(msg));
	}
	if (split)
		ft_free_split(split);
	if (fd != -1)
		close(fd);
	ft_smart_free((void **)&line);
	exit(FT_EXIT_ON_ERROR);
}

/**
	@brief Frees the assigned memory and passes the respective return value.
	@param return_value Return value that indicates the ocured problem.
	@param go Structure of an geometric object to be filled with values of the 
		respective type.
	@param s Pointer to a structure of a specific geometric object 
		(sphere, plane, cylinder).
	@return Number that indicates on the error.
*/
int	ft_list_creation_arg_error(int return_value, t_geo_object *go, void *s)
{
	ft_smart_free((void **)&s);
	ft_smart_free((void **)&go);
	return (return_value);
}
