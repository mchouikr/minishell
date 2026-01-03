# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 19:19:07 by edelplan          #+#    #+#              #
#    Updated: 2026/01/03 11:48:13 by mchouikr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
SRCS =  srcs/builtins/cd_builtin.c srcs/builtins/echo_builtin.c \
		srcs/builtins/env_builtin.c srcs/builtins/export_builtin.c \
		srcs/builtins/unset_builtin.c srcs/builtins/pwd_builtin.c \
		srcs/builtins/exit_builtin.c srcs/front/front.c  srcs/minishell.c \
		srcs/parsing/token_parsing_helper.c srcs/exec/exec.c \
		srcs/exec/exec_utils_2.c srcs/exec/exec_utils.c \
		srcs/exec/close_and_wait.c srcs/exec/exec_init.c \
		srcs/exec/data_init.c srcs/exec/is_valid.c srcs/exec/redirections.c \
		srcs/exec/heredoc.c srcs/exec/dup_and_close.c srcs/exec/child.c \
		srcs/exec/single_builtin.c srcs/minishell_utils.c \
		srcs/env/env.c ./srcs/parsing/ft_tokenizer.c \
		srcs/parsing/builtin_parsing.c srcs/parsing/exec_parsing.c \
		srcs/parsing/input_parsing.c srcs/parsing/token_parsing.c \
		srcs/parsing/ft_tokenizer_helper.c srcs/signal/signal_parsing.c \
		srcs/signal/signal_parsing_helper.c srcs/parsing/init_and_free.c \
		srcs/parsing/ft_tokenizer_helper2.c \
		srcs/parsing/token_parsing_helper2.c \
		srcs/parsing/var_expansion_helper.c srcs/parsing/var_expansion.c \
		srcs/parsing/process_quotes.c srcs/parsing/init_and_free2.c \
		srcs/parsing/init_and_free3.c srcs/minishell_utils2.c srcs/minishell_utils3.c\
		srcs/builtins/export_builtin_helper.c srcs/builtins/cd_builtin_helper.c \
		srcs/exec/child_helper.c srcs/exec/single_builtin_helper.c srcs/exec/heredoc_helper.c\

OBJS = ${SRCS:.c=.o}
INCLUDE = -I includes
RM = rm -rf
CLANG = cc
FLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -L$(LIBFT) -lft -lreadline
VALGRIND ?= valgrind
VALGRIND_FLAGS ?= --leak-check=full --show-leak-kinds=all --track-origins=yes
WHITE = \033[0;37m
GREEN = \033[0;32m
LIBFT = ./libft
DOCKER_IMAGE ?= minishell
DOCKER_MOUNT = -v "$(CURDIR)":/workspace
DOCKER_RUN = docker run --rm -it $(DOCKER_MOUNT) $(DOCKER_IMAGE)

.c.o:
	@echo -n "${WHITE}Compiling objects from $< : "
	@$(CLANG) $(FLAGS) -c $< -o $@ $(INCLUDE)
	@echo "${GREEN}Done!"

all:
	@$(MAKE) --no-print-directory -C libft
	@$(MAKE) --no-print-directory $(NAME)

$(NAME): $(OBJS)
	@echo "${WHITE}Building $(NAME)"
	@$(CLANG) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "${GREEN}$(NAME) built successfully!"

clean:
	@$(MAKE) clean --no-print-directory -C libft
	@echo "${WHITE}Cleaning up object files"
	@$(RM) $(OBJS)
	@echo "${GREEN}Object files cleaned!"

fclean: clean
	@echo "${WHITE}Cleaning up libft"
	@$(RM) libft/libft.a
	@echo "${WHITE}Cleaning up all generated files"
	@$(RM) $(NAME)
	@echo "${GREEN}All generated files cleaned!"


re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
	@echo "😎😎😎 RELINKING DONE! 😎😎😎"

valgrind: $(NAME)
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

docker-build:
	@docker build -t $(DOCKER_IMAGE) .

docker-shell:
	@$(DOCKER_RUN)

docker-make:
	@$(DOCKER_RUN) bash -lc "make fclean && make"

.PHONY: all clean fclean re make valgrind docker-build docker-shell docker-make
