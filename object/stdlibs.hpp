#ifndef ZHWKCC_STDLIBS_H
#define ZHWKCC_STDLIBS_H

#include "../semantic/idtable.hpp"
#include <string>
#include <unordered_map>

struct StdLibrary {
    std::unordered_map<std::string, FunctionSignature> libfuncs;
    StdLibrary();
    FunctionSignature getfunc(std::string libname, std::string funcname, bool& succ);
};

#endif
