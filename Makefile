# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 19:48:19 by jdeathlo          #+#    #+#              #
#    Updated: 2020/02/23 13:32:17 by jdeathlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
# Why? Because I don't like 42's restrictions on how to build projects. >:-(
#

TARGET := minishell
BUILD_DIR := build

$(TARGET):
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(BUILD_DIR) --target all
	@cp build/$(TARGET) $(TARGET)

all: $(TARGET)

clean:
	@$(RM) -rf build

fclean: clean
	@$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
