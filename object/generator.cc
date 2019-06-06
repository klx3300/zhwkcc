#include "generator.hpp"
#include "../format/log.hpp"
#include "../utility/utility.hpp"

using namespace std;

static inline uint8_t VType2IType(uint8_t vtype) {
    if(vtype == VTYPE_INTEGER) return ITYPE_INTEGER;
    if(vtype == VTYPE_FLOAT) return ITYPE_FLOAT;
    if(vtype == VTYPE_STRING) return ITYPE_STRING;
    if(vtype == VTYPE_POINTER) return ITYPE_POINTER;
    qLogFailfmt("Generator: No matching itype for vtype %d\n", vtype);
    abort();
    return -1;
}

void NodeOpInvalid(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Reached invalid AST Node.\n");
}

void NodeOpMasterList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: MasterList(%d)\n", node->lineno);
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    NodeOperator(node->childs[1], G, nullptr, nullptr);
}

void NodeOpGlobalVariable(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Define Global Variable(%d)\n", node->lineno);
    G.idtable.curr_vartype.clear();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.idtable.curr_vartype.clear();
}

FunctionSignature ReadFuncSignature(ASTNode* node, Generator& G) {
    FunctionSignature fsign;
    if((node->type != TYPE_FUNC_DECL) || (node->type != TYPE_FUNC_DEF)) {
        qLogFail("Generator: reading function signature from non-function nodes.\n");
        abort();
    }
    G.idtable.curr_vartype.clear();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    fsign.return_type = G.idtable.curr_vartype;
    G.idtable.curr_vartype.clear();
    node = node->childs[1];
    if(node->childs[0] == nullptr) {
        fsign.return_type.clear();
        return fsign;
    }
    node = node->childs[0];
    while(node != nullptr){
        G.idtable.curr_vartype.clear();
        NodeOperator(node->childs[0]->childs[0], G, nullptr, nullptr);
        fsign.param_types.push_back(G.idtable.curr_vartype);
        G.idtable.curr_vartype.clear();
        node = node->childs[1];
    }
    return fsign;
}

void NodeOpFuncDeclaration(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    auto deftry = G.idtable.func_ids.find(node->childs[1]->data.identifier);
    if(deftry != G.idtable.func_ids.end()){
        qLogWarnfmt("Semantic Analysis: Multiple declarations for function %s.\n",
                node->childs[1]->data.identifier.c_str());
        return;
    }
    qLogDebugfmt("Generator: Function decl: %s\n", node->childs[1]->data.identifier.c_str());
    auto fsign = ReadFuncSignature(node, G);
    fsign.namespc = 1;
    fsign.funcid = G.idtable.curr_funcid;
    G.idtable.curr_funcid++;
    G.idtable.func_ids[node->childs[1]->data.identifier] = fsign;
}

void NodeOpFuncDefinition(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Function definition: %s\n", node->childs[1]->data.identifier.c_str());
    auto fsign = ReadFuncSignature(node, G);
    auto deftry = G.idtable.func_ids.find(node->childs[1]->data.identifier);
    if(deftry != G.idtable.func_ids.end()){
        if(!FuncSignatureCompare((*deftry).second, fsign)){
            qLogFailfmt("Semantic Analysis: Prototype mismatch for function %s.\n",
                    node->childs[1]->data.identifier.c_str());
            abort();
        }
    }
    fsign.namespc = 1;
    fsign.funcid = G.idtable.curr_funcid;
    G.idtable.curr_funcid++;
    G.idtable.func_ids[node->childs[1]->data.identifier] = fsign;
    G.codes.push_back(InstructionFormat(OP_FUNC, 
                ImmediateOperand(fsign.namespc),
                ImmediateOperand(fsign.funcid),
                Operand()));
    G.idtable.scope_push();
    // Creating parameter takeplace in this scope
    qLogDebug("Generator: Creating parameter takeplace..\n");
    auto pnameit = node->childs[1]->childs[0];
    for(auto &ptype: fsign.param_types) {
        bool succ = true;
        G.idtable.define_variable(
                pnameit->childs[0]->childs[1]->data.identifier,
                ptype, succ);
        if(!succ) {
            qLogFailfmt("Generator: failed to set takeplace for parameter %s\n", 
                pnameit->childs[0]->childs[1]->data.identifier.c_str());
            abort();
        }
        qLogDebugfmt("Generator: parameter %s\n", 
            pnameit->childs[0]->childs[1]->data.identifier.c_str());
        pnameit = pnameit->childs[1];
    }
    NodeOperator(node->childs[2], G, nullptr, nullptr);
}

void NodeOpTypeSpecification(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Simple type specification: %s\n", node->data.identifier.c_str());
    if((node->data.identifier == "int") || (node->data.identifier == "char")){
        G.idtable.curr_vartype.push_back(NewTypeSignature(VTYPE_INTEGER));
    } else if(node->data.identifier == "float") {
        G.idtable.curr_vartype.push_back(NewTypeSignature(VTYPE_FLOAT));
    } else if(node->data.identifier == "string") {
        G.idtable.curr_vartype.push_back(NewTypeSignature(VTYPE_STRING));
    } else {
        qLogDebug("Generator: Unknown type. Aborting...");
        abort();
    }
}

void NodeOpVariableDeclaration(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebug("Generator: Variable declaration list\n");
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    if(node->childs[1] != nullptr) NodeOperator(node->childs[1], G, nullptr, nullptr);
}

static VariableReference ComplexTypeDefGen(list<TypeSignature> comp_type, Generator& G, string prefix, string itsname){
    auto curriter = comp_type.begin();
    uint8_t currtype = (*(comp_type.begin())).basetype;
    bool vardef_succ = true;
    list<TypeSignature> temp_deftype;
    qLogDebugfmt("Generator: Complex type recursion reach <%s>.\n", TypeSignatureStr[currtype]);
    if(currtype == VTYPE_INTEGER) {
        temp_deftype.push_back(NewTypeSignature(VTYPE_INTEGER));
        auto vr = G.idtable.define_variable(prefix + ":" + "int" + "@" + itsname + uint_to_string(G.temporals_id), 
                temp_deftype, vardef_succ);
        G.temporals_id++;
        if(!vardef_succ) {
            qLogFailfmt("Generator: When generating complex type for %s.\n",
                    (prefix+itsname).c_str());
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_VARDEF,
                    ImmediateOperand(0),
                    ImmediateOperand(ITYPE_INTEGER), 
                    VariableOperand(vr)));
        qLogDebugfmt("Generator: Variable reference No.%d\n", vr.varid);
        return vr;
    } else if (currtype == VTYPE_FLOAT) {
        temp_deftype.push_back(NewTypeSignature(VTYPE_FLOAT));
        auto vr = G.idtable.define_variable(prefix + ":" + "float" + "@" + itsname + uint_to_string(G.temporals_id), 
                temp_deftype, vardef_succ);
        G.temporals_id++;
        if(!vardef_succ) {
            qLogFailfmt("Generator: When generating complex type for %s.\n",
                    (prefix+itsname).c_str());
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_VARDEF,
                    ImmediateOperand(0),
                    ImmediateOperand(ITYPE_FLOAT),
                    VariableOperand(vr)));
        qLogDebugfmt("Generator: Variable reference No.%d\n", vr.varid);
        return vr;
    } else if (currtype == VTYPE_STRING) {
        temp_deftype.push_back(NewTypeSignature(VTYPE_STRING));
        auto vr = G.idtable.define_variable(prefix + ":" + "str" + "@" + itsname + uint_to_string(G.temporals_id), 
                temp_deftype, vardef_succ);
        G.temporals_id++;
        if(!vardef_succ) {
            qLogFailfmt("Generator: When generating complex type for %s.\n",
                    (prefix+itsname).c_str());
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_VARDEF,
                    ImmediateOperand(0),
                    ImmediateOperand(ITYPE_STRING),
                    VariableOperand(vr)));
        qLogDebugfmt("Generator: Variable reference No.%d\n", vr.varid);
        return vr;
    } else if (currtype == VTYPE_POINTER) {
        // pointer is also terminating.
        temp_deftype.push_back(NewTypeSignature(VTYPE_POINTER));
        auto vr = G.idtable.define_variable(prefix + ":" + "ptr" + "@" + itsname + uint_to_string(G.temporals_id), 
                temp_deftype, vardef_succ);
        G.temporals_id++;
        if(!vardef_succ) {
            qLogFailfmt("Generator: When generating complex type for %s.\n",
                    (prefix+itsname).c_str());
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_VARDEF,
                    ImmediateOperand(0),
                    ImmediateOperand(ITYPE_POINTER),
                    VariableOperand(vr)));
        qLogDebugfmt("Generator: Variable reference No.%d\n", vr.varid);
        return vr;
    } else if (currtype == VTYPE_ARRAY) {
        // firstly, we has to check whether the next type is basic type
        auto nextiter = comp_type.begin();
        nextiter++;
        auto nexttype = ((*nextiter).basetype);
        if(SimpleVarType(nexttype)){
            temp_deftype.push_back(NewTypeSignature(nexttype, (*curriter).arraysize));
            auto vr = G.idtable.define_variable(prefix + ":" + "arr<" + TypeSignatureStr[nexttype] + 
                    ">@" + itsname + uint_to_string(G.temporals_id),
                    temp_deftype, vardef_succ);
            G.temporals_id++;
            if(!vardef_succ) {
                qLogFailfmt("Generator: When generating complex type for %s.\n",
                        (prefix+itsname).c_str());
                abort();
            }
            G.codes.push_back(InstructionFormat(OP_VARDEF, ImmediateOperand((*curriter).arraysize),
                        ImmediateOperand(VType2IType(nexttype)), VariableOperand(vr)));
            qLogDebugfmt("Generator: Variable reference No.%d\n", vr.varid);
            return vr;
        } else {
            auto arrsize = ((*nextiter).arraysize);
            VariableReference nlvrs[arrsize];
            auto nltype = comp_type;
            nltype.pop_front();
            for(unsigned int i = 0; i < arrsize; i++){
                auto nlvr = ComplexTypeDefGen(nltype, G, prefix + ":arr", itsname);
                nlvrs[i] = nlvr;
            }
            auto vr = G.idtable.define_variable(prefix + ":" + "arr<" + TypeSignatureStr[nexttype] + 
                    ">@" + itsname + uint_to_string(G.temporals_id),
                    comp_type, vardef_succ);
            G.temporals_id++;
            if(!vardef_succ) {
                qLogFailfmt("Generator: When generating complex type for %s.\n",
                        (prefix+itsname).c_str());
                abort();
            }
            qLogDebugfmt("Generator: Variable reference No.%d\n", vr.varid);
            G.codes.push_back(InstructionFormat(OP_VARDEF, ImmediateOperand(arrsize), 
                        ImmediateOperand(ITYPE_POINTER), VariableOperand(vr)));
            // initialization codes
            for(unsigned int i = 0; i < arrsize; i++){
                G.codes.push_back(InstructionFormat(OP_STORE, VariableOperand(nlvrs[i]),
                            Operand(), VariableOperand(vr)));
                G.codes.push_back(InstructionFormat(OP_ADD, VariableOperand(vr),
                            VariableOperand(G.int_one), VariableOperand(vr)));
            }
            G.codes.push_back(InstructionFormat(OP_ARRRESET, VariableOperand(vr),
                        Operand(), Operand()));
            // completed.
            return vr;
        }
    } else {
        qLogFail("Generator: Unrecognized type in curr_type.\n");
        abort();
    }
}

void NodeOpVariableName(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Define variable %s\n", node->data.identifier.c_str());
    // Check variable type
    if(G.idtable.curr_vartype.size() == 0) {
        qLogFail("Generator: variable definition with invalid(empty) current type.\n");
        abort();
    }
    if(G.idtable.curr_vartype.size() == 1) {
        // this is the simple types.
        // we can directly generate it.
        uint8_t currtype = (*G.idtable.curr_vartype.begin()).basetype;
        qLogDebugfmt("Generator: as type [%s]\n", TypeSignatureStr[currtype]);
        // Register it
        bool vardef_succ = true;
        auto vr = G.idtable.define_variable(node->data.identifier, G.idtable.curr_vartype, vardef_succ);
        if(!vardef_succ){
            qLogFailfmt("Semantic Analysis: at (%d). Aborting...\n", node->lineno);
            abort();
        }
        if(currtype == VTYPE_INTEGER) {
            G.codes.push_back(InstructionFormat(OP_VARDEF,
                        ImmediateOperand(0),
                        ImmediateOperand(ITYPE_INTEGER),
                        VariableOperand(vr)));
        } else if (currtype == VTYPE_FLOAT) {
            G.codes.push_back(InstructionFormat(OP_VARDEF,
                        ImmediateOperand(0),
                        ImmediateOperand(ITYPE_FLOAT),
                        VariableOperand(vr)));
        } else if (currtype == VTYPE_STRING) {
            G.codes.push_back(InstructionFormat(OP_VARDEF,
                        ImmediateOperand(0),
                        ImmediateOperand(ITYPE_STRING),
                        VariableOperand(vr)));
        } else {
            qLogFailfmt("Generator: invalid simple type code %d?? Aborting...\n", currtype);
            abort();
        }
        if(tmpvar_refr != nullptr) *tmpvar_refr = vr;
    } else {
        // for complex types, we use some 'complex type definition generator'.
        // that's because for supporting N-dimension arrays, we generate many temporal variables.
        // every temporal variables will be registered into the global registry, so avoid creating these arrays.
        // you'd better try flatten them.
        auto vr = ComplexTypeDefGen(G.idtable.curr_vartype, G, "", node->data.identifier);
        if(tmpvar_refr != nullptr) *tmpvar_refr = vr;
    }
    if(result_type != nullptr) *result_type = G.idtable.curr_vartype;
}

void NodeOpComplexType(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    TypeSignature tsign;
    if(node->data.identifier == "array") {
        tsign.basetype = VTYPE_ARRAY;
        tsign.arraysize = node->data.literal_int;
        G.idtable.curr_vartype.push_back(tsign);
        NodeOperator(node->childs[0], G, nullptr, nullptr);
    } else if(node->data.identifier == "pointer") {
        tsign.basetype = VTYPE_POINTER;
        tsign.arraysize = 0;
        G.idtable.curr_vartype.push_back(tsign);
    } else {
        qLogFailfmt("Generator: unknown complex type identifier %s\n",
                node->data.identifier.c_str());
        abort();
    }
}

void NodeOpFuncPrototype(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Operation on non-operative node FuncPrototype.\n");
    abort();
}

void NodeOpParameterList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Operation on non-operative node ParameterList.\n");
    abort();
}

void NodeOpParameter(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Operation on non-operative node Parameter.\n");
    abort();
}

void NodeOpStatementBlock(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebug("Generator: Statement block stated.\n");
    G.idtable.scope_push();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    G.idtable.scope_pop();
    qLogDebug("Generator: Statement block ended.\n");
}

void NodeOpStatementList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(node->childs[0] != nullptr){
        NodeOperator(node->childs[0], G, nullptr, nullptr);
        if(node->childs[1] != nullptr) {
            NodeOperator(node->childs[1], G, nullptr, nullptr);
        }
    }
}

void NodeOpExpression(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(node->childs[0] == nullptr) {
        qLogWarnfmt("Semantic Analysis: Empty expression at %d\n", node->lineno);
        return;
    }
    NodeOperator(node->childs[0], G, tmpvar_refr, result_type);
}

void NodeOpReturn(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: generating return at %d\n", node->lineno);
    VariableReference x;
    NodeOperator(node->childs[0], G, &x, nullptr);
    G.codes.push_back(InstructionFormat(OP_RET,
                VariableOperand(x),
                Operand(), Operand()));
}

void NodeOpCondIfTrue(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: iftrue at %d\n", node->lineno);
    VariableReference condreslt;
    list<TypeSignature> condtype;
    NodeOperator(node->childs[0], G, &condreslt, &condtype);
    if(condtype.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: Using non-boolean values for if statement %d.\n",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_IF, 
                VariableOperand(condreslt),
                Operand(), Operand()));
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.codes.push_back(InstructionFormat(OP_ELSE,
                Operand(), Operand(), Operand()));
    G.codes.push_back(InstructionFormat(OP_IFEND,
                Operand(), Operand(), Operand()));
}

void NodeOpCondIf(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: if at %d\n", node->lineno);
    VariableReference condreslt;
    list<TypeSignature> condtype;
    NodeOperator(node->childs[0], G, &condreslt, &condtype);
    if(condtype.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: Using non-boolean values for if statement %d.\n",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_IF, 
                VariableOperand(condreslt),
                Operand(), Operand()));
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.codes.push_back(InstructionFormat(OP_ELSE,
                Operand(), Operand(), Operand()));
    NodeOperator(node->childs[2], G, nullptr, nullptr);
    G.codes.push_back(InstructionFormat(OP_IFEND,
                Operand(), Operand(), Operand()));

}

void NodeOpLoopWhile(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: while-loop at %d\n", node->lineno);
    G.codes.push_back(InstructionFormat(OP_LOOPCOND, 
                Operand(), Operand(), Operand()));
    VariableReference condreslt;
    list<TypeSignature> condtype;
    NodeOperator(node->childs[0], G, &condreslt, &condtype);
    if(condtype.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: Using non-boolean values for loop condition %d.\n",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_LOOP,
                VariableOperand(condreslt), Operand(), Operand()));
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.codes.push_back(InstructionFormat(OP_LOOPEND,
                Operand(), Operand(), Operand()));
}

void NodeOpVariableDefinition(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Define Local Variable(%d)\n", node->lineno);
    G.idtable.curr_vartype.clear();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.idtable.curr_vartype.clear();
}

void NodeOpInitializer(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    // chld[0] = variable_name
    // chld[1] = eval_expr
    VariableReference vref;
    list<TypeSignature> vtsign;
    NodeOperator(node->childs[0], G, &vref, &vtsign);
    VariableReference tmpref;
    list<TypeSignature> tmptsign;
    NodeOperator(node->childs[1], G, &tmpref, &tmptsign);
    if(!TypeSignatureCompare(vtsign, tmptsign)){
        qLogFailfmt("Semantic Analysis: Type mismatch in line %d\n",
                node->lineno);
        abort();
    }
    // we doesn't support array initializer, so
    auto currts = (*(G.idtable.curr_vartype.begin())).basetype;
    if((currts == VTYPE_INTEGER) || (currts == VTYPE_FLOAT)
            || (currts == VTYPE_POINTER)) {
        G.codes.push_back(InstructionFormat(OP_ADD,
                    VariableOperand(tmpref),
                    VariableOperand(G.int_zero),
                    VariableOperand(vref)));
        qLogDebug("Generator: Initialized\n");
    } else if(currts == VTYPE_STRING) {
        G.codes.push_back(InstructionFormat(OP_ADD,
                    VariableOperand(tmpref),
                    VariableOperand(G.string_zero),
                    VariableOperand(vref)));
        qLogDebug("Generator: Initialized\n");
    } else {
        qLogFailfmt("Semantic Analysis: Initializer on unsupported type at line %d.\n",
                node->lineno);
        abort();
    }
    if(tmpvar_refr != nullptr) *tmpvar_refr = vref;
    if(result_type != nullptr) *result_type = vtsign;
}

void NodeOpOperator(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(node->data.identifier == "assign") {
        // the left side has to be: identifier, dereference or access
        if(node->childs[0]->type == TYPE_IDENTIFIER) {
            qLogDebugfmt("Generator: assign to identifier %d\n",
                    node->lineno);
            // for identifiers, we extract it out from identifier list
            list<TypeSignature> asts;
            bool succ = true;
            VariableReference asvr = G.idtable.get_variable(node->childs[0]->data.identifier, &asts, succ);
            if(!succ) {
                qLogFailfmt("Semantic Analysis: Undefined identifier: %s, %d\n",
                        node->childs[0]->data.identifier.c_str(),
                        node->childs[0]->lineno);
                abort();
            }
            list<TypeSignature> valts;
            VariableReference valvr;
            NodeOperator(node->childs[1], G, &valvr, &valts);
            if(!TypeSignatureCompare(asts, valts)){
                if(!TypeCheck(asts, VTYPE_POINTER, valts, VTYPE_ARRAY)){
                    qLogFailfmt("Semantic Analysis: Type mismatch for assignment. %d\n",
                            node->lineno);
                    abort();
                } else {
                    qLogDebugfmt("Semantic Analysis: Using array name as pointer here.. %d\n",
                            node->lineno);
                }
            }
            auto currts = asts.begin()->basetype;
            if((currts == VTYPE_INTEGER) || (currts == VTYPE_FLOAT)
                    || (currts == VTYPE_POINTER)) {
                G.codes.push_back(InstructionFormat(OP_ADD,
                            VariableOperand(valvr),
                            VariableOperand(G.int_zero),
                            VariableOperand(asvr)));
            } else if(currts == VTYPE_STRING) {
                G.codes.push_back(InstructionFormat(OP_ADD,
                            VariableOperand(valvr),
                            VariableOperand(G.string_zero),
                            VariableOperand(asvr)));
            } else {
                qLogFailfmt("Semantic Analysis: You cant direct assign complex types. %d\n",
                        node->lineno);
                abort();
            }
            if(tmpvar_refr != nullptr) *tmpvar_refr = valvr;
            if(result_type != nullptr) *result_type = valts;
        } else if ((node->childs[0]->type == TYPE_OPERATOR) || 
                node->childs[0]->data.identifier == "dereference"){
            qLogDebugfmt("Generator: assign to dereference accesses %d\n",
                        node->lineno);
            list<TypeSignature> ptrts;
            VariableReference ptrvr;
            NodeOperator(node->childs[0]->childs[0], G, &ptrvr, &ptrts);
            list<TypeSignature> realts = ptrts;
            realts.pop_front(); // remove the 'pointer' directive
            list<TypeSignature> valts;
            VariableReference valvr;
            NodeOperator(node->childs[1], G, &valvr, &valts);
            if(!TypeSignatureCompare(realts, valts)){
                if(!TypeCheck(realts, VTYPE_POINTER, valts, VTYPE_ARRAY)){
                    qLogFailfmt("Semantic Analysis: Type mismatch for *deref* assignment. %d\n",
                            node->lineno);
                    abort();
                } else {
                    qLogDebugfmt("Semantic Analysis: Using array name as pointer here.. %d\n",
                            node->lineno);
                }
            }
            G.codes.push_back(InstructionFormat(OP_STORE,
                        VariableOperand(valvr),
                        Operand(),
                        VariableOperand(ptrvr)));
            if(tmpvar_refr != nullptr) *tmpvar_refr = valvr;
            if(result_type != nullptr) *result_type = valts;
        } else if(node->childs[0]->type == TYPE_ACCESS) {
            qLogDebugfmt("Generator: assign to array access %d\n",
                    node->lineno);
            list<TypeSignature> arrts, idxts;
            VariableReference arrvr, idxvr;
            NodeOperator(node->childs[0]->childs[0], G, &arrvr, &arrts);
            NodeOperator(node->childs[0]->childs[1], G, &idxvr, &idxts);
            // type checks
            if(idxts.begin()->basetype != VTYPE_INTEGER){
                qLogFail("Semantic Analysis: using non-integer as array access operand.\n");
                abort();
            }
            list<TypeSignature> realts = arrts;
            realts.pop_front();
            list<TypeSignature> valts;
            VariableReference valvr;
            NodeOperator(node->childs[1], G, &valvr, &valts);
            if(!TypeSignatureCompare(realts, valts)) {
                if(!TypeCheck(realts, VTYPE_POINTER, valts, VTYPE_ARRAY)){
                    qLogFailfmt("Semantic Analysis: Type mismatch for *access* assignment. %d\n",
                            node->lineno);
                    abort();
                } else {
                    qLogDebugfmt("Semantic Analysis: Using array name as pointer here.. %d\n",
                            node->lineno);
                }
            }
            // All checks completed.
            // Generate a temporal variable for that
            list<TypeSignature> temporal_ts = arrts;
            bool temporal_succ = true;
            auto temporal_vr = G.idtable.define_variable(
                    "access_temporal_" + uint_to_string(G.idtable.curr_varid),
                    temporal_ts, temporal_succ);
            if(!temporal_succ){
                qLogFailfmt("Generator: while registering temporal for array access assignment %d\n",
                        node->lineno);
                abort();
            }
            G.codes.push_back(InstructionFormat(OP_VARDEF,
                        ImmediateOperand(0),
                        ImmediateOperand(ITYPE_POINTER),
                        VariableOperand(temporal_vr)));
            G.codes.push_back(InstructionFormat(OP_ADD,
                        VariableOperand(arrvr),
                        VariableOperand(idxvr),
                        VariableOperand(temporal_vr)));
            G.codes.push_back(InstructionFormat(OP_STORE,
                        VariableOperand(valvr),
                        Operand(),
                        VariableOperand(temporal_vr)));
            if(tmpvar_refr != nullptr) *tmpvar_refr = valvr;
            if(result_type != nullptr) *result_type = valts;
        } else {
            qLogFailfmt("Semantic Analysis: Using right values as assignment target %d.\n",
                    node->lineno);
            abort();
        }
    } else if(node->data.identifier == "and") {
        qLogDebugfmt("Generator: Operator and %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: logical operator between non-integer variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_and_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for and operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_AND,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "or") {
        qLogDebugfmt("Generator: Operator or %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: logical operator between non-integer variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_or_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for or operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_OR,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "<") {
        qLogDebugfmt("Generator: Operator lesser %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_lesser_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for lesser operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_LES,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "<=") {
        qLogDebugfmt("Generator: Operator leq %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_leq_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for leq operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_LEQ,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == ">") {
        qLogDebugfmt("Generator: Operator gre %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_gre_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for gre operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_GRE,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == ">=") {
        qLogDebugfmt("Generator: Operator geq %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_geq_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for geq operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_GEQ,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "==") {
        qLogDebugfmt("Generator: Operator equ %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype  != opBts.begin()->basetype)){
            qLogFailfmt("Generator: EQUAL operator between different type variable %d\n",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_equ_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for equ operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_EQU,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "plus") {
        qLogDebugfmt("Generator: Operator add %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if((!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype)))
                && (!TypeCheck(opAts, VTYPE_STRING, opBts, VTYPE_STRING))
                && (!TypeCheck(opAts, VTYPE_POINTER, opBts, VTYPE_INTEGER))
                && (!TypeCheck(opAts, VTYPE_ARRAY, opBts, VTYPE_INTEGER))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op + %d\n",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_add_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for add operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_ADD,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "minus") {
        qLogDebugfmt("Generator: Operator minus %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if((!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype)))
                && (!TypeCheck(opAts, VTYPE_POINTER, opBts, VTYPE_INTEGER))
                && (!TypeCheck(opAts, VTYPE_ARRAY, opBts, VTYPE_INTEGER))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op - %d\n",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_minus_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for minus operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_SUB,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "multiply") {
        qLogDebugfmt("Generator: Operator multiply %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if(!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op * %d\n",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_mul_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for multiply operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_MUL,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "divide") {
        qLogDebugfmt("Generator: Operator divide %d\n", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if(!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op / %d\n",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_div_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for divide operator %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_DIV,
                    VariableOperand(opAvr),
                    VariableOperand(opBvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "negate") {
        qLogDebugfmt("Generator: Operator negate %d\n", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        // type check
        // things become a bit complex..
        if(!(NumericVarType(opAts.begin()->basetype))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator negate: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        tmpts = opAts;
        tmpvr = G.idtable.define_variable(
                "op_negate_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for negate operator %d\n",
                    node->lineno);
            abort();
        }
        // this is done by zero subtraction
        G.codes.push_back(InstructionFormat(OP_SUB,
                    VariableOperand(G.int_zero),
                    VariableOperand(opAvr),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "not") {
        qLogDebugfmt("Generator: Operator not %d\n", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        // type check
        // things become a bit complex..
        if(opAts.begin()->basetype != VTYPE_INTEGER){
            qLogFailfmt("Semantic Analysis: incompatible type for operator not: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        tmpts = opAts;
        tmpvr = G.idtable.define_variable(
                "op_not_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for operator not %d\n",
                    node->lineno);
            abort();
        }
        // this is done by zero subtraction
        G.codes.push_back(InstructionFormat(OP_NOT,
                    VariableOperand(opAvr),
                    Operand(),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "dereference") {
        // reaching this means the result of dereference is treated as
        // rvalue. We can safely use temporal variables to replace it.
        qLogDebugfmt("Generator: Operator dereference/temporal %d\n", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        // type check
        // things become a bit complex..
        if((opAts.begin()->basetype != VTYPE_POINTER) &&
                (opAts.begin()->basetype != VTYPE_ARRAY)){
            qLogFailfmt("Semantic Analysis: dereferencing non-reference value: %d\n",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        tmpts = opAts;
        tmpts.pop_front();
        tmpvr = G.idtable.define_variable(
                "op_deref_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for operator not %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_LOAD,
                    VariableOperand(opAvr),
                    Operand(),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "address") {
        qLogDebugfmt("Generator: Operator addressof %d\n", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        bool tmpsucc = true;
        tmpts = opAts;
        tmpts.push_front(NewTypeSignature(VTYPE_POINTER));
        tmpvr = G.idtable.define_variable(
                "op_addrof_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for operator addrof %d\n",
                    node->lineno);
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_GETADDR,
                    VariableOperand(opAvr),
                    Operand(),
                    VariableOperand(tmpvr)));
        if(tmpvar_refr != nullptr) *tmpvar_refr = tmpvr;
        if(result_type != nullptr) *result_type = tmpts;
    } else if(node->data.identifier == "member") {
        // currently structures is not supported, so member
        // operator is only used to access standard library functions.

    }
}

void NodeOpCall(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpIdentifier(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpLiteralInteger(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpLiteralFloat(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpLiteralString(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpArgumentList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpIndexAccess(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOpBreakClause(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    G.codes.push_back(InstructionFormat(OP_BREAK,
                Operand(), Operand(), Operand()));
}

void NodeOpContinueClause(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    G.codes.push_back(InstructionFormat(OP_CONTINUE,
                Operand(), Operand(), Operand()));
}

void NodeOpInitializerList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Initializer list not supported yet..");
    abort();
}

void NodeOpLiteralNullptr(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}

void NodeOperator(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){

}
