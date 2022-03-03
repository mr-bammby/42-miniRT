CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/


UNAME = $(shell uname)
#echo $(UNAME)

SRC			=	main.c ft_utils.c ft_utils_num.c

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



#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

# $(NAME):	${OBJF}
# 			make libftmake
# 			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) $(HEADD)$(HEADF) $(LIBFTD)$(LIBFTL)
$(NAME):	${OBJF}
			make libftmake
			make libgnlmake
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) -L $(HEADD) $(LIBFTD)$(LIBFTL) ${LIBGNLD}${LIBGNLL} -L /usr/local/lib -I /usr/local/include 


all:		${NAME}

libftmake:
			${LIBFT_MAKE}

libgnlmake:
			${LIBGNL_MAKE}

clean:
			${RM} ${OBJD}*.o
			make -C ${LIBFTD} clean
			make -C ${LIBGNLD} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFTD}${LIBFTL}
			${RM} ${LIBGNLD}${LIBGNLL}
			@${RM} ${HEADD}miniRT.h.gch
			@rm -rf miniRT.dSYM

re:			fclean all

.PHONY:		all clean fclean re