#include "compiler.h"

sds	read_whole_file(char *filename)
{
	sds	ret = new_string("");
	int	fd;
	sds buff = new_string(" ");
	buff[1] = '\0';

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	while (read(fd, buff, 1) > 0)
		ret = sdscat(ret, buff);
	if (read(fd, buff, 1) == -1)
		return (free_sds(buff), free_sds(ret), NULL);
	return (free_sds(buff), ret);
}

Lexer	*get_full_lex(Files *files)
{
	sds	ret = new_string("");
	Lexer	*lex = calloc(sizeof(Lexer), 1);

	while (files && files->filename)
	{
		//if (sdslen(files->filename) < 3 || strcmp(&(files->filename[sdslen(files->filename) - 4]), ".sdm"))
			//return (free_sds(ret), free(lex), NULL);
		ret = sdsjoin(ret, read_whole_file(files->filename), 3);
		ret = sdscat(ret, "\n");
		files = files->next;
	}
	lex->src = ret;
	return (lex);
}

Token_type	get_token_type(sds token_lex)
{
	if (!token_lex)
		return (TOKEN_IDENTIFIER);
	if (strcmp(token_lex, "\n") == 0)
		return (TOKEN_NEWLINE);
	if (strcmp(token_lex, "func") == 0)
		return (TOKEN_FUNC);
	if (strcmp(token_lex, "class") == 0)
		return (TOKEN_CLASS);
	if (strcmp(token_lex, "if") == 0)
		return (TOKEN_IF);
	if (strcmp(token_lex, "while") == 0)
		return (TOKEN_WHILE);
	if (strcmp(token_lex, "return") == 0)
		return (TOKEN_RETURN);
	if (strcmp(token_lex, "public") == 0)
		return (TOKEN_PUBLIC);
	if (strcmp(token_lex, "private") == 0)
		return (TOKEN_PRIVATE);
	if (strcmp(token_lex, ":") == 0)
		return (TOKEN_COLON);
	if (strcmp(token_lex, ";") == 0)
		return (TOKEN_SEMICOLON);
	if (strcmp(token_lex, ",") == 0)
		return (TOKEN_COMMA);
	if (strcmp(token_lex, ".") == 0 || strcmp(token_lex, "...") == 0)
		return (TOKEN_DOT);
	if (strcmp(token_lex, "->") == 0)
		return (TOKEN_ARROW);
	if (strcmp(token_lex, "(") == 0)
		return (TOKEN_LPAREN);
	if (strcmp(token_lex, ")") == 0)
		return (TOKEN_RPAREN);
	if (strcmp(token_lex, "+") == 0)
		return (TOKEN_PLUS);
	if (strcmp(token_lex, "-") == 0)
		return (TOKEN_MINUS);
	if (strcmp(token_lex, "*") == 0)
		return (TOKEN_STAR);
	if (strcmp(token_lex, "/") == 0)
		return (TOKEN_SLASH);
	if (strcmp(token_lex, "=") == 0)
		return (TOKEN_EQUAL);
	if (strcmp(token_lex, "==") == 0)
		return (TOKEN_EQUAL_EQUAL);
	return (TOKEN_IDENTIFIER);
}

Token	*new_token(Token_type type, sds lex, int line, int column)
{
	Token	*token = malloc(sizeof(Token));

	token->type = type;
	token->lex = lex;
	token->line = line;
	token->column = column;
	return (token);
}
Token	*get_token(Lexer *lexer)
{
	sds	token_lex = NULL;
	size_t	token_len;

	token_len = lexer->pos - lexer->cur;
	token_lex = subsds(lexer->src, lexer->cur, token_len);
	Token_type	type = get_token_type(token_lex);
	lexer->column += token_len;
	lexer->cur = lexer->pos;
	return (new_token(type, token_lex, lexer->line, lexer->column - token_len));
}

int	is_token_char(char c)
{
	return (isalnum((unsigned char)c) || c == '_');
}

void	skip_unused_chars(Lexer *lexer)
{
	while (lexer->src[lexer->pos] && (lexer->src[lexer->pos] == ' ' || lexer->src[lexer->pos] == '\t' || lexer->src[lexer->pos] == '\r'))
	{
		lexer->column++;
		lexer->pos++;
	}
	lexer->cur = lexer->pos;
}

Token	*get_next_token(Lexer *lexer)
{
	char c;
	const int INDENT_WIDTH = 2;

	/* At start of a line, detect leading spaces/tabs as indentation */
	if (lexer->column == 0)
	{
		size_t i = lexer->pos;
		int space_count = 0;
		while (lexer->src[i] == ' ' || lexer->src[i] == '\t')
		{
			if (lexer->src[i] == ' ')
				space_count += 1;
			else
				space_count += INDENT_WIDTH;
			i++;
		}
		int level = space_count / INDENT_WIDTH;
		int delta = level - lexer->indent_level;
		if (delta != 0)
		{
			lexer->pending_indent = delta;
			/* consume the indent characters so they don't appear as tokens */
			lexer->pos = i;
			lexer->column = space_count;
		}
	}

	/* If there are pending indent/dedent tokens, emit them one by one */
	if (lexer->pending_indent != 0)
	{
		if (lexer->pending_indent > 0)
		{
			lexer->pending_indent--;
			lexer->indent_level++;
			return (new_token(TOKEN_INDENT, new_string("{"), lexer->line, lexer->column));
		}
		else
		{
			lexer->pending_indent++;
			lexer->indent_level--;
			return (new_token(TOKEN_DEDENT, new_string("}"), lexer->line, lexer->column));
		}
	}

	/* Skip inline whitespace (spaces/tabs/carriage returns) between tokens */
	skip_unused_chars(lexer);
	c = lexer->src[lexer->pos];
	if (!c)
		return (NULL);

	lexer->cur = lexer->pos;
	if (isalnum((unsigned char)c) || c == '_')
	{
		while (lexer->src[lexer->pos] && (isalnum((unsigned char)lexer->src[lexer->pos]) || lexer->src[lexer->pos] == '_'))
			lexer->pos++;
	}
	else if (c == '-' && lexer->src[lexer->pos + 1] == '>')
		lexer->pos += 2;
	else if (c == '=' && lexer->src[lexer->pos + 1] == '=')
		lexer->pos += 2;
	else
		lexer->pos++;

	Token *tok = get_token(lexer);
	if (tok && tok->lex && tok->lex[0] == '\n' && tok->lex[1] == '\0')
	{
		lexer->line++;
		lexer->column = 0;
	}
	if (tok && tok->lex && tok->lex[0] && (isdigit((unsigned char)tok->lex[0]) || (tok->lex[0] == '-' && isdigit((unsigned char)tok->lex[1]))))
	{
		int is_float = 0;
		for (size_t i = 0; tok->lex[i]; i++)
		{
			if (tok->lex[i] == '.')
			{
				is_float = 1;
				break;
			}
		}
		tok->type = is_float ? TOKEN_FLOAT_LITERAL : TOKEN_INT_LITERAL;
	}
	if (strcmp(tok->lex, "do") == 0)
		tok->type = TOKEN_DO;
	return (tok);
}

