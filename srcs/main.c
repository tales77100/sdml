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
	Parser parser;
	File *files = getFiles(av);
	if (!files)
		return (putERROR(FILEERROR), 1);
	if (!parseInput(&parser, files))
		return (freeFiles(files), 1);
	AST ast;
	freeFiles(files);
	if (!createAST(&parser, &ast))
		return (freeParser(parser), 1);
	return (makeBin(&ast));
}