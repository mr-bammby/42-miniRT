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

static void file_extension_check(char *file_name)
{
	int cnt;
	int len;

	cnt = 0;
	len = ft_strlen(file_name);
	if (len < 4)
		ft_exit_on_arg_error(FT_ERR_FILE_NAME, NULL, -1, NULL);
	while (cnt < len - 3)
	{
		if (file_name[cnt] == '.' && cnt != 0)
			ft_exit_on_arg_error(FT_ERR_FILE_NAME, NULL, -1, NULL);
		cnt++;
	}
	if (file_name[cnt] == '.' && file_name[cnt + 1] == 'r' \
		&& file_name[cnt + 2] == 't')
		return ;
	ft_exit_on_arg_error(FT_ERR_FILE_NAME, NULL, -1, NULL);
}

static int access_check(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if(fd == -1)
		ft_exit_on_arg_error(FT_ERR_FILE_ACCESS, NULL, -1, NULL);
	return (fd);
}



static int three_num_check(char* str)
{
	char **split;
	int i;

	split = ft_split(str, ',');
	if (split == NULL)
		return (1);
	i = 0;
	while(split[i] != NULL)
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

static void main_line_check(char **line_split, int last_check, int fd, char *line)
{
	static int	a_cnt = 0;
	static int	l_cnt = 0; 									//remove for bonus part
	static int	c_cnt = 0;
	int			i;

	if (last_check)
	{
		if (c_cnt == 0)
			ft_exit_on_arg_error(FT_ERR_C_LESS, NULL, fd, line);
		else
			return ;
	}
	i = 1;
	if (!ft_strcmp(line_split[0], "C"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
				ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
			else if (i == 1 || i == 2)
			{
				if(three_num_check(line_split[i]))
					ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
					ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
			i++;
		}
		if (i != 4)
			ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
		c_cnt++;
		if (c_cnt > 1)
			ft_exit_on_arg_error(FT_ERR_C_MANY, line_split, fd, line);
		return ;
	}
	else if (!ft_strcmp(line_split[0], "A"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 2)
				ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
			if (i == 2)
			{
				if(three_num_check(line_split[i]))
					ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
					ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
			i++;
		}
		if (i != 3)
			ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
		a_cnt++;
		if (a_cnt > 1)
			ft_exit_on_arg_error(FT_ERR_A_MANY, line_split, fd, line);
		return ;
	}
	else if (!ft_strcmp(line_split[0], "L"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
				ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
			if (i == 1 || i == 3)
			{
				if(three_num_check(line_split[i]))
					ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
					ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
			i++;
		}
		if (i != 4)
			ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
		l_cnt++;
		if (l_cnt > 1) ///remove for bonus part
			ft_exit_on_arg_error(FT_ERR_L_MANY, line_split, fd, line);
		return ;
	}
	ft_exit_on_arg_error(FT_ERR_UNKNOWN_OBJ, line_split, fd, line);
}

static void object_line_check(char **line_split, int fd, char *line)
{
	int			i;

	i = 1;
	if (!ft_strcmp(line_split[0], "sp"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
				ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
			if (i == 1 || i == 3)
			{
				if(three_num_check(line_split[i]))
					ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
					ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
			i++;
		}
		if (i != 4)
			ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
		return ;
	}
	else if (!ft_strcmp(line_split[0], "pl"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
				ft_exit_on_arg_error(FT_ERR_PL_ARG_CHECK, line_split, fd, line);
			if(three_num_check(line_split[i]))
				ft_exit_on_arg_error(FT_ERR_PL_ARG_CHECK, line_split, fd, line);
			i++;
		}
		if (i != 4)
			ft_exit_on_arg_error(FT_ERR_PL_ARG_CHECK, line_split, fd, line);
		return ;
	}
	else if (!ft_strcmp(line_split[0], "cy"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 5)
				ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
			if (i == 1 || i == 2 || i == 5)
			{
				if(three_num_check(line_split[i]))
					ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
					ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
			i++;
		}
		if (i != 6)
			ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
		return ;
	}
	ft_exit_on_arg_error(FT_ERR_UNKNOWN_OBJ, line_split, fd, line);
}

void line_check(char **line, int last_check, int fd)
{
	char		**line_split;
	char		*temp;

	if (last_check == 1)
	{
		main_line_check(NULL, 1, fd, NULL);
		return ;
	}
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
		return ; //check if that is newline problem
	if (line_split[0] == NULL)
	{
		ft_free_split(line_split);
		return ;
	}
	if (!ft_strcmp(line_split[0], "A") || !ft_strcmp(line_split[0], "L") || !ft_strcmp(line_split[0], "C"))
		main_line_check(line_split, 0, fd, *line);
	else if (!ft_strcmp(line_split[0], "sp") || !ft_strcmp(line_split[0], "pl") || !ft_strcmp(line_split[0], "cy")) /////////////bonus add other shapes
		object_line_check(line_split, fd, *line);
	else
		ft_exit_on_arg_error(FT_ERR_UNKNOWN_OBJ, line_split, fd, *line);
	ft_free_split(line_split);
}

void ft_argument_check(int argc, char **argv)
{
	char *line;
	int fd;

	if (argc != 2)
		ft_exit_on_arg_error(FT_ERR_ARG_NUM, NULL, -1, NULL);
	file_extension_check(argv[1]);
	fd = access_check(argv[1]);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_check(&line, 0, fd);
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	line_check(NULL, 1, fd);
	//return (0);
}