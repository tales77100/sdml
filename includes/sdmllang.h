#ifndef SDMLLANG
# define SDMLLANG

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define FILEREADSIZE 1000


# define FILEERROR "Couldn't read the file.\nEither because of permission or because the file doesn't exist.\n"

typedef struct s_File
{
    char *content; // malloced
    char *name; // this is from argv / av
    size_t size; // if one day I need this
    struct s_File *next; // pointer to next File object / next input file
}           File;


 // I really need to replace this into a grammar json or smth
typedef enum e_Type
{
    WORD,
    SPACE,
    INDENT,
    DEDENT,
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
    PLUS,
    MINUS,
    PERCENT,
    DASH,
    QUOTE,
    STAR,
    NLINE,
    QUESTIONMARK,
    EXCLAMATIONMARK,
    AND,
    OR,
    RET,
    DOT,
    UNDEFINED,
}           Type;

typedef struct s_Token
{
    size_t  startCollumn;
    size_t  startLine;
    size_t  indexFromcontent;
    File    *file;
    char    *toString;
    Type    type;
    struct s_Token *next;
}           Token;

typedef struct s_Lexer
{
    Token   *tokens;
    Token   *last;
}           Lexer;

typedef struct s_Parser
{
    
}           Parser;

typedef struct s_AST
{

}           AST;

int TODO(const char *str);
int putERROR(const char *msg);


File *getFiles(char **names);
char *getWholeFile(char *name);
int freeFiles(File *files);
void printFile(File file);



int initLexer(Lexer *lexer, File *files);
void removeToken(Lexer *lexer, size_t index);
int cleanLexer(Lexer *lexer);
void printLexer(Lexer *lexer);
void freeLexer(Lexer *lexer);
int addToken(Lexer *lexer, size_t line, size_t collumn, Type type);
Type getTypeFromChar(char c);

int parseInput(Parser *parser, File *files);
int freeParser(Parser parser);


int createAST(Parser *parser, AST *ast);



int makeBin(AST *ast);

#endif