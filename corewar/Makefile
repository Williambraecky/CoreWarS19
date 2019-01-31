# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrouvroy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/22 14:23:31 by nrouvroy          #+#    #+#              #
#    Updated: 2019/01/31 10:52:46 by sde-spie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		:=	./src
INC_DIR		:=	./includes
OBJ_DIR		:=	./obj
LIBFT_DIR	:=	../libft

INC			:=	-I $(INC_DIR)/
LIB_LNK		:=	-L $(LIBFT_DIR) -lft
LIB_INC		:=	-I $(LIBFT_DIR)/includes
LIB_INC		+=	$(INC)

SRC			:=	corewar.c\
				error.c\
				op.c\
				parse_command.c\
				utils.c\
				read_champ.c\
				prepare_battle.c\
				create_process.c\
				init_vm.c\
				introduce_champs.c\
				do_cycle.c\
				read_instruction.c

OBJ			:=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC			:=	gcc -g
CFG			:=	-O3
CFG			+=	-Wall -Wextra
CFG			+=	#-fsanitize=address
NAME		:=	corewar

# rules

all: $(NAME)

lib:
	@$(MAKE) -C $(LIBFT_DIR) re
	@echo "\033[1;34mcorewar\t\033[1;33mLIB\t\t\033[0;32m[OK]\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(CFG) $(LIB_INC) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) -o $(NAME) $(CFG) $(OBJ) $(LIB_LNK)
	@echo "\033[1;34mcorewar\t\033[1;33mExecutable\t\033[0;32m[OK]\033[0m"

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;34mcorewar\t\033[1;33mCleaning\t\033[0;32m[OK]\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[1;34mcorewar\t\033[1;33mFull Cleaning\t\033[0;32m[OK]\033[0m"

re: fclean all

.PHONY: all clean fclean re lib
