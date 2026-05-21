#ifndef LEXER_H
# define LEXER_H

# include "compiler.h"

typedef struct {
	sds		src;
	size_t		pos;
	size_t		cur;
	int		line;
	int		column;
}		Lexer;

#endif
