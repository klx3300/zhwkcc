#ifndef ZHWKCC_IDTABLE_H
#define ZHWKCC_IDTABLE_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "../object/objformat.hpp"
#include "../object/instr.hpp"

struct IdTable {
    std::vector<std::unordered_map<std::string, uint16_t>> scope_variables;
    std::vector<uint16_t> scope_varid;
    uint16_t curr_scope;
    uint16_t curr_varid;
    std::vector<LiteralValue> literals;
    IdTable();
    void scope_push();
    void scope_pop();
    VariableReference define_variable(std::string ident, bool& succ);
    VariableReference get_variable(std::string ident, bool& succ);
    VariableReference define_literal(LiteralValue livalue, bool& succ);
};


#endif
