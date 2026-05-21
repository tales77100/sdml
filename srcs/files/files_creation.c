#include "compiler.h"


Files   *new_file_node(char *file_name)
{
        Files   *ret = calloc(1, sizeof(Files));
        if (!ret)
                return (NULL);
        ret->filename = new_string(file_name);
        return (ret);
}

Files   *push_file_node(Files *head, Files *new)
{
        if (!head)
                return (new);
	if (!new)
		return (head);
        head->next = new;
        new->prev = head;
        return (new);
}

Files   *make_file_nodes(char **files)
{
        Files   *ret = NULL;
        while (*files)
        {
                ret = push_file_node(ret, new_file_node(*files));
                files++;
        }
        while (ret && ret->prev)
                ret = ret->prev;
	return (ret);
}
