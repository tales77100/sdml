#include "sdmllang.h"

Type getTypeFromChar(char c)
{
    switch (c)
    {
        case '(' : return LPARENT;
        case ')' : return RPARENT;
        case '[' : return LBRACKET;
        case ']' : return RBRACKET;
        case '{' : return LCBRACKET;
        case '}' : return RCBRACKET;
        case ',' : return COMMA;
        case ';' : return SEMICO;
        case '>' : return GREATER_THAN;
        case '<' : return LOWER_THAN;
        case '=' : return EQUAL;
        case '\r': return RET;
        case ':' : return COLON;
        case '\'': return SQUOTE;
        case '"' : return QUOTE;
        case '*' : return STAR;
        case '\n': return NLINE;
        case '\t': return INDENT;
        case '-' : return MINUS;
        case '+' : return PLUS;
        case '/' : return DASH;
        case '%' : return PERCENT;
        case ' ' : return SPACE;
        case '?' : return QUESTIONMARK;
        case '!' : return EXCLAMATIONMARK;
        case '.' : return DOT;
        case '&' : return AND;
        case '|' : return OR;
        default  : return UNDEFINED;
    }
}

int addToken(Lexer *lexer, size_t line, size_t collumn, Type type)
{
    Token *new = calloc(1, sizeof(Token));
    if (!new) return (0);
    new->startLine = line;
    new->startCollumn = collumn;
    new->type = type;
    lexer->last = new;
    if (!lexer->tokens)
    {
        lexer->tokens = new;
        return (1);
    }
    Token *head = lexer->tokens;
    while (head->next) head = head->next;
    head->next = new;
    return (1);
}

char *findWordInText(Token *it)
{
    (void) it;
    TODO("substr the it->indexFromContent to last WORD indexFromContent and remove everyone in between\n");
    return (strdup(""));
}


static char *typeToText(Type type, Token *t)
{
    switch (type)
    {
        case LPARENT:        return strdup("(");
        case RPARENT:        return strdup(")");
        case LBRACKET:       return strdup("[");
        case RBRACKET:       return strdup("]");
        case LCBRACKET:      return strdup("{");
        case RCBRACKET:      return strdup("}");
        case COMMA:          return strdup(",");
        case SEMICO:         return strdup(";");
        case GREATER_THAN:   return strdup(">");
        case LOWER_THAN:     return strdup("<");
        case EQUAL:          return strdup("=");
        case COLON:          return strdup(":");
        case SQUOTE:         return strdup("'");
        case QUOTE:          return strdup("\"");
        case STAR:           return strdup("*");
        case NLINE:          return strdup("\\n");
        case INDENT:         return strdup("\\t");
        case SPACE:          return strdup(" ");
        case RET:            return strdup("\\r");
        case QUESTIONMARK:   return strdup("?");
        case EXCLAMATIONMARK:return strdup("!");
        case DOT:            return strdup(".");
        case AND:            return strdup("&");
        case OR:             return strdup("|");
        case PLUS:           return strdup("+");
        case MINUS:          return strdup("-");
        case DASH:           return strdup("/");
        case PERCENT:        return strdup("%");
        case WORD:           return findWordInText(t);
        case UNDEFINED:      return strdup("<undefined>");
        default:             return strdup("<unknown>");
    }
}


/*
* We create all of the tokens and letting un-assigned char into undefined (not in gramar).
* Then we will clean the lexer and remove all undefined tokens.
*/
int initLexer(Lexer *lexer, File *files)
{
    *lexer = (Lexer){0};
    for (File *file = files; file; file = file->next)
    {
        size_t line = 1;
        size_t collumn = 1;
        size_t trueIndex = 0;
        for (size_t i = 0; i < file->size; i++)
        {
            char c = file->content[i];
            if (!addToken(lexer, line, collumn, getTypeFromChar(c)))
                return (0);
            // printf("'%c' -> '%s' -> %d\n", c, typeToText(getTypeFromChar(c)), (int)c);
            lexer->last->indexFromcontent = trueIndex;
            lexer->last->file = file;
            trueIndex++;
            if (c == '\n')
            {
                line++;
                collumn = 1;
            }
            else
                collumn++;
        }
    }
    return (1);
}

void removeToken(Lexer *lexer, size_t index)
{
    size_t i = 0;
    Token *head = lexer->tokens;
    while (head->next)
    {
        if (i+1 == index)
        {
            head->next = head->next->next;
            break;
        }
        i++;
        head= head->next;
    }
}

void freeLexer(Lexer *lexer)
{
    while (lexer->tokens)
    {
        Token *temp = lexer->tokens;
        lexer->tokens = lexer->tokens->next;
        free(temp->toString);
        free(temp);
    }
}

/*
* for every undefine, start a word. We naively assume that a stream of
* undefined is a word.
*/
int cleanLexer(Lexer *lexer)
{
    for (Token *it = lexer->tokens; it; it = it->next)
    {
        if (it->type == UNDEFINED)
        {
            it->type = WORD;
            it->toString = typeToText(WORD, it);
        }
        else
            it->toString = typeToText(it->type, it);
    }
    
    return (1);
}

void printLexer(Lexer *lexer)
{
    size_t i = 0;
    for (Token *it = lexer->tokens; it; it = it->next)
    {
        printf("Token %zu: Line %zu | Col %zu | Type '%s' | trueIndex %zu | file %s\n",
               i,
               it->startLine,
               it->startCollumn,
               it->toString,
               it->indexFromcontent,
               it->file->name);
               i++;
    }
}