#ifndef PARSER_H
# define PARSER_H

# include "compiler.h"

typedef struct {
	struct Token* tokens;
	size_t count;
	size_t current;
}		Parser;

#endif
