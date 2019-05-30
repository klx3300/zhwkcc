#ifndef ZHWKCC_LEXICAL_CALLCONV_H
#define ZHWKCC_LEXICAL_CALLCONV_H

#include "mini_c.lex.hpp"

class LexerClass: public yyFlexLexer {

};

static inline int yylex() {
    return LexerClass::yylex();
}

#endif
