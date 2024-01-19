# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 16:06:19 by marobert          #+#    #+#              #
#    Updated: 2023/09/27 14:06:12 by jalamell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Colors from https://misc.flogisoft.com/bash/tip_colors_and_formatting#colors1
RED			=	\e[31m
GREEN		=	\e[32m
CYAN		=	\e[34m
IGREY		=	\e[48;5;249m
END			=	\e[0m
ERASE		=	\e[2K\r


DIR_INCS	=	srcs/header
SRC_DIR		=	srcs
SRC_FILES	=	main.cpp Game.cpp Rotation.cpp
LDFLAGS		=	-Lsrcs/lib -lftxui-screen -lftxui-dom -lftxui-component
FTXUI_MAKE	=	FTXUI-5.0.0/build/Makefile

SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
DIR_BUILD	=	.build/
OBJS		=	$(patsubst %.cpp, $(DIR_BUILD)%.o, $(SRCS))

DEPS		=	$(patsubst %.cpp, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS	=	-MMD -MP
CC			=	c++
RM			=	rm -rf
CFLAGS		=	-std=c++17 $(KEYBOARD:%=-D %=1) -Wall -Wextra -Werror
NAME		=	tetris

all:		$(NAME)

run:		all
			./tetris

$(NAME):	$(FTXUI_MAKE) $(OBJS)
			@printf "[$(CYAN)Compiling$(END)] % 25s" $(NAME)
			@$(CC) $(CFLAGS) $(DIR_INCS:%=-I %) -o $(NAME) $(OBJS) $(LIBS) $(LDFLAGS)
			@printf "$(ERASE)[$(GREEN)Done$(END)] % 30s\n" $(NAME)

$(FTXUI_MAKE):
			mkdir -p FTXUI-5.0.0/build srcs/lib
			cd FTXUI-5.0.0/build && cmake ..
			cd FTXUI-5.0.0/build && make -j
			cp FTXUI-5.0.0/build/{libftxui-component.a,libftxui-dom.a,libftxui-screen.a} srcs/lib/

-include $(DEPS)

$(DIR_BUILD)%.o : %.cpp
			@printf "[$(CYAN)Compiling$(END)] % 25s" $(patsubst $(shell dirname $<)/%, %, $<)
			@mkdir -p $(shell dirname $@)
			@$(CC) $(CFLAGS) $(DEPS_FLAGS) $(DIR_INCS:%=-I %) -c $< -o $@
			@printf "$(ERASE)[$(GREEN)Done$(END)] % 30s\n" $(patsubst $(shell dirname $<)/%, %, $<)

clean:
			@$(RM) $(DIR_BUILD)
			@printf "[$(RED)Deleted$(END)] % 27s\n" "$(NAME) objects"

fclean:		clean
			@$(RM) $(NAME)
			@printf "[$(RED)Deleted$(END)] % 27s\n" $(NAME)

re:			fclean
			@make all

.PHONY: norme
norme:
			norminette $(SRCS) $(DIR_INCS) | grep -v 'OK!' | cat

.PHONY: shrek
shrek:
		@echo "$(GREEN)⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ "
		@echo "⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ "
		@echo "⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ "
		@echo "⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
		@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉$(END)"

.PHONY:		all clean fclean re run
