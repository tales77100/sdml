#include "compiler.h" 

void	free_all_tokens(Token *tokens, size_t count)
{
	for (size_t i = 0; i < count; i++)
		free_sds(tokens[i].lex);
	free(tokens);
}

int	main(int ac, char *av[])
{
	if (ac < 2)
	{
		fprintf(stderr, "sdmlc: ERROR: not enough arguments:\n ./sdmlc <file_name>.sdm ...\n");
		return (1);
	}
	Files	*head = make_file_nodes(av + 1);
	Parser *new_parser = launch_new_parser(head);
	parse(new_parser);
	free_sds(head->filename);
	free_all_tokens(new_parser->tokens, new_parser->count);
	free(head);
	free(new_parser);
	return (0);
}