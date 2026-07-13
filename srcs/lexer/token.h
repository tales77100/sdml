#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

typedef struct s_lexer Lexer;

typedef enum {
	TOKEN_EOF,

	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_STRING,

	TOKEN_FUNC,
	TOKEN_CLASS,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_RETURN,
	TOKEN_PUBLIC,
	TOKEN_PRIVATE,
	TOKEN_INT_LITERAL,
	TOKEN_FLOAT_LITERAL,
	TOKEN_DO,

	TOKEN_COLON,
	TOKEN_SEMICOLON,
	TOKEN_COMMA,
	TOKEN_DOT,
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
	TOKEN_NEWLINE,
}	Token_type;

typedef struct s_token {
	Token_type		type;
	char			*lex;
	int			line;
	int			column;
}       Token;

typedef struct {
    Token	*data;
    size_t	count;
    size_t	capacity;
    size_t	curr;
}		TokenArray;

TokenArray	*creat_dynamic_token(void);
void push_token(TokenArray* arr, Token token);
TokenArray	*tokenize(Lexer *lexer);

#endif
