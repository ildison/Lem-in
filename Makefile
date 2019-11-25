# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cormund <cormund@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 12:44:34 by cormund           #+#    #+#              #
#    Updated: 2019/11/25 16:51:23 by cormund          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lem-in
LIBFT := libft.a
HEADERS := libft.h lem_in.h
CC := clang
CFLAGS := -Wall -Wextra -Werror -O3 -g
REMOVE := /bin/rm -rf
DIR_BIN := bin
DIR_INCLUDE := -I include
DIR_LIBS := src/libs
DIR_LIBFT := $(DIR_LIBS)/libft
DIR_SRC := src/$(NAME)

# DIR_SDLLIBS := $(DIR_LIBS)/libSDL2
# DIR_INCLUDE_SDL := -I $(DIR_SDLLIBS)/SDL2.framework/Headers -I $(DIR_SDLLIBS)/SDL2_ttf.framework/Headers
# SDL_LIBS := -Wl,-rpath,$(DIR_SDLLIBS) -F $(DIR_SDLLIBS) -framework SDL2 -framework SDL2_ttf

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)/$(NAME)
vpath %.h $(DIR_INCLUDE)
vpath %.a $(DIR_LIBFT)

SRC_NAME := lem-in.c\
			read_input.c\
			parsing.c\
			adjacencies.c\
			suurballe.c\
			bfs.c\
			queue.c\
			check_paths.c\
			validation.c\
			push_ants_cormund.c
			# push_ants.c

# SRC_VIS := visualization.c\
# 			loop.c\
# 			render.c\
# 			steps.c\
# 			background.c

OBJ_NAME := $(SRC_NAME:.c=.o)
# OBJ_VIS := $(SRC_VIS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_NAME)
	@$(CC) $(CFLAGS) $(addprefix $(DIR_BIN)/, $(addprefix $(NAME)/, $(OBJ_NAME))) -lft -L $(DIR_LIBFT) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(OBJ_NAME): %.o: %.c $(HEADERS)
	@mkdir -p $(DIR_BIN)/$(NAME)
	@$(CC) $(CFLAGS) -c $< $(DIR_INCLUDE) -o $(DIR_BIN)/$(NAME)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

# $(OBJ_VIS): %.o: %.c $(HEADERS)
# 	@mkdir -p $(DIR_BIN)/$(VISUAL)
# 	@$(CC) $(CFLAGS) -c $< $(DIR_INCLUDE) $(DIR_INCLUDE_SDL) -o $(DIR_BIN)/$(VISUAL)/$@
# 	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

$(LIBFT):
	@$(MAKE) -C $(DIR_LIBFT)
	@$(MAKE) -C $(DIR_LIBFT) clean

clean:
	@rm -rf $(DIR_BIN)
	@$(MAKE) -C $(DIR_LIBFT) fclean

fclean: clean
	@$(REMOVE) $(NAME)
	@$(REMOVE) $(PUSH_SWAP)

re: fclean all
