#ifndef TOKEN_H
# define TOKEN_H

# include "compiler.h"

typedef enum {
	TOKEN_EOF,
	
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_STRING,

	TOKEN_FUNC,
	TOKEN_CLASS,
	TOKEN_IF,
	TOKEN_WHILE,
	TOKEN_RETURN,
	TOKEN_PUBLIC,
	TOKEN_PRIVATE,

	TOKEN_COLON,
	TOKEN_SEMICOLON,
	TOKEN_ARROW,

	TOKEN_LPAREN,
	TOKEN_RPAREN,

	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,

	TOKEN_EQUAL,
	TOKEN_EQUAL_EQUAL,

	TOKEN_INDENT,
	TOKEN_DEDENT,
}	Token_type;

typedef struct {
	Token_type	type;
	char		*lex;
	int		line;
	int		column;
}		Token;

typedef struct {
    Token	*data;
    size_t	count;
    size_t	capacity;
}		TokenArray;

#endif
