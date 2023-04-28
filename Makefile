# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 13:19:05 by lumorale          #+#    #+#              #
#    Updated: 2023/04/27 12:06:25 by lumorale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -f
AR				=	ar -rcs

SRCS			=	src/philo.c \
					src/freerror.c \
					src/timer.c \
					src/threads.c \
					src/utils.c \
					
					

#		COLORS		#
CYELLOW			=\033[1;33m
CGREEN			=\033[0;32m
CRED			=\033[0;91m
PURPLE			=\033[0;35m
CRESET			=\033[0m

OBJS			=	$(SRCS:.c=.o)

%.o: %.c
				@$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(FLAGS) $(OBJS)   -o $(NAME)
				@echo "\n$(CYELLOW)$(NAME) $(PURPLE)-> $(CGREEN) compiled$(CRESET)"

bonus:			$(LIBFT) $(LINE)

clean:
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_B)
				@echo "${CYELLOW}${NAME} $(PURPLE)-> ${CRED} objects files were deleted.${CRESET}"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_B)
				@echo "${CYELLOW}${NAME} $(PURPLE)-> ${CRED} was deleted.${CRESET}"

re:				fclean all

.PHONY:			all clean fclean re bonus