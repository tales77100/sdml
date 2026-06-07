#ifndef COMPILER_H
# define COMPILER_H

# include "sds.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "../srcs/lexer/token.h"
# include "../srcs/parser/parser.h"
# include "../srcs/lexer/lexer.h"
# include "../srcs/files/files.h"

Files *make_file_nodes(char **files);
Parser *launch_new_parser(Files *head);
Parser	*parse(Parser *parser);

#endif
