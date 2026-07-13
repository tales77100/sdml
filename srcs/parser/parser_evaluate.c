#include "compiler.h"

bool	is_valide_decl(Parser *parser)
{
	while (parser->tokens[parser->current].type == TOKEN_STAR)
		parser->current++;
	if (!(parser->tokens[parser->current].type == TOKEN_IDENTIFIER))
		return (false);
	parser->current++;
	while (parser->tokens[parser->current].type != TOKEN_COMMA
		|| parser->tokens[parser->current].type != TOKEN_RPAREN)
	{
		if (parser->tokens[parser->current].type != TOKEN_COLON)
			return (false);
		if (parser->tokens[++(parser->current)].type != TOKEN_IDENTIFIER)
			return (false);
		parser->current += 2;
	}
	return (true);
}

bool    eval_func(Parser *parser)
{
	while (parser->tokens[parser->current].type != TOKEN_FUNC)
		parser->current++;
	parser->current++;
	while (parser->tokens[parser->current].type != TOKEN_INDENT && parser->current < parser->count)
	{
		if ((parser->tokens[parser->current].type != TOKEN_IDENTIFIER
			|| parser->tokens[parser->current + 1].type != TOKEN_LPAREN))
			return (false);
		parser->current += 2;
		while (parser->current < parser->count && parser->tokens[parser->current].type != TOKEN_RPAREN)
		{
			if (!is_valide_decl(parser))
				return (false);
			if (parser->tokens[parser->current].type != TOKEN_COMMA
				|| parser->tokens[parser->current].type != TOKEN_RPAREN
				|| parser->tokens[parser->current].type != TOKEN_STAR)
				return (false);
		}
		parser->current++;
	}
	if (parser->current < parser->count)
		return (false);
	return (true);
}


bool    evaluate_parsing(Parser *parser)
{
    size_t i = parser->current;
    while (i < parser->count)
    {
        if (parser->tokens[i].type == TOKEN_FUNC && !(eval_func(parser)))
            return (false);
        // else if (parser->tokens[i].type == TOKEN_CLASS && !(eval_class(parser)))
        //     return (false);
        // else if (parser->tokens[i].type == TOKEN_IF && !(eval_if(parser)))
        //     return (false);
        // else if (parser->tokens[i].type == TOKEN_ELSE && !(eval_else(parser)))
        //     return (false);
        // else if (parser->tokens[i].type == TOKEN_WHILE && !(eval_while(parser)))
        //     return (false);
        // else if (parser->tokens[i].type == TOKEN_PRIVATE && !(eval_class_memb(parser)))
        //     return (false);
        // else if (parser->tokens[i].type == TOKEN_PUBLIC && !(eval_class_memb(parser)))
        //     return (false);
        else
            i++;
    }
    return (true);
}