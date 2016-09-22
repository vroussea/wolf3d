# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 09:55:27 by vroussea          #+#    #+#              #
#    Updated: 2016/09/22 22:15:20 by vroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE =		wolf3d
INCLUDES =	libft/libft.a
HEADER =	wolf.h
MKINC =		make -C libft/
MLX =		-lmlx -framework OpenGL -framework AppKit
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
SOURCES =	main.c file_reader.c event.c minimap.c draw.c line.c tools.c
OBJS =		$(SOURCES:.c=.o)

all :		$(EXE)
$(EXE) :	$(OBJS) $(HEADER) Makefile
			$(MKINC)
			$(CC) $(CFLAGS) -c $(SOURCES)
			$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(INCLUDES) $(MLX)
norm :
			norminette $(SOURCES) $(HEADER)
meteo :
			curl http://wttr.in/Paris
clean :
			-rm -f $(OBJS)
fclean :	clean
			$(MKINC) fclean
			-rm -f $(EXE)
re :		fclean all
