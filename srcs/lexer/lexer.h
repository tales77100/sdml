#ifndef LEXER_H
# define LEXER_H


# include <ctype.h>

struct s_files;

typedef struct s_lexer {
	sds     src;
	size_t  pos;
	size_t  cur;
	int     line;
	int     column;
	int     indent_level;
	int     pending_indent;
}   Lexer;

Lexer	*get_full_lex(struct s_files *head);
Token	*get_next_token(Lexer *lexer);
Token_type	get_token_type(sds token_lex);
int	is_token_char(char c);
Token	*new_token(Token_type type, sds lex, int line, int column);
Token	*get_token(Lexer *lexer);

#endif
