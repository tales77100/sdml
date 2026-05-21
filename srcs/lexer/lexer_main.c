#include "compiler.h"

sds	read_whole_file(char *filename)
{
	sds	ret = NULL;
	int	fd;
	char	buff[1];

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	while (read(fd, buff, 1) > 0)
		ret = sdsjoin(ret, buff, 1);
	if (read(fd, buff, 1) == -1)
		return (free_sds(ret), NULL);
	return (ret);
}

Lexer	*get_full_lex(Files *files)
{
	sds	ret = NULL;
	Lexer	*lex = calloc(sizeof(Lexer), 1);

	while (files->filename)
	{
		if (sdslen(files->filename) < 4 || strcmp(&(files->filename[sdslen(files->filename) - 3]), ".sdm"))
			return (free_sds(ret), free(lex), NULL);
		ret = sdsjoin(ret, read_whole_file(files->filename), 3);
		ret = sdsjoin(ret, "\n", 1);
		files = files->next;
	}
	lex->src = ret;
	return (lex);
}



Token	*get_next_token(Lexer *lexer)
{
	
}
