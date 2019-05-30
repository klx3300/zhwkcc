#ifndef ZHWKCC_VALTYPE_H
#define ZHWKCC_VALTYPE_H

#include "ast.hpp"
#include <string>

struct ValueType {
    std::string identifier;
    int literal_int;
    unsigned int literal_unsigned;
    double literal_float;
    std::string literal_string;
    ASTNode* astnode;
};

#endif
