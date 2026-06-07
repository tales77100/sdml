#include "compiler.h"

TokenArray	*creat_dynamic_token(void)
{
	TokenArray	*ret = calloc(sizeof(TokenArray), 1);
	if (!ret)
		return (NULL);
	ret->data = malloc(sizeof(Token) * 2);
	if (!ret->data)
		return (free(ret), NULL);
	ret->capacity = 2;
	ret->curr = 0;
	return (ret);
}

Token	*peek_token(TokenArray *arr, size_t offset)
{
	if (arr->curr + offset >= arr->count)
		return (NULL);
	return (&arr->data[arr->curr + offset]);
}

void push_token(TokenArray* arr, Token token)
{
    if (arr->count >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, sizeof(Token) * arr->capacity);
    }
    arr->data[arr->count++] = token;
}

TokenArray	*tokenize(Lexer *lexer)
{
	TokenArray	*tokens = creat_dynamic_token();
	Token		*token;

	while ((token = get_next_token(lexer)) != NULL)
		push_token(tokens, *token);
	free_sds(lexer->src);
	return (tokens);
}