#include "sdmllang.h"

int processTokens(Lexer *lexer, Parser *parser)
{
    (void)lexer;
    (void)parser;
    printLexer(lexer);
    return (1);
}

int freeParser(Parser parser)
{
    (void)parser;
    return (1);
}

int parseInput(Parser *parser, File *files)
{
    Lexer lexer;

    if (!initLexer(&lexer, files))
        return (0);
    if (!lexer.tokens)
        return (printFile(*files), freeLexer(&lexer), TODO("no tokens found in input files\n"));
    if (!cleanLexer(&lexer))
        return (freeLexer(&lexer), TODO("lexer cleaning failed\n"));
    for (Token *it = lexer.tokens; it; it = it->next)
    {
        if (it->type == UNDEFINED) return (freeLexer(&lexer), TODO("wtf"));
    }
    
    if (!processTokens(&lexer, parser))
        return (freeLexer(&lexer), TODO("token processing failed\n"));
    freeLexer(&lexer);
    return (1);
}
