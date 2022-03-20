/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:09:09 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/06 20:09:09 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param split
	@param gol
	@param vo
	@return 
*/
static int	ft_list_builder_exec(char **split, t_list **gol, t_view_object *vo)
{
	int	error;

	if (ft_strlen(split[0]) == 1)
		error = ft_fill_vo(split, vo);
	else
		error = ft_create_gol(split, gol);
	return (error);
}

/**
	@brief
	@param line
	@param fd
	@param gol
	@return 
*/
static char	**ft_list_builder_split(char *line, int fd, t_list **gol)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split == NULL)
	{
		ft_exit_free(*gol);
		ft_exit_on_arg_error(FT_ERR_UNKNOWN, split, fd, line);
	}
	return (split);
}

/**
	@brief
	@param filename
	@param gol
	@param vo
	@return 
*/
void	ft_list_builder(char *filename, t_list **gol, t_view_object *vo)
{
	int		fd;
	char	*line;
	char	**split;
	int		error;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_list_builder_split(line, fd, gol);
		if (ft_strcmp(split[0], "\n"))
		{
			error = ft_list_builder_exec(split, gol, vo);
			if (error != 0)
			{
				ft_perror(error);
				ft_exit_free(*gol);
				ft_exit_on_arg_error(NULL, split, fd, line);
			}
		}
		ft_free_split(split);
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
}
