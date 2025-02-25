ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fPIC
NAME = libft_malloc_$(HOSTTYPE).so
HEADER = inc/malloc.h libft/libft.h
SRCS = src/free.c \
	   src/malloc.c \
	   src/realloc.c \
	   src/block_operations.c \
	   src/create_new.c \
	   src/helper.c \
	   src/show_alloc_mem.c \
	   src/search.c \
	   src/print_infos.c
OBJS = ${SRCS:.c=.o}
DSRCS = ./libft/*.c
DOBJS = ${DSRCS:.c=.o}
LINK = libft_malloc.so

all : ${NAME}
%.o : %.c ${HEADER}
	$(CC) -c $(CFLAGS) $<
	mv *.o src/
$(NAME) : $(OBJS)
	make -C libft
	ar -rc $@ $(OBJS) $(DOBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(DOBJS)
	rm -f $(LINK)
	ln -s $(NAME) $(LINK)
clean :
	make clean -C libft 
	rm -f $(OBJS)
fclean : clean
	rm -f $(LINK)
	rm -f libft/libft.a
	rm -f $(NAME)
re : fclean all
