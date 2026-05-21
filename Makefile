FILE_FILES = srcs/files/files_creation.c

LEXER_FILES = srcs/lexer/lexer_main.c

PARSER_FILES = srcs/parser/parser_main.c

FILES = srcs/main.c	\
	$(FILE_FILES)	\
	$(LEXER_FILES)	\
	$(PARSER_FILES)	\

OBJETS = $(FILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I42_compatible_sds/includes -Iincludes -Isrcs/files  -Isrcs/parser  -Isrcs/lexer -g3

CC = cc

SDS_LIB = 42_compatible_sds/sds.a 

NAME = sdmlc

all: $(NAME)

$(NAME): $(OBJETS)
	make -C 42_compatible_sds
	$(CC) $(CFLAGS) $(OBJETS) $(SDS_LIB) -o $(NAME)

clean:
	make clean -C 42_compatible_sds
	rm -rf $(OBJETS)

fclean: clean
	make fclean -C 42_compatible_sds
	rm -rf $(NAME)

re: fclean all

run: re $(NAME)
	./sdmlc main.sdm

.PHONY: all clean fclean re bonus
