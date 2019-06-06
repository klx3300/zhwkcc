#ifndef ZHWKCC_IDTABLE_H
#define ZHWKCC_IDTABLE_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

#include "../object/objformat.hpp"
#include "../object/instr.hpp"

enum VariableTypeSignature {
    VTYPE_INTEGER = 0,
    VTYPE_FLOAT,
    VTYPE_STRING,
    VTYPE_ARRAY,
    VTYPE_POINTER
};

static inline bool SimpleVarType(uint8_t vtype) {
    if(vtype == VTYPE_ARRAY) return false;
    return true;
}

static inline bool NumericVarType(uint8_t vtype) {
    if(vtype == VTYPE_INTEGER) return true;
    if(vtype == VTYPE_FLOAT) return true;
    return false;
}


static const char* TypeSignatureStr[] = {
    "int",
    "float",
    "string",
    "array",
    "pointer"
};

struct TypeSignature {
    uint8_t basetype;
    uint32_t arraysize;
};

struct FunctionSignature {
    std::list<TypeSignature> return_type;
    std::vector<std::list<TypeSignature>> param_types;
    uint32_t namespc;
    uint32_t funcid;
};

static inline bool TypeSignatureCompare(const std::list<TypeSignature>& a, const std::list<TypeSignature>& b){
    if(a.size() != b.size()) return false;
    auto ai = a.begin(), bi = b.begin();
    while(ai != a.end()){
        if((*ai).basetype != (*bi).basetype) return false;
        if((*ai).arraysize != (*bi).arraysize) return false;
        ai++; bi++;
    }
    return true;
}

static inline bool FuncSignatureCompare(const FunctionSignature& a, const FunctionSignature& b){
    if(!TypeSignatureCompare(a.return_type, b.return_type)) return false;
    if(a.param_types.size() != b.param_types.size()) return false;
    auto ai = a.param_types.begin(), bi = b.param_types.begin();
    while(ai != a.param_types.end()){
        if(!TypeSignatureCompare((*ai), (*bi))) return false;
        ai++; bi++;
    }
    return true;
}

TypeSignature NewTypeSignature(uint8_t btype);
TypeSignature NewTypeSignature(uint8_t btype, uint32_t arsize);

struct VariableSignature {
    std::list<TypeSignature> vartype;
    uint16_t varid;
};


struct IdTable {
    std::vector<std::unordered_map<std::string, VariableSignature>> scope_variables;
    std::vector<uint16_t> scope_varid;
    uint16_t curr_scope;
    uint16_t curr_varid;
    std::vector<LiteralValue> literals;
    std::unordered_map<std::string, FunctionSignature> func_ids;
    uint32_t curr_funcid;
    std::list<TypeSignature> curr_vartype;
    std::vector<std::list<TypeSignature>> curr_funcall_argtypes;
    IdTable();
    void scope_push();
    void scope_pop();
    VariableReference define_variable(std::string ident, std::list<TypeSignature> ts, bool& succ);
    VariableReference get_variable(std::string ident, std::list<TypeSignature>* vtp, bool& succ);
    VariableReference define_literal(LiteralValue livalue, bool& succ);
};

static inline bool TypeCheck(
        const std::list<TypeSignature>& vt_a, uint8_t exvt_a,
        const std::list<TypeSignature>& vt_b, uint8_t exvt_b){
    if(vt_a.begin()->basetype != exvt_a) return false;
    if(vt_b.begin()->basetype != exvt_b) return false;
    return true;
}

static inline bool TypeCheck(const std::list<TypeSignature>& vt_a,
        const std::list<TypeSignature>& vt_ex) {
    if(vt_a.begin()->basetype == vt_ex.begin()->basetype) return true;
    return false;
}


#endif
