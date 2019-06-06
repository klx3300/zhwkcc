#ifndef ZHWKCC_UTILITY_H
#define ZHWKCC_UTILITY_H

#include <string>
#include <cstdio>

int string_to_integer(std::string str);
double string_to_double(std::string str);

std::string uint_to_string(uint32_t u);

std::string trim_string_quotes(std::string str);

int extract_from_char_string(std::string charstr);


#endif
