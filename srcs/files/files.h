#ifndef FILES_H
# define FILES_H

# include "compiler.h"

typedef struct  s_files{
        sds     filename;
        struct s_files *next;
        struct s_files *prev;
}               Files;


#endif
