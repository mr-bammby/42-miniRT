CC			= gcc
CFLAGS		= -g3 #-Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/


UNAME = $(shell uname)
#echo $(UNAME)

SRC			=	main.c ft_utils.c ft_utils_num.c ft_utils_mlx.c ft_arg_check.c ft_list_builder.c diagnostics.c ft_exit_free.c ft_screen_maker.c \
				ft_sphere_distance.c ft_light_stuff.c ft_plane_distance.c ft_cylinder_distance.c ft_cylinder_utils.c

# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)

NAME		= miniRT
HEADD		= ./incl/
HEADF		= miniRT.h

LIBFTD		= ./libft/
LIBFT_OBJD	= objs
LIBFT_SRCD	= srcs/
LIBFTL		= libft.a

LIBFT_OBJF    = ${LIBFTD}${LIBFT_OBJD}/*.o
LIBFT_MAKE    = make -C ${LIBFTD}

LIBGNLD		= ./gnl/
LIBGNL_OBJD	= objs
LIBGNL_SRCD	= srcs/
LIBGNLL		= libgnl.a

LIBGNL_OBJF    = ${LIBGNLD}${LIBGNL_OBJD}/*.o
LIBGNL_MAKE    = make -C ${LIBGNLD}

LIBVECTORD		= ./libvector/
LIBVECTOR_OBJD	= objs
LIBVECTOR_SRCD	= srcs/
LIBVECTORL		= libvector.a

LIBVECTOR_OBJF    = ${LIBVECTORD}${LIBVECTOR_OBJD}/*.o
LIBVECTOR_MAKE    = make -C ${LIBVECTORD}

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
MINILIB_D = ./mlx_linux

$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			make libftmake
			make libgnlmake
			make libvectormake
			make mlx_all
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) ${LIBVECTORD}${LIBVECTORL} ${LIBGNLD}${LIBGNLL} $(LIBFTD)$(LIBFTL) -L /usr/local/lib -I /usr/local/include ./mlx_linux/libmlx_Linux.a -L /usr/include/X11/extensions/ -lXext -lX11 -lm

endif

ifeq ($(UNAME), Darwin)
MINILIB_D = ./mlx_mac

$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -Imlx -c -o $@ $<

$(NAME):	${OBJF}
			make libftmake
			make libgnlmake
			make libvectormake
			make mlx_all
			$(CC) $(CFLAGS) -L $(MINILIB_D) -lmlx -framework OpenGL -L /usr/X11/lib -lXext -lX11 $(SRCF) ${LIBGNLD}${LIBGNLL} $(LIBFTD)$(LIBFTL) ${LIBVECTORD}${LIBVECTORL} -o $(NAME)
endif


all:		${NAME}

libftmake:
			${LIBFT_MAKE}

libgnlmake:
			${LIBGNL_MAKE}

libvectormake:
			${LIBVECTOR_MAKE}

mlx_all:
			cd $(MINILIB_D) && bash ./configure

clean:
			${RM} ${OBJD}*.o
			make -C ${LIBFTD} clean
			make -C ${LIBGNLD} clean
			make -C ${LIBVECTORD} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFTD}${LIBFTL}
			${RM} ${LIBGNLD}${LIBGNLL}
			${RM} ${LIBVECTORD}${LIBVECTORL}
			@${RM} ${HEADD}miniRT.h.gch
			@rm -rf miniRT.dSYM

re:			fclean all

.PHONY:		all clean fclean re