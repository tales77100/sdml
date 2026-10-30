#include "../includes/sdmllang.h"


int TODO(const char *msg)
{
	write(1, "[ TODO ]: ", 11);
	write(1, msg, strlen(msg));
	return (1);
}

int	howToUse()
{
	TODO("write a pretty message for user who can't use a compiler\n");
	return (0);
}

int putERROR(const char *msg)
{
	write(1, msg, strlen(msg));
	return (0);
}

int main(int ac, char **av)
{
	if (ac < 2) return (howToUse());
	if (ac > 3) return (TODO("implement multi files as an input\n"));
	File *files = getFiles(av);
	if (!files)
		return (putERROR(FILEERROR), 1);
	Lexer lexer = {0};
	if (!parseInput(&lexer, files))
		return (freeFiles(files), 1);
	AST ast;
	freeFiles(files);
	if (!createAST(&lexer, &ast))
		return (freeLexer(&lexer), 1);
	return (makeBin(&ast));
}