CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/
SRC			=	ft_fixed_conversion.c ft_add_vec.c ft_sub_vec.c ft_scalar_prod.c \
				ft_cross_prod_vec.c ft_creat_vec.c ft_quadratic_solver.c ft_create_ray.c \
				ft_points_dist.c ft_point_on_ray.c ft_parallel_line_dist.c ft_create_plane.c \
				ft_rev_vec.c ft_create_vec_from_points.c
# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF 		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD 		= $(OBJF:$(OBJD)%.o)

NAME		= libvector.a
HEADD		= ./incl/
HEADF		= libvector.h


#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			ar rcs ${NAME} ${OBJF}


all:		${NAME}


clean:		
			${RM} ${OBJF}

fclean:		clean
			${RM} ${NAME}
			${RM} a.out

re:			fclean all

.PHONY:		all clean fclean re