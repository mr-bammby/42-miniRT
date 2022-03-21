/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:29:18 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/04 21:29:18 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Checks for the amount of numbers and if they are digits for 
		an argument category that should contain 3 numbers.
	@param str String to be checked for argument category requirement.
	@return 0 on success, else 1.
*/
int	ft_three_num_check(char *str)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (split == NULL)
		return (1);
	i = 0;
	while (split[i] != NULL)
	{
		if (i > 2)
		{
			ft_free_split(split);
			return (1);
		}
		if (ft_digit_check(split[i]) != 0)
		{
			ft_free_split(split);
			return (1);
		}
		i++;
	}
	ft_free_split(split);
	if (i != 3)
		return (1);
	return (0);
}

/**
	@brief Assigns the appropriate function to check objects according to
		their type.
	@param line_split Array of strings separated by argument categories.
	objects after inputfile was completely processed.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return None.
*/
static void	ft_arg_check_assignment(char **line_split, int fd, char *line)
{
	if (!ft_strcmp(line_split[0], "A") || !ft_strcmp(line_split[0], "L") || \
		!ft_strcmp(line_split[0], "C"))
		ft_arg_check_vo(line_split, 0, fd, line);
	else if (!ft_strcmp(line_split[0], "sp") || \
		!ft_strcmp(line_split[0], "pl") || !ft_strcmp(line_split[0], "cy"))
		ft_arg_check_go(line_split, fd, line);
	else
		ft_exit_on_arg_error(FT_ERR_UNKNOWN_OBJ, line_split, fd, line);
}

/**
	@brief Divides the string in line into individual argument categories
	and checks for their validity.
	@param line Line that was read from input file.
	@param last_check Indicator for checking the correct amount of mandatory
		objects after inputfile was completely processed.
	@param fd Filedescriptor of opened input file.
	@return 0 on success.
	@exception If last line has been processed, check if one camera object
		is available (last_check == 1)
*/
static int	ft_arg_check_handler(char **line, int last_check, int fd)
{
	char		**line_split;
	char		*temp;

	if (last_check == 1)
		return (ft_arg_check_vo(NULL, 1, fd, NULL));
	if (line == NULL || *line == NULL)
		ft_exit_on_arg_error(FT_ERR_UNKNOWN, NULL, fd, *line);
	temp = *line;
	if (ft_strlen(*line) != 0 && (*line)[ft_strlen(*line) - 1] == '\n')
	{
		*line = ft_substr(*line, 0, ft_strlen(*line) - 1);
		ft_smart_free((void **)&temp);
	}
	line_split = ft_split(*line, ' ');
	if (line_split == NULL)
		return (0);//check if that is newline problem
	if (line_split[0] == NULL)
	{
		ft_free_split(line_split);
		return (0);
	}
	ft_arg_check_assignment(line_split, fd, *line);
	ft_free_split(line_split);
	return (0);
}

/**
	@brief Checks for input file validity.
	@param argc Number of arguments passed.
	@param argv Arguments passed.
	@return None.
*/
void	ft_argument_check(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc != 2)
		ft_exit_on_arg_error(FT_ERR_ARG_NUM, NULL, -1, NULL);
	ft_file_extension_check(argv[1]);
	fd = ft_access_check(argv[1]);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_arg_check_handler(&line, 0, fd);
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_arg_check_handler(NULL, 1, fd);
}
