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

int file_extension_check(char *file_name)
{
	int cnt;
	int len;

	cnt = 0;
	len = ft_strlen(file_name);
	if (len < 4)
	{
		write(2, "Error: unsupported file\n", 24);
		return (1);
	}
	while (cnt < len - 3)
	{
		if (file_name[cnt] == '.' && cnt != 0)
		{
			write(2, "Error: unsupported file\n", 24);
			return(1);
		}
		cnt++;
	}
	if (file_name[cnt] == '.' && file_name[cnt + 1] == 'r' \
		&& file_name[cnt + 2] == 't')
		return(0);
	write(2, "Error: unsupported file\n", 24);
	return(1);
}

int access_check(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if(fd == -1)
	{
		perror("Error");
		return(-1);
	}
	return (fd);
}



int three_num_check(char* str)
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

int main_line_check(char **line_split, int last_check)
{
	static int	a_cnt = 0;
	static int	l_cnt = 0; 									//remove for bonus part
	static int	c_cnt = 0;
	int			i;

	if (last_check)
		return (!c_cnt);
	i = 1;
	if (!ft_strcmp(line_split[0], "C"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
			{
				ft_free_split(line_split);
				return (1);
			}
			if (i == 1 || i == 2)
			{
				if(three_num_check(line_split[i]))
				{
					ft_free_split(line_split);
					return (1);
				}
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
				{
					ft_free_split(line_split);
					return (1);
				}
			i++;
		}
		ft_free_split(line_split);
		if (i != 4)
			return (1);
		c_cnt++;
		if (c_cnt > 1)
			return (1);
		return (0);
	}
	else if (!ft_strcmp(line_split[0], "A"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 2)
			{
				ft_free_split(line_split);
				return (1);
			}
			if (i == 2)
			{
				if(three_num_check(line_split[i]))
				{
					ft_free_split(line_split);
					return (1);
				}
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
				{
					ft_free_split(line_split);
					return (1);
				}
			i++;
		}
		ft_free_split(line_split);
		if (i != 3)
			return (1);
		a_cnt++;
		if (a_cnt > 1)
			return (1);
		return (0);
	}
	else if (!ft_strcmp(line_split[0], "L"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
			{
				ft_free_split(line_split);
				return (1);
			}
			if (i == 1 || i == 3)
			{
				if(three_num_check(line_split[i]))
				{
					ft_free_split(line_split);
					return (1);
				}
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
				{
					ft_free_split(line_split);
					return (1);
				}
			i++;
		}
		ft_free_split(line_split);
		if (i != 4)
			return (1);
		l_cnt++;
		if (l_cnt > 1) ///remove for bonus part
			return (1);
		return (0);
	}
	return(1);
}

int object_line_check(char **line_split)
{
	int			i;

	i = 1;
	if (!ft_strcmp(line_split[0], "sp"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
			{
				ft_free_split(line_split);
				return (1);
			}
			if (i == 1 || i == 3)
			{
				if(three_num_check(line_split[i]))
				{
					ft_free_split(line_split);
					return (1);
				}
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
				{
					ft_free_split(line_split);
					return (1);
				}
			i++;
		}
		ft_free_split(line_split);
		if (i != 4)
			return (1);
		return (0);
	}
	else if (!ft_strcmp(line_split[0], "pl"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 3)
			{
				ft_free_split(line_split);
				return (1);
			}
			if(three_num_check(line_split[i]))
			{
				ft_free_split(line_split);
				return (1);
			}
			i++;
		}
		ft_free_split(line_split);
		if (i != 4)
			return (1);
		return (0);
	}
	else if (!ft_strcmp(line_split[0], "cy"))
	{
		while(line_split[i] != NULL)
		{
			if (i > 5)
			{
				ft_free_split(line_split);
				return (1);
			}
			if (i == 1 || i == 2 || i == 5)
			{
				if(three_num_check(line_split[i]))
				{
					ft_free_split(line_split);
					return (1);
				}
			}
			else
				if (ft_digit_check(line_split[i]) != 0)
				{
					ft_free_split(line_split);
					return (1);
				}
			i++;
		}
		ft_free_split(line_split);
		if (i != 6)
			return (1);
		return (0);
	}
	return (1);
}

int line_check(char **line, int last_check)
{
	char		**line_split;
	char		*temp;

	if (last_check == 1)
		return(main_line_check(NULL, 1));
	temp = *line;
	*line = ft_strtrim(*line, "\n");
	ft_smart_free((void **)&temp);
	line_split = ft_split(*line, ' ');
	if (line_split == NULL)
		return (1);
	if (line_split[0] == NULL)
		return(0);
	if (!ft_strcmp(line_split[0], "A") || !ft_strcmp(line_split[0], "L") || !ft_strcmp(line_split[0], "C"))
		return(main_line_check(line_split, 0));
	else if (!ft_strcmp(line_split[0], "sp") || !ft_strcmp(line_split[0], "pl") || !ft_strcmp(line_split[0], "cy")) /////////////bonus add other shapes
		return(object_line_check(line_split));
	return (1);
}

int argument_check(int argc, char **argv)
{
	char *line;
	int fd;

	if (argc != 2)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	if (file_extension_check(argv[1]) != 0)
		return (2);
	fd = access_check(argv[1]);
	if (fd == -1)
		return (3);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line_check(&line, 0) != 0)
		{
			close(fd);
			ft_smart_free((void **)&line);
			write(2, "Error: unknown line format1\n", 28);
			return(4);
		}
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line_check(NULL, 1) != 0)
	{
		write(2, "Error: unknown line format2\n", 27);
		return(4);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int error;

	error = argument_check(argc, argv);
	if(error)
		return (error);
	//error = list_builder
}
