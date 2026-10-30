#include "sdmllang.h"


/* Here we rearange tokens to match paterns
* (ie: '-' + '>' = '->' so we regroup the two to make an arrow)
* we then examin if the streams of those tokens are legal in the language
*/
int processTokens(Lexer *lexer)
{
    printLexer(lexer);
    return (1);
}

int parseInput(Lexer *lexer, File *files)
{

    if (!initLexer(lexer, files))
        return (0);
    if (!lexer->tokens)
        return (printFile(*files), freeLexer(lexer), TODO("no tokens found in input files\n"));
    if (!cleanLexer(lexer))
        return (freeLexer(lexer), TODO("lexer cleaning failed\n"));
    for (Token *it = lexer->tokens; it; it = it->next)
    {
        if (it->type == UNDEFINED) return (freeLexer(&lexer), TODO("wtf"));
    }
    if (!processTokens(lexer))
        return (freeLexer(&lexer), TODO("token processing failed\n"));
    freeLexer(&lexer);
    return (1);
}
