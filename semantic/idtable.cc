#include "idtable.hpp"
#include "../format/log.hpp"
#include <cstdlib>

using namespace std;

static inline uint16_t REAL_SCOPE(const IdTable* idt){
    return idt->curr_scope - 1;
}

static inline uint16_t REAL_SCOPE(uint16_t currsc){
    return currsc - 1;
}

#define VECLAST(vec) ((vec)[(vec).size()-1])

IdTable::IdTable() {
    curr_scope = 1;
    curr_varid = 0;
    scope_variables.push_back(unordered_map<string, VariableSignature>());
    scope_varid.push_back(0);
}

void IdTable::scope_push() {
    curr_scope++;
    if(curr_scope >= 65534) {
        qLogFail("Semantic Analyser: Too deep scope wraps.");
        abort();
    }
    curr_varid = 0;
    scope_variables.push_back(unordered_map<string, VariableSignature>());
    scope_varid.push_back(0);
}

void IdTable::scope_pop() {
    if(curr_scope == 1) {
        qLogFail("Semantic Analyser: Object Generator is trying to remove the global scope. Aborting...");
        abort();
    }
    curr_scope--;
    scope_variables.pop_back();
    scope_varid.pop_back();
    curr_varid = VECLAST(scope_varid);
}


VariableReference IdTable::define_variable(string ident, list<TypeSignature> type, bool& succ){
    auto& csvariables = VECLAST(scope_variables);
    if(csvariables.find(ident) != csvariables.end()) {
        qLogFailfmt("Semantic Analyser: Variable %s redefined in current scope.",
                ident.c_str());
        succ = false;
        return VariableReference();
    }
    succ = true;
    curr_varid ++;
    VECLAST(scope_varid) = curr_varid;
    VariableSignature vs;
    vs.varid = curr_varid - 1;
    vs.vartype = type;
    csvariables[ident] = vs;
    qLogDebugfmt("IDTable: defining %s%s as %hu:%hu", TypeSignaturePrinter(type).c_str(),
            ident.c_str(), curr_scope, vs.varid);
    return VariableOperand(curr_scope, curr_varid - 1).as_var;
}

VariableReference IdTable::get_variable(string ident, list<TypeSignature>* type, bool& succ){
    VariableReference vref;
    bool found = false;
    for(int i = REAL_SCOPE(this); i >= 0; i--){
        auto& vars = scope_variables[i];
        if(vars.find(ident) != vars.end()){
            found = true;
            VariableSignature vs = vars[ident];
            vref.varid = vs.varid;
            vref.scope = i + 1;
            if(type != NULL) *type = vs.vartype;
        }
    }
    if(!found){
        qLogFailfmt("Semantic Analyser: Variable %s undefined.",
                ident.c_str());
        succ = false;
    } else {
        succ = true;
    }
    return vref;
}

VariableReference IdTable::define_literal(LiteralValue lival, bool& succ){
    lival.varid = literals.size();
    if(lival.varid >= 65535){
        qLogFail("Semantic Analyser: Too many literals.");
        succ = false;
        return VariableReference();
    }
    literals.push_back(lival);
    succ = true;
    return VariableOperand(0, lival.varid).as_var;
}

TypeSignature NewTypeSignature(uint8_t btype){
    TypeSignature ts;
    ts.basetype = btype;
    ts.arraysize = 0;
    return ts;
}

TypeSignature NewTypeSignature(uint8_t btype, uint32_t arsize){
    TypeSignature ts;
    if(btype != VTYPE_ARRAY) {
        qLogFail("AssertionError: TypeSignature should be array type when calling array type ctor.");
        abort();
    }
    ts.basetype = btype;
    ts.arraysize = arsize;
    return ts;
}
