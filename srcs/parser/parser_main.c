#include "compiler.h"

Parser *launch_new_parser(Files *head)
{
	Parser *parser = calloc(sizeof(Parser), 1);
	if (!parser)
		return (NULL);
	Lexer *lexer = get_full_lex(head);
	if (!lexer)
		return (free(parser), NULL);
	TokenArray *tokens = tokenize(lexer);
	if (!tokens)
		return (free(parser), free(lexer->src), free(lexer), NULL);
	parser->tokens = tokens->data;
	parser->count = tokens->count;
	parser->current = 0;
	free(tokens);
	free(lexer);
	return (parser);
}

void	print_tokens(Parser *parser)
{
	for (size_t i = 0; i < parser->count - 1 ; i++)
	{
		const char *lex = parser->tokens[i].lex ? parser->tokens[i].lex : "(null)";
		if (parser->tokens[i].type == TOKEN_NEWLINE)
			lex = "\\n";
		const char *tname;
		switch (parser->tokens[i].type)
		{
			case TOKEN_EOF: tname = "TOKEN_EOF"; break;
			case TOKEN_IDENTIFIER: tname = "TOKEN_IDENTIFIER"; break;
			case TOKEN_NUMBER: tname = "TOKEN_NUMBER"; break;
			case TOKEN_STRING: tname = "TOKEN_STRING"; break;
			case TOKEN_FUNC: tname = "TOKEN_FUNC"; break;
			case TOKEN_CLASS: tname = "TOKEN_CLASS"; break;
			case TOKEN_IF: tname = "TOKEN_IF"; break;
			case TOKEN_WHILE: tname = "TOKEN_WHILE"; break;
			case TOKEN_RETURN: tname = "TOKEN_RETURN"; break;
			case TOKEN_PUBLIC: tname = "TOKEN_PUBLIC"; break;
			case TOKEN_PRIVATE: tname = "TOKEN_PRIVATE"; break;
			case TOKEN_COLON: tname = "TOKEN_COLON"; break;
			case TOKEN_SEMICOLON: tname = "TOKEN_SEMICOLON"; break;
			case TOKEN_COMMA: tname = "TOKEN_COMMA"; break;
			case TOKEN_DOT: tname = "TOKEN_DOT"; break;
			case TOKEN_ARROW: tname = "TOKEN_ARROW"; break;
			case TOKEN_LPAREN: tname = "TOKEN_LPAREN"; break;
			case TOKEN_RPAREN: tname = "TOKEN_RPAREN"; break;
			case TOKEN_PLUS: tname = "TOKEN_PLUS"; break;
			case TOKEN_MINUS: tname = "TOKEN_MINUS"; break;
			case TOKEN_STAR: tname = "TOKEN_STAR"; break;
			case TOKEN_SLASH: tname = "TOKEN_SLASH"; break;
			case TOKEN_EQUAL: tname = "TOKEN_EQUAL"; break;
			case TOKEN_EQUAL_EQUAL: tname = "TOKEN_EQUAL_EQUAL"; break;
			case TOKEN_INDENT: tname = "TOKEN_INDENT"; break;
			case TOKEN_DEDENT: tname = "TOKEN_DEDENT"; break;
			case TOKEN_NEWLINE: tname = "TOKEN_NEWLINE"; break;
			case TOKEN_INT_LITERAL: tname = "TOKEN_INT_LITERAL"; break;
			case TOKEN_FLOAT_LITERAL: tname = "TOKEN_FLOAT_LITERAL"; break;
			case TOKEN_DO: tname = "TOKEN_DO"; break;
			default: tname = "TOKEN_UNKNOWN"; break;
		}
		printf("Type: %s, Line: %d, Column: %d, Token: |%s|\n",
			tname, parser->tokens[i].line, parser->tokens[i].column, lex);
	}
	for (size_t i = 0; i < parser->count - 1 ; i++)
	{
		if (strcmp(parser->tokens[i].lex, "{") == 0)
			printf("<INDENT>");
		else if (strcmp(parser->tokens[i].lex, "}") == 0)
			printf("<DEDENT>");
		else
			printf("%s ", parser->tokens[i].lex);
	}
	printf("\n");
}

Parser	*parse(Parser *parser)
{
	print_tokens(parser);
	return (parser);
}