CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/
SRC			= get_next_line_utils.c get_next_line.c
# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF 		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD 		= $(OBJF:$(OBJD)%.o)

NAME		= libgnl.a
HEADD		= ./incl/
HEADF		= get_next_line.h


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