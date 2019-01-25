# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/25 12:18:28 by wbraeckm          #+#    #+#              #
#    Updated: 2019/01/25 12:34:01 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM = asm
NAME_VM = vm
CC = gcc
FLAGS = -O3 -Wall -Wextra -Werror
INCLUDES = ./includes/
SRCSFOLDER = ./srcs/
OBJFOLDER = ./obj/
LIBFOLDER = ./libft/
LIBINCLUDES = ./libft/includes/
LIBFT = $(LIBFOLDER)libft.a

ITEMS = $(shell find srcs -type f | grep -E "\.c$$" | sed 's/srcs//g')
SRCS = $(addprefix $(SRCSFOLDER), $(ITEMS))
OBJ = $(addprefix $(OBJFOLDER), $(ITEMS:.c=.o))
SRCSUBS = $(shell find ./srcs -type d)
OBJSUBS = $(SRCSUBS:./srcs%=./obj%)
LONGEST = $(shell echo $(notdir $(SRCS)) | tr " " "\n" | \
	awk ' { if ( length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

ASMOBJ = $(shell find srcs/common srcs/asm -type f | grep -E "\.c$$" \
| sed -e 's/^srcs/obj/g' | sed 's/.c$$/.o/g')
VMOBJ = $(shell find srcs/common srcs/vm -type f | grep -E "\.c$$" \
| sed -e 's/^srcs/obj/g' | sed 's/.c$$/.o/g')

ccblue = "\33[0;34m"
ccred = "\033[0;91m"
ccgreen = "\033[0;92m"
ccgreenhard = "\033[0;32m"
cccyan = "\033[0;96m"
ccreset = "\033[0;0m"
cclightgray = "\033[0;37m"

all: lib $(NAME_ASM) $(NAME_VM)

$(OBJFOLDER)/%.o:$(SRCSFOLDER)/%.c
	@printf $(ccblue)
	@printf "Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -I$(LIBINCLUDES)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "\r"

$(OBJSUBS):
	@mkdir $@

lib:
	@make -C $(LIBFOLDER)

$(NAME_ASM): $(OBJSUBS) $(OBJ)
	@printf $(cccyan)
	@printf "Compiling $(NAME_ASM) "
	@$(CC) $(FLAGS) -o $(NAME_ASM) $(ASMOBJ) -I$(INCLUDES) \
-I$(LIBINCLUDES) $(LIBFT)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "                                                     \n"

$(NAME_VM): $(OBJSUBS) $(OBJ)
	@printf $(cccyan)
	@printf "Compiling $(NAME_VM) "
	@$(CC) $(FLAGS) -o $(NAME_VM) $(VMOBJ) -I$(INCLUDES) \
-I$(LIBINCLUDES) $(LIBFT)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "                                                     \n"

clean:
	@printf $(ccred)
	rm -rf obj/
	@make -C $(LIBFOLDER) clean
	@printf $(ccreset)

fclean: clean
	@printf $(ccred)
	rm -rf $(NAME_ASM) $(NAME_VM)
	@make -C $(LIBFOLDER) fclean
	@printf $(ccreset)

re: fclean all

norm:
	@norminette $(SRCSFOLDER) $(INCLUDES)

.PHONY: norm clean fclean re
