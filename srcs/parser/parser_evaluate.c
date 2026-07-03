#include "compiler.h"

// bool    evaluate_parsing(Parser *parser)
// {
//     size_t i = parser->current;
//     while (i < parser->count)
//     {
//         if (parser->tokens[i].type == TOKEN_FUNC && !(eval_func(parser)))
//             return (false);
//         else if (parser->tokens[i].type == TOKEN_CLASS && !(eval_class(parser)))
//             return (false);
//         else if (parser->tokens[i].type == TOKEN_IF && !(eval_if(parser)))
//             return (false);
//         else if (parser->tokens[i].type == TOKEN_WHILE && !(eval_while(parser)))
//             return (false);
//         else if (parser->tokens[i].type == TOKEN_PRIVATE && !(eval_class_mem(parser)))
//             return (false);
//         else if (parser->tokens[i].type == TOKEN_PUBLIC && !(eval_class_mem(parser)))
//             return (false);
//         else
//             i++;
//     }
//     return (true);
// }