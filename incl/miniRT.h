#ifndef MINIRT_H
# define MINIRT_H

# include "../gnl/incl/get_next_line.h"
# include "../libft/incl/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

/* ft_utils.c */

int		ft_strcmp(char *s1, char *s2);
void	ft_smart_free(void **ptr);
void	ft_free_split(char **split);

/* ft_utils_num.c */
int		ft_digit_check(char *argv);
int		ft_atoll(const char *str, long long int *out);
#endif
