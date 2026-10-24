#ifndef SDMLLANG
# define SDMLLANG

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define FILEREADSIZE 1000


# define FILEERROR "Couldn't read the file.\nEither because of permission or because the file doesn't exist.\n"

typedef struct s_File
{
    char *content; // malloced
    char *name; // this is from argv / av
    size_t size; // if one day I need this
    struct s_File *next; // pointer to next File object / next input file
}           File;

typedef enum e_Type
{
    WORD,
    INDENT,
    DEDNT,
    LPARENT,
    RPARENT,
    LBRACKET,
    RBRACKET,
    LCBRACKET,
    RCBRACKET,
    COMMA,
    SEMICO,
    GREATER_THAN,
    LOWER_THAN,
    EQUAL,
    COLON,
    SQUOTE,
    QUOTE,
    STAR,
    NLINE,
    UNDEFINED,
}           Type;

typedef struct s_Token
{
    size_t  startCollumn;
    size_t  startLine;
    Type    type;
}           Token;

typedef struct s_Lexer
{
    size_t  capacity;
    size_t  size;
    Token   *tokens;
}           Lexer;

typedef struct s_Parser
{
    
}           Parser;

typedef struct s_AST
{

}           AST;

int TODO(const char *str);
size_t sdml_strlen(const char *str);
int putERROR(const char *msg);


File *getFiles(char **names);
int sdml_strcpy(char *dest, char *src);
char *getWholeFile(char *name, size_t *size);
int freeFiles(File *files);


int parseInput(Parser *parser, File *files);
int freeParser(Parser parser);


int createAST(Parser *parser, AST *ast);



int makeBin(AST *ast);

#endif