NAME		=	ft_ssl

SRCS		= 	\
				main.c \
				parser.c \
				$(addprefix algorithms/, \
					$(addprefix md5/, \
						md5_intern.c \
						md5_extern.c \
					) \
				)

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

CC			=	clang
CFLAGS		=   -Wall -Wextra -Werror -g3
INCLUDE		=	-I includes/ -I libft

LIBFT		=	libft/libft.a

all		:	$(NAME)

$(LIBFT): FORCE
	make -C libft

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

-include $(OBJS_DEPEND)

clean	:	
	rm -Rf build/ $(TEST_NAME)


fclean	:	clean
	rm -f ${NAME}

fcleanlib: fclean
	make -C libft fclean

re		:	fclean
			make ${NAME}

relib	:	fcleanlib
			make ${NAME}

FORCE:

.PHONY	:	all clean fclean re FORCE fcleanlib relib