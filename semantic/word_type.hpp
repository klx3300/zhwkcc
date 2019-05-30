#ifndef ZHWKCC_SEMANTIC_WORDTYPE_H
#define ZHWKCC_SEMANTIC_WORDTYPE_H

#include <string>

struct WordType {
    std::string identifier;
    int literal_int;
    unsigned int literal_unsigned;
    double literal_float;
    std::string literal_string;
};

#endif
