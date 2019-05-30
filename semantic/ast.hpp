#ifndef ZHWKCC_AST_H
#define ZHWKCC_AST_H

#include "word_type.hpp"

enum ASTNodeType {
    TYPE_INVAL = 0,
    TYPE_MASTER_LIST,
    TYPE_GLOBAL_VAR,
    TYPE_FUNC_DECL,
    TYPE_FUNC_DEF,
    TYPE_TYPESPEC,
    TYPE_VAR_DECLIST,
    TYPE_VARNAME,
    TYPE_COMPLEX,
    TYPE_FUNC_PROTO,
    TYPE_PARAM_LIST,
    TYPE_PARAM,
    TYPE_STMTBLK,
    TYPE_STMTLIST,
    TYPE_EXPR,
    TYPE_RETURN,
    TYPE_IFTRUE,
    TYPE_IF,
    TYPE_WHILE,
    TYPE_VARDEF,
    TYPE_INITIALIZER,
    TYPE_OPERATOR,
    TYPE_CALL,
    TYPE_IDENTIFIER,
    TYPE_LITERAL_INTEGER,
    TYPE_LITERAL_FLOAT,
    TYPE_LITERAL_STRING,
    TYPE_ARGLIST,
    TYPE_ACCESS,
    TYPE_COUNT // this is the guard, add types before this!
};

extern const char* ASTNodeTypeStr[];

struct ASTNode {
    ASTNodeType type;
    WordType data;
    ASTNode* childs[3];
    int lineno;
    ASTNode();
    ASTNode(ASTNodeType typ,
            ASTNode* chld0, ASTNode* chld1, ASTNode* chld2,
            int lnumber);
    void recursive_print(int level);
};

#endif
