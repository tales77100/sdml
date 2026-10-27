FILE_FILES = srcs/File/File.c

AST_FILES = srcs/AST/AST.c \

PARSER_FILES = srcs/Parser/Parser.c \
		srcs/Parser/Lexer.c 		\

FILES = $(FILE_FILES)	\
		$(PARSER_FILES)	\
		$(AST_FILES)	\
		srcs/main.c

BUILDDIR = build/
OBJ = $(FILES:%.c=$(BUILDDIR)%.o)

CFLAGS = -Wall -Wextra -Werror -Iincludes -g3
CC = cc

NAME = sdmlc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILDDIR)$(NAME)

$(BUILDDIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

re: clean all

run: re $(NAME)
	$(BUILDDIR)$(NAME) main.sdm

.PHONY: all clean fclean re run
