#include "compiler.h" 

int	main(int ac, char *av[])
{
	if (ac < 2)
	{
		fprintf(stderr, "sdmlc: ERROR: not enough arguments: ./sdmlc <file_name>.sdm ...");
		return (1);
	}
	Files	*head = make_file_nodes(av + 1);
	Parser *new_parser = launch_new_parser(head);
	(void)new_parser;
	return (0);
}
