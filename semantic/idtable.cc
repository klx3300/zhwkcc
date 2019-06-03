#include "idtable.hpp"
#include "../format/log.hpp"

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
    scope_variables.push_back(unordered_map<string, uint16_t>());
    scope_varid.push_back(0);
}

void IdTable::scope_push() {
    curr_scope++;
    curr_varid = 0;
    scope_variables.push_back(unordered_map<string, uint16_t>());
    scope_varid.push_back(0);
}

void IdTable::scope_pop() {
    curr_scope--;
    scope_variables.pop_back();
    scope_varid.pop_back();
    curr_varid = VECLAST(scope_varid);
}

VariableReference IdTable::define_variable(string ident, bool& succ){
    auto& csvariables = VECLAST(scope_variables);
    if(csvariables.find(ident) != csvariables.end()) {
        qLogFailfmt("Semantic Analyser: Variable %s redefined in current scope.\n",
                ident.c_str());
        succ = false;
        return VariableReference();
    }
    succ = true;
    curr_varid ++;
    VECLAST(scope_varid) = curr_varid;
    csvariables[ident] = curr_varid - 1;
    return VariableOperand(VREF_CURRSCOPE, curr_varid - 1).as_var;
}

VariableReference IdTable::get_variable(string ident, bool& succ){
    VariableReference vref;
    bool found = false;
    for(int i = REAL_SCOPE(this); i >= 0; i--){
        auto& vars = scope_variables[i];
        if(vars.find(ident) != vars.end()){
            found = true;
            vref.varid = vars[ident];
            vref.scope = i + 1;
        }
    }
    if(!found){
        qLogFailfmt("Semantic Analyser: Variable %s undefined.\n",
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
        qLogFail("Semantic Analyser: Too many literals.\n");
        succ = false;
        return VariableReference();
    }
    literals.push_back(lival);
    succ = true;
    return VariableOperand(0, lival.varid).as_var;
}

