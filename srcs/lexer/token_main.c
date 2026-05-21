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
	return (ret);
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
