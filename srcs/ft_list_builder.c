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
	@brief Runs appropriate builder function in regards of object type.
	@param split Null-terminated array of strings to be added.
	@param gol Pointer to list of objects (sphere, plane, cylinder).
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@return 0 on success, else number that indicates on the error.
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
	@brief Split a given line by space and clean exit on error.
	@param line Line to be splitted.
	@param fd Filedescriptor of opened file.
	@param gol Pointer to list of objects (sphere, plane, cylinder).
	@return Returns splitted line as null-terminated array of strings.
*/
static char	**ft_list_builder_split(char *line, int fd, t_list **gol)
{
	char	**split;
	char	*trim_tmp;

	trim_tmp = ft_strtrim(line, "\n");
	split = ft_split(trim_tmp, ' ');
	ft_smart_free((void **)&trim_tmp);
	if (split == NULL)
	{
		ft_exit_free(*gol);
		ft_exit_on_arg_error(FT_ERR_UNKNOWN, split, fd, line);
	}
	return (split);
}

/**
	@brief Loops through the given file line by line and creates list of geometrical
		objects and structure of view objects.
	@param filename The file to be read.
	@param gol Pointer to list of objects (sphere, plane, cylinder).
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@return None.
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
		if (ft_strcmp(line, "\n"))
		{
			split = ft_list_builder_split(line, fd, gol);
			error = ft_list_builder_exec(split, gol, vo);
			if (error != 0)
			{
				ft_perror(error);
				ft_exit_free(*gol);
				ft_exit_on_arg_error(NULL, split, fd, line);
			}
			ft_free_split(split);
		}
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
}
