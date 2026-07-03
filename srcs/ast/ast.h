#ifndef AST_H
# define AST_H


typedef struct {
    TokenArray arr;
} ASTparams;

typedef enum {
    ASTFUNC,
    ASTCLASS,
    ASTIF,
    ASTWHILE,
    ASTELSE,
    ASTPRIVATE,
    ASTPUBLIC,
} ASTtype;

typedef struct {
    TokenArray arr;
} ASTbody;

typedef struct {
    TokenArray arr;
}       ASTstatement;


typedef struct AST_s{
    ASTparams p;
    ASTtype t;
    ASTbody b;
    ASTstatement s;
}       AST;

#endif 