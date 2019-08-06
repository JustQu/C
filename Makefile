CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror\
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)

LDLIBS = -lft\
		-L$(LIBFTDIR)\
		-lmlx\
		-framework OpenGL\
		-framework AppKit
LDFLAGS	= 

LIBFT = libft.a
LIBFTDIR = ./libft
LIBFTINC = $(LIBFTDIR)/includes

INCDIR = ./include
SRCSDIR = srcs/
SRCS = draw.c get_color.c graphics.c key_event.c main.c matrix3.c read.c rotate_map.c\
		rotation_matrix.c
OBJS = $(SRCS:.c=.o)
TARGET = fdf

.PHONY: all
all: $(LIBFT) $(TARGET)

$(LIBFT):
	make -C $(LIBFTDIR)

$(TARGET): $(OBJS) $(LIB)
	@echo 'making executable'
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
	@echo DONE!

$(OBJS): %.o: $(SRCSDIR)%.c $(INCDIR)/fdf.h
	@$(CC) -c $< $(CFLAGS) 

$(INCDIR)/fdf.h:

.PHONY: clean
clean:
	@echo deliting object files
	@$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(TARGET)
	@make -C $(LIBFTDIR) fclean

.PHONY: re
re:	fclean all
