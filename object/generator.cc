#include "generator.hpp"
#include "../format/log.hpp"
#include "../utility/utility.hpp"

using namespace std;

static inline uint8_t VType2IType(uint8_t vtype) {
    if(vtype == VTYPE_INTEGER) return ITYPE_INTEGER;
    if(vtype == VTYPE_FLOAT) return ITYPE_FLOAT;
    if(vtype == VTYPE_STRING) return ITYPE_STRING;
    if(vtype == VTYPE_POINTER) return ITYPE_POINTER;
    qLogFailfmt("Generator: No matching itype for vtype %d", vtype);
    abort();
    return -1;
}

void NodeOpInvalid(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Reached invalid AST Node.");
}

void NodeOpMasterList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: MasterList(%d)", node->lineno);
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    if(node->childs[1] != nullptr) NodeOperator(node->childs[1], G, nullptr, nullptr);
}

void NodeOpGlobalVariable(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Define Global Variable(%d)", node->lineno);
    G.idtable.curr_vartype.clear();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.idtable.curr_vartype.clear();
}

FunctionSignature ReadFuncSignature(ASTNode* node, Generator& G) {
    FunctionSignature fsign;
    if((node->type != TYPE_FUNC_DECL) && (node->type != TYPE_FUNC_DEF)) {
        qLogFail("Generator: reading function signature from non-function nodes.");
        abort();
    }
    G.idtable.curr_vartype.clear();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    fsign.return_type = G.idtable.curr_vartype;
    qLogDebugfmt("Generator: ret type discovery: %s", TypeSignaturePrinter(G.idtable.curr_vartype).c_str());
    G.idtable.curr_vartype.clear();
    node = node->childs[1];
    if(node->childs[0] == nullptr) {
        fsign.param_types.clear();
        return fsign;
    }
    node = node->childs[0];
    while(node != nullptr){
        G.idtable.curr_vartype.clear();
        NodeOperator(node->childs[0]->childs[0], G, nullptr, nullptr);
        fsign.param_types.push_back(G.idtable.curr_vartype);
        qLogDebugfmt("Generator: param type discovery: %s", TypeSignaturePrinter(G.idtable.curr_vartype).c_str());
        G.idtable.curr_vartype.clear();
        node = node->childs[1];
    }
    return fsign;
}

void NodeOpFuncDeclaration(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    auto deftry = G.idtable.func_ids.find(node->childs[1]->data.identifier);
    if(deftry != G.idtable.func_ids.end()){
        qLogWarnfmt("Semantic Analysis: Multiple declarations for function %s.",
                node->childs[1]->data.identifier.c_str());
        return;
    }
    qLogDebugfmt("Generator: Function decl: %s", node->childs[1]->data.identifier.c_str());
    auto fsign = ReadFuncSignature(node, G);
    fsign.namespc = 1;
    fsign.funcid = G.idtable.curr_funcid;
    G.idtable.curr_funcid++;
    G.idtable.func_ids[node->childs[1]->data.identifier] = fsign;
}

void NodeOpFuncDefinition(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Function definition: %s", node->childs[1]->data.identifier.c_str());
    auto fsign = ReadFuncSignature(node, G);
    auto deftry = G.idtable.func_ids.find(node->childs[1]->data.identifier);
    if(deftry != G.idtable.func_ids.end()){
        if(!FuncSignatureCompare((*deftry).second, fsign)){
            qLogFailfmt("Semantic Analysis: Prototype mismatch for function %s.",
                    node->childs[1]->data.identifier.c_str());
            abort();
        }
    }
    fsign.namespc = 1;
    fsign.funcid = G.idtable.curr_funcid;
    G.idtable.curr_funcid++;
    G.idtable.func_ids[node->childs[1]->data.identifier] = fsign;
    if(node->childs[1]->data.identifier == "main"){
        qLogDebugfmt("Generator: main function detected at %u", fsign.funcid);
        G.entr_func_id = fsign.funcid;
    }
    G.codes.push_back(InstructionFormat(OP_FUNC, 
                ImmediateOperand(fsign.namespc),
                ImmediateOperand(fsign.funcid),
                Operand()));
    G.idtable.scope_push();
    // Creating parameter takeplace in this scope
    qLogDebug("Generator: Creating parameter takeplace..");
    auto pnameit = node->childs[1]->childs[0];
    for(auto &ptype: fsign.param_types) {
        bool succ = true;
        G.idtable.define_variable(
                pnameit->childs[0]->childs[1]->data.identifier,
                ptype, succ);
        if(!succ) {
            qLogFailfmt("Generator: failed to set takeplace for parameter %s", 
                pnameit->childs[0]->childs[1]->data.identifier.c_str());
            abort();
        }
        qLogDebugfmt("Generator: parameter %s", 
            pnameit->childs[0]->childs[1]->data.identifier.c_str());
        pnameit = pnameit->childs[1];
    }
    NodeOperator(node->childs[2], G, nullptr, nullptr);
}

void NodeOpTypeSpecification(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    /* qLogDebugfmt("Generator: Simple type specification: %s", node->data.identifier.c_str()); */
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
    qLogDebug("Generator: Variable declaration list");
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    if(node->childs[1] != nullptr) NodeOperator(node->childs[1], G, nullptr, nullptr);
}

static VariableReference ComplexTypeDefGen(list<TypeSignature> comp_type, Generator& G, string prefix, string itsname){
    auto curriter = comp_type.begin();
    uint8_t currtype = (*(comp_type.begin())).basetype;
    bool vardef_succ = true;
    list<TypeSignature> temp_deftype;
    qLogDebugfmt("Generator: Complex type recursion reach <%s>.", TypeSignaturePrinter(comp_type).c_str());
    /* if(currtype == VTYPE_INTEGER) { */
    /*     temp_deftype.push_back(NewTypeSignature(VTYPE_INTEGER)); */
    /*     auto vr = G.idtable.define_variable(prefix + itsname + uint_to_string(G.temporals_id), */ 
    /*             temp_deftype, vardef_succ); */
    /*     G.temporals_id++; */
    /*     if(!vardef_succ) { */
    /*         qLogFailfmt("Generator: When generating complex type for %s.", */
    /*                 (prefix+itsname).c_str()); */
    /*         abort(); */
    /*     } */
    /*     G.codes.push_back(InstructionFormat(OP_VARDEF, */
    /*                 ImmediateOperand(0), */
    /*                 ImmediateOperand(ITYPE_INTEGER), */ 
    /*                 VariableOperand(vr))); */
    /*     qLogDebugfmt("Generator: Variable reference No.%d", vr.varid); */
    /*     return vr; */
    /* } else if (currtype == VTYPE_FLOAT) { */
    /*     temp_deftype.push_back(NewTypeSignature(VTYPE_FLOAT)); */
    /*     auto vr = G.idtable.define_variable(prefix + itsname + uint_to_string(G.temporals_id), */ 
    /*             temp_deftype, vardef_succ); */
    /*     G.temporals_id++; */
    /*     if(!vardef_succ) { */
    /*         qLogFailfmt("Generator: When generating complex type for %s.", */
    /*                 (prefix+itsname).c_str()); */
    /*         abort(); */
    /*     } */
    /*     G.codes.push_back(InstructionFormat(OP_VARDEF, */
    /*                 ImmediateOperand(0), */
    /*                 ImmediateOperand(ITYPE_FLOAT), */
    /*                 VariableOperand(vr))); */
    /*     qLogDebugfmt("Generator: Variable reference No.%d", vr.varid); */
    /*     return vr; */
    /* } else if (currtype == VTYPE_STRING) { */
    /*     temp_deftype.push_back(NewTypeSignature(VTYPE_STRING)); */
    /*     auto vr = G.idtable.define_variable(prefix + itsname + uint_to_string(G.temporals_id), */ 
    /*             temp_deftype, vardef_succ); */
    /*     G.temporals_id++; */
    /*     if(!vardef_succ) { */
    /*         qLogFailfmt("Generator: When generating complex type for %s.", */
    /*                 (prefix+itsname).c_str()); */
    /*         abort(); */
    /*     } */
    /*     G.codes.push_back(InstructionFormat(OP_VARDEF, */
    /*                 ImmediateOperand(0), */
    /*                 ImmediateOperand(ITYPE_STRING), */
    /*                 VariableOperand(vr))); */
    /*     qLogDebugfmt("Generator: Variable reference No.%d", vr.varid); */
    /*     return vr; */
    if (currtype == VTYPE_POINTER) {
        // pointer is also terminating.
        temp_deftype = comp_type;
        auto vr = G.idtable.define_variable(prefix + itsname,
                temp_deftype, vardef_succ);
        G.temporals_id++;
        if(!vardef_succ) {
            qLogFailfmt("Generator: When generating complex type for %s.",
                    (prefix+itsname).c_str());
            abort();
        }
        G.codes.push_back(InstructionFormat(OP_VARDEF,
                    ImmediateOperand(0),
                    ImmediateOperand(ITYPE_POINTER),
                    VariableOperand(vr)));
        qLogDebugfmt("Generator: Variable reference No.%d", vr.varid);
        return vr;
    } else if(currtype == VTYPE_ARRAY) {
        // firstly, we has to check whether the next type is basic type
        auto nextiter = comp_type.begin();
        nextiter++;
        auto nexttype = ((*nextiter).basetype);
        if(SimpleVarType(nexttype)){
            temp_deftype = comp_type;
            auto vr = G.idtable.define_variable(prefix + itsname,
                    temp_deftype, vardef_succ);
            G.temporals_id++;
            if(!vardef_succ) {
                qLogFailfmt("Generator: When generating complex type for %s.",
                        (prefix+itsname).c_str());
                abort();
            }
            G.codes.push_back(InstructionFormat(OP_VARDEF, ImmediateOperand((*curriter).arraysize),
                        ImmediateOperand(VType2IType(nexttype)), VariableOperand(vr)));
            qLogDebugfmt("Generator: Variable reference No.%d", vr.varid);
            return vr;
        } else {
            auto arrsize = ((*nextiter).arraysize);
            VariableReference nlvrs[arrsize];
            auto nltype = comp_type;
            nltype.pop_front();
            for(unsigned int i = 0; i < arrsize; i++){
                auto nlvr = ComplexTypeDefGen(nltype, G, prefix + "__arr" + uint_to_string(G.idtable.curr_varid)
                        , itsname);
                nlvrs[i] = nlvr;
            }
            auto vr = G.idtable.define_variable(prefix + itsname,
                    comp_type, vardef_succ);
            G.temporals_id++;
            if(!vardef_succ) {
                qLogFailfmt("Generator: When generating complex type for %s.",
                        (prefix+itsname).c_str());
                abort();
            }
            qLogDebugfmt("Generator: Variable reference No.%d", vr.varid);
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
        qLogFail("Generator: Unrecognized type in curr_type.");
        abort();
    }
}

void NodeOpVariableName(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Define variable %s", node->data.identifier.c_str());
    // Check variable type
    if(G.idtable.curr_vartype.size() == 0) {
        qLogFail("Generator: variable definition with invalid(empty) current type.");
        abort();
    }
    if(G.idtable.curr_vartype.size() == 1) {
        // this is the simple types.
        // we can directly generate it.
        uint8_t currtype = (*G.idtable.curr_vartype.begin()).basetype;
        qLogDebugfmt("Generator: as type [%s]", TypeSignatureStr[currtype]);
        // Register it
        bool vardef_succ = true;
        auto vr = G.idtable.define_variable(node->data.identifier, G.idtable.curr_vartype, vardef_succ);
        if(!vardef_succ){
            qLogFailfmt("Semantic Analysis: at (%d). Aborting...", node->lineno);
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
        } else if (currtype == VTYPE_POINTER) {
            G.codes.push_back(InstructionFormat(OP_VARDEF,
                        ImmediateOperand(0),
                        ImmediateOperand(ITYPE_POINTER),
                        VariableOperand(vr)));
        } else {
            qLogFailfmt("Generator: invalid simple type code %d?? Aborting...", currtype);
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
        NodeOperator(node->childs[0], G, nullptr, nullptr);
    } else {
        qLogFailfmt("Generator: unknown complex type identifier %s",
                node->data.identifier.c_str());
        abort();
    }
}

void NodeOpFuncPrototype(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Operation on non-operative node FuncPrototype.");
    abort();
}

void NodeOpParameterList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Operation on non-operative node ParameterList.");
    abort();
}

void NodeOpParameter(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Generator: Operation on non-operative node Parameter.");
    abort();
}

void NodeOpStatementBlock(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebug("Generator: Statement block stated.");
    G.idtable.scope_push();
    NodeOperator(node->childs[0], G, nullptr, nullptr);
    G.idtable.scope_pop();
    qLogDebug("Generator: Statement block ended.");
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
        qLogWarnfmt("Semantic Analysis: Empty expression at %d", node->lineno);
        return;
    }
    NodeOperator(node->childs[0], G, tmpvar_refr, result_type);
}

void NodeOpReturn(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: generating return at %d", node->lineno);
    VariableReference x;
    NodeOperator(node->childs[0], G, &x, nullptr);
    G.codes.push_back(InstructionFormat(OP_RET,
                VariableOperand(x),
                Operand(), Operand()));
}

void NodeOpCondIfTrue(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: iftrue at %d", node->lineno);
    VariableReference condreslt;
    list<TypeSignature> condtype;
    NodeOperator(node->childs[0], G, &condreslt, &condtype);
    if(condtype.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: Using non-boolean values for if statement %d.",
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
    qLogDebugfmt("Generator: if at %d", node->lineno);
    VariableReference condreslt;
    list<TypeSignature> condtype;
    NodeOperator(node->childs[0], G, &condreslt, &condtype);
    if(condtype.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: Using non-boolean values for if statement %d.",
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
    qLogDebugfmt("Generator: while-loop at %d", node->lineno);
    G.codes.push_back(InstructionFormat(OP_LOOPCOND, 
                Operand(), Operand(), Operand()));
    VariableReference condreslt;
    list<TypeSignature> condtype;
    NodeOperator(node->childs[0], G, &condreslt, &condtype);
    if(condtype.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: Using non-boolean values for loop condition %d.",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_LOOP,
                VariableOperand(condreslt), Operand(), Operand()));
    G.in_loops++;
    NodeOperator(node->childs[1], G, nullptr, nullptr);
    G.in_loops--;
    G.codes.push_back(InstructionFormat(OP_LOOPEND,
                Operand(), Operand(), Operand()));
}

void NodeOpVariableDefinition(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogDebugfmt("Generator: Define Local Variable(%d)", node->lineno);
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
        qLogFailfmt("Semantic Analysis: Type mismatch in line %d",
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
        qLogDebug("Generator: Initialized");
    } else if(currts == VTYPE_STRING) {
        G.codes.push_back(InstructionFormat(OP_ADD,
                    VariableOperand(tmpref),
                    VariableOperand(G.string_zero),
                    VariableOperand(vref)));
        qLogDebug("Generator: Initialized");
    } else {
        qLogFailfmt("Semantic Analysis: Initializer on unsupported type at line %d.",
                node->lineno);
        abort();
    }
    if(node->childs[2] != nullptr) NodeOperator(node->childs[2], G, &tmpref, &tmptsign);
    if(tmpvar_refr != nullptr) *tmpvar_refr = vref;
    if(result_type != nullptr) *result_type = vtsign;
}

void NodeOpOperator(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(node->data.identifier == "assign") {
        // the left side has to be: identifier, dereference or access
        if(node->childs[0]->type == TYPE_IDENTIFIER) {
            qLogDebugfmt("Generator: assign to identifier %d",
                    node->lineno);
            // for identifiers, we extract it out from identifier list
            list<TypeSignature> asts;
            bool succ = true;
            VariableReference asvr = G.idtable.get_variable(node->childs[0]->data.identifier, &asts, succ);
            if(!succ) {
                qLogFailfmt("Semantic Analysis: Undefined identifier: %s, %d",
                        node->childs[0]->data.identifier.c_str(),
                        node->childs[0]->lineno);
                abort();
            }
            list<TypeSignature> valts;
            VariableReference valvr;
            NodeOperator(node->childs[1], G, &valvr, &valts);
            if(!TypeSignatureCompare(asts, valts)){
                if(!TypeCheck(asts, VTYPE_POINTER, valts, VTYPE_ARRAY)){
                    qLogFailfmt("Semantic Analysis: Type mismatch for assignment. %d",
                            node->lineno);
                    abort();
                } else {
                    qLogDebugfmt("Semantic Analysis: Using array name as pointer here.. %d",
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
                qLogFailfmt("Semantic Analysis: You cant direct assign complex types. %d",
                        node->lineno);
                abort();
            }
            if(tmpvar_refr != nullptr) *tmpvar_refr = valvr;
            if(result_type != nullptr) *result_type = valts;
        } else if ((node->childs[0]->type == TYPE_OPERATOR) || 
                node->childs[0]->data.identifier == "dereference"){
            qLogDebugfmt("Generator: assign to dereference accesses %d",
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
                    qLogFailfmt("Semantic Analysis: Type mismatch for *deref* assignment. %d",
                            node->lineno);
                    abort();
                } else {
                    qLogDebugfmt("Semantic Analysis: Using array name as pointer here.. %d",
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
            qLogDebugfmt("Generator: assign to array access %d",
                    node->lineno);
            list<TypeSignature> arrts, idxts;
            VariableReference arrvr, idxvr;
            NodeOperator(node->childs[0]->childs[0], G, &arrvr, &arrts);
            NodeOperator(node->childs[0]->childs[1], G, &idxvr, &idxts);
            // type checks
            if(idxts.begin()->basetype != VTYPE_INTEGER){
                qLogFail("Semantic Analysis: using non-integer as array access operand.");
                abort();
            }
            list<TypeSignature> realts = arrts;
            realts.pop_front();
            list<TypeSignature> valts;
            VariableReference valvr;
            NodeOperator(node->childs[1], G, &valvr, &valts);
            if(!TypeSignatureCompare(realts, valts)) {
                if(!TypeCheck(realts, VTYPE_POINTER, valts, VTYPE_ARRAY)){
                    qLogFailfmt("Semantic Analysis: Type mismatch for *access* assignment. %d",
                            node->lineno);
                    abort();
                } else {
                    qLogDebugfmt("Semantic Analysis: Using array name as pointer here.. %d",
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
                qLogFailfmt("Generator: while registering temporal for array access assignment %d",
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
            qLogFailfmt("Semantic Analysis: Using right values as assignment target %d.",
                    node->lineno);
            abort();
        }
    } else if(node->data.identifier == "and") {
        qLogDebugfmt("Generator: Operator and %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: logical operator between non-integer variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_and_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for and operator %d",
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
        qLogDebugfmt("Generator: Operator or %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: logical operator between non-integer variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_or_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for or operator %d",
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
        qLogDebugfmt("Generator: Operator lesser %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_lesser_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for lesser operator %d",
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
        qLogDebugfmt("Generator: Operator leq %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_leq_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for leq operator %d",
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
        qLogDebugfmt("Generator: Operator gre %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_gre_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for gre operator %d",
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
        qLogDebugfmt("Generator: Operator geq %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype != VTYPE_INTEGER) ||
                (opBts.begin()->basetype != VTYPE_INTEGER)){
            qLogFailfmt("Generator: compare operator between non-integer variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_geq_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for geq operator %d",
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
        qLogDebugfmt("Generator: Operator equ %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        if((opAts.begin()->basetype  != opBts.begin()->basetype)){
            qLogFailfmt("Generator: EQUAL operator between different type variable %d",
                    node->lineno);
        }
        bool tmpsucc = true;
        tmpts.push_back(NewTypeSignature(VTYPE_INTEGER));
        tmpvr = G.idtable.define_variable(
                "op_equ_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for equ operator %d",
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
        qLogDebugfmt("Generator: Operator add %d", node->lineno);
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
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op + %d",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_add_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for add operator %d",
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
        qLogDebugfmt("Generator: Operator minus %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if((!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype)))
                && (!TypeCheck(opAts, VTYPE_POINTER, opBts, VTYPE_INTEGER))
                && (!TypeCheck(opAts, VTYPE_ARRAY, opBts, VTYPE_INTEGER))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op - %d",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_minus_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for minus operator %d",
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
        qLogDebugfmt("Generator: Operator multiply %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if(!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op * %d",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_mul_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for multiply operator %d",
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
        qLogDebugfmt("Generator: Operator divide %d", node->lineno);
        list<TypeSignature> opAts, opBts, tmpts;
        VariableReference opAvr, opBvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        NodeOperator(node->childs[1], G, &opBvr, &opBts);
        // type check
        // things become a bit complex..
        if(!(NumericVarType(opAts.begin()->basetype) && NumericVarType(opBts.begin()->basetype))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator +: %d",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        if((opAts.begin()->basetype == VTYPE_FLOAT) ||
                (opBts.begin()->basetype == VTYPE_FLOAT)){
            qLogDebugfmt("Semantic Analysis: implicit type promotion: int->float for op / %d",
                    node->lineno);
            tmpts.push_back(NewTypeSignature(VTYPE_FLOAT));
        } else{
            tmpts = opAts;
        }
        tmpvr = G.idtable.define_variable(
                "op_div_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for divide operator %d",
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
        qLogDebugfmt("Generator: Operator negate %d", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        // type check
        // things become a bit complex..
        if(!(NumericVarType(opAts.begin()->basetype))){
            qLogFailfmt("Semantic Analysis: incompatible type for operator negate: %d",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        tmpts = opAts;
        tmpvr = G.idtable.define_variable(
                "op_negate_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for negate operator %d",
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
        qLogDebugfmt("Generator: Operator not %d", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        // type check
        // things become a bit complex..
        if(opAts.begin()->basetype != VTYPE_INTEGER){
            qLogFailfmt("Semantic Analysis: incompatible type for operator not: %d",
                    node->lineno);
            abort();
        }
        bool tmpsucc = true;
        tmpts = opAts;
        tmpvr = G.idtable.define_variable(
                "op_not_temporal_" + uint_to_string(G.idtable.curr_varid),
                tmpts, tmpsucc);
        if(!tmpsucc){
            qLogFailfmt("Generator: while creating temporal for operator not %d",
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
        qLogDebugfmt("Generator: Operator dereference/temporal %d", node->lineno);
        list<TypeSignature> opAts, tmpts;
        VariableReference opAvr, tmpvr;
        NodeOperator(node->childs[0], G, &opAvr, &opAts);
        // type check
        // things become a bit complex..
        if((opAts.begin()->basetype != VTYPE_POINTER) &&
                (opAts.begin()->basetype != VTYPE_ARRAY)){
            qLogFailfmt("Semantic Analysis: dereferencing non-reference value: %d",
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
            qLogFailfmt("Generator: while creating temporal for operator not %d",
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
        qLogDebugfmt("Generator: Operator addressof %d", node->lineno);
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
            qLogFailfmt("Generator: while creating temporal for operator addrof %d",
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
        qLogFailfmt("Semantic Analysis: member operator is only allowed to use on function calls. %d",
                node->lineno);
        abort();
    } else {
        qLogFailfmt("Generator: unknown operator node id %s (%d)",
                node->data.identifier.c_str(), node->lineno);
        abort();
    }
}

void NodeOpCall(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    // not supporting function pointers yet, so things is easy
    FunctionSignature fsign;
    if(node->childs[0]->type == TYPE_IDENTIFIER){
        auto funcname = node->childs[0]->data.identifier;
        auto ftiter = G.idtable.func_ids.find(funcname);
        if(ftiter == G.idtable.func_ids.end()){
            qLogFailfmt("Semantic Analysis: undefined function name: %s (%d)",
                    funcname.c_str(), node->lineno);
            abort();
        }
        fsign = ftiter->second;
    } else if((node->childs[0]->type == TYPE_OPERATOR) && 
            (node->childs[0]->data.identifier == "member")){
        if(node->childs[0]->childs[0]->type != TYPE_IDENTIFIER) {
            qLogFailfmt("Semantic Analysis: non-identifier as structurals is not supported yet.. (%d)",
                    node->lineno);
            abort();
        }
        auto libns = node->childs[0]->childs[0]->data.identifier;
        auto libfname = node->childs[0]->data.literal_string;
        bool libsucc = true;
        fsign = G.stdlib.getfunc(libns, libfname, libsucc);
        if(!libsucc) {
            qLogFailfmt("Semantic Analysis: undefined: %s.%s (%d)",
                    libns.c_str(), libfname.c_str(), node->lineno);
            abort();
        }
    } else {
        qLogFailfmt("Semantic Analysis: func call operator on non-callable object %d",
                node->lineno);
    }
    // Parameter evaluation & type checks.
    vector<list<TypeSignature>> argument_typelist;
    vector<VariableReference> argument_reflist;
    auto argiter = node->childs[1];
    while(argiter != nullptr){
        list<TypeSignature> argts;
        VariableReference argvr;
        NodeOperator(argiter->childs[0], G, &argvr, &argts);
        argument_typelist.push_back(argts);
        argument_reflist.push_back(argvr);
        argiter = argiter->childs[1];
    }
    if(argument_typelist.size() != fsign.param_types.size()){
        qLogFailfmt("Semantic Analysis: function require %lu args, but %lu provided. (%d)",
                fsign.param_types.size(), argument_typelist.size(), node->lineno);
        abort();
    }
    // define return temporal
    bool retsucc = true;
    auto retvr = G.idtable.define_variable("func_ret_temporal_" + uint_to_string(G.idtable.curr_varid),
            fsign.return_type, retsucc);
    if(!retsucc) {
        qLogFailfmt("Generator: while generating temporal for function returns %d.",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_VARDEF,
                ImmediateOperand(0),
                ImmediateOperand(VType2IType(fsign.return_type.begin()->basetype)),
                VariableOperand(retvr)));
    for(int i = 0; i < (int)(argument_typelist.size()); i++){
        if(!TypeCheck(argument_typelist[i], fsign.param_types[i])){
            qLogFailfmt("Semantic Analysis: argument type mismatch on ArgNo.%d (%d)",
                    i, node->lineno);
            abort();
        }
        VariableReference argvr;
        argvr.varid = i;
        G.codes.push_back(InstructionFormat(OP_FUNCARG,
                    VariableOperand(argument_reflist[i]),
                    Operand(),
                    VariableOperand(argvr)));
    }
    G.codes.push_back(InstructionFormat(OP_FUNCCALL,
                ImmediateOperand(fsign.namespc),
                ImmediateOperand(fsign.funcid),
                VariableOperand(retvr)));
}

void NodeOpIdentifier(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    list<TypeSignature> idts;
    VariableReference idvr;
    bool idsucc = true;
    idvr = G.idtable.get_variable(node->data.identifier, &idts, idsucc);
    if(!idsucc) {
        qLogFailfmt("Semantic Analysis: undefined identifier: %s (%d)",
                node->data.identifier.c_str(), node->lineno);
        abort();
    }
    if(tmpvar_refr != nullptr) (*tmpvar_refr) = idvr;
    if(result_type != nullptr) (*result_type) = idts;
}

void NodeOpLiteralInteger(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    list<TypeSignature> ts;
    ts.push_back(NewTypeSignature(VTYPE_INTEGER));
    if(result_type != nullptr) (*result_type) = ts;
    if(node->data.literal_int == 0){
        if(tmpvar_refr != nullptr) (*tmpvar_refr) = G.int_zero;
        return;
    }
    if(node->data.literal_int == 1){
        if(tmpvar_refr != nullptr) (*tmpvar_refr) = G.int_one;
        return;
    }
    if(node->data.literal_int == -1){
        if(tmpvar_refr != nullptr) (*tmpvar_refr) = G.int_minusone;
        return;
    }
    // Else, register a temporal literal for that
    qLogDebugfmt("Generator: new integer literal %d",
            node->lineno);
    LiteralValue lv;
    lv.integer = node->data.literal_int;
    lv.type = LTYPE_INT;
    bool litsucc = true;
    auto lvr = G.idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFailfmt("Generator: when registering new literals at %d",
                node->lineno);
        abort();
    }
    if(tmpvar_refr != nullptr) (*tmpvar_refr) = lvr;
}

void NodeOpLiteralFloat(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    list<TypeSignature> ts;
    ts.push_back(NewTypeSignature(VTYPE_FLOAT));
    if(result_type != nullptr) (*result_type) = ts;
    if(double_equal(node->data.literal_float, 0.0l)){
        if(tmpvar_refr != nullptr) (*tmpvar_refr) = G.float_zero;
        return;
    }
    // Else, register a temporal literal for that
    qLogDebugfmt("Generator: new float literal %d",
            node->lineno);
    LiteralValue lv;
    lv.floating = node->data.literal_float;
    lv.type = LTYPE_FLOAT;
    bool litsucc = true;
    auto lvr = G.idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFailfmt("Generator: when registering new literals at %d",
                node->lineno);
        abort();
    }
    if(tmpvar_refr != nullptr) (*tmpvar_refr) = lvr;
}

void NodeOpLiteralString(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    list<TypeSignature> ts;
    ts.push_back(NewTypeSignature(VTYPE_STRING));
    if(result_type != nullptr) (*result_type) = ts;
    if(node->data.literal_string.size() == 0){
        if(tmpvar_refr != nullptr) (*tmpvar_refr) = G.string_zero;
        return;
    }
    // Else, register a temporal literal for that
    qLogDebugfmt("Generator: new string literal %d",
            node->lineno);
    LiteralValue lv;
    lv.strlit = node->data.literal_string;
    lv.type = LTYPE_STR;
    bool litsucc = true;
    auto lvr = G.idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFailfmt("Generator: when registering new literals at %d",
                node->lineno);
        abort();
    }
    if(tmpvar_refr != nullptr) (*tmpvar_refr) = lvr;
}

void NodeOpArgumentList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    // ArgumentList nodes are resolved in 'Call' nodes.
    // Shouldn't reach this
    qLogFailfmt("Semantic Analysis: unexpected reach: argument list at %d", 
            node->lineno);
    abort();
}

void NodeOpIndexAccess(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    list<TypeSignature> arrts, idxts, tmpts, rests;
    VariableReference arrvr, idxvr, tmpvr, resvr;
    NodeOperator(node->childs[0], G, &arrvr, &arrts);
    NodeOperator(node->childs[1], G, &idxvr, &idxts);
    // type checks.
    if(idxts.begin()->basetype != VTYPE_INTEGER) {
        qLogFailfmt("Semantic Analysis: non-integer index on array access: %d",
                node->lineno);
        abort();
    }
    if((arrts.begin()->basetype != VTYPE_ARRAY) &&
            (arrts.begin()->basetype != VTYPE_POINTER)){
        qLogFailfmt("Semantic Analysis: accessing non-array type elements. %d",
                node->lineno);
        abort();
    }
    tmpts = arrts;
    tmpts.pop_front();
    rests = tmpts;
    bool succ = true;
    tmpts.push_front(NewTypeSignature(VTYPE_POINTER));
    tmpvr = G.idtable.define_variable("access_ptr_temporal_" + uint_to_string(G.idtable.curr_varid),
            tmpts, succ);
    if(!succ) {
        qLogFailfmt("Generator: while generating temporals for array access. %d",
                node->lineno);
        abort();
    }
    resvr = G.idtable.define_variable("access_res_temporal_" + uint_to_string(G.idtable.curr_varid),
            rests, succ);
    if(!succ) {
        qLogFailfmt("Generator: while generating temporals for array access result. %d",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_ADD,
                VariableOperand(arrvr),
                VariableOperand(idxvr),
                VariableOperand(tmpvr)));
    G.codes.push_back(InstructionFormat(OP_LOAD,
                VariableOperand(tmpvr),
                Operand(),
                VariableOperand(resvr)));
    if(!tmpvar_refr) (*tmpvar_refr) = resvr;
    if(!result_type) (*result_type) = rests;
}

void NodeOpBreakClause(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(G.in_loops == 0) {
        qLogFailfmt("Semantic Analysis: break clause is only available inside loops. %d",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_BREAK,
                Operand(), Operand(), Operand()));
}

void NodeOpContinueClause(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(G.in_loops == 0) {
        qLogFailfmt("Semantic Analysis: continue clause is only available inside loops. %d",
                node->lineno);
        abort();
    }
    G.codes.push_back(InstructionFormat(OP_CONTINUE,
                Operand(), Operand(), Operand()));
}

void NodeOpInitializerList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    qLogFail("Initializer list not supported yet..");
    abort();
}

void NodeOpLiteralNullptr(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    if(tmpvar_refr != nullptr) (*tmpvar_refr) = G.pointer_zero;
    list<TypeSignature> ts;
    ts.push_back(NewTypeSignature(VTYPE_POINTER));
    if(result_type != nullptr) (*result_type) = ts;
}

void NodeOperator(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, list<TypeSignature>* result_type){
    NodeOperators[node->type](node, G, tmpvar_refr, result_type);
}

Generator::Generator() {
    func_id_alloc = 0;  
    entr_func_id = 0;
    in_loops = 0;
    temporals_id = 0;

    qLogDebug("Generator: basic literals..");
    LiteralValue lv;
    lv.integer = 0;
    lv.type = LTYPE_INT;
    bool litsucc = true;
    int_zero = idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFail("Generator: when registering basic literals");
        abort();
    }

    lv.integer = 1;
    lv.type = LTYPE_INT;
    litsucc = true;
    int_one = idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFail("Generator: when registering basic literals");
        abort();
    }

    lv.integer = -1;
    lv.type = LTYPE_INT;
    litsucc = true;
    int_minusone = idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFail("Generator: when registering basic literals");
        abort();
    }

    lv.floating = 0.0l;
    lv.type = LTYPE_FLOAT;
    litsucc = true;
    float_zero = idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFail("Generator: when registering basic literals");
        abort();
    }

    lv.strlit = "";
    lv.type = LTYPE_STR;
    litsucc = true;
    string_zero = idtable.define_literal(lv, litsucc);
    if(!litsucc) {
        qLogFail("Generator: when registering basic literals");
        abort();
    }

    list<TypeSignature> ptrts;
    ptrts.push_back(NewTypeSignature(VTYPE_POINTER));
    pointer_zero = idtable.define_variable("__nullptr", ptrts, litsucc);
    if(!litsucc) {
        qLogFail("Generator: when registering basic literals");
        abort();
    }
    codes.push_back(InstructionFormat(OP_VARDEF,
                ImmediateOperand(0),
                ImmediateOperand(ITYPE_POINTER),
                VariableOperand(pointer_zero)));
    codes.push_back(InstructionFormat(OP_NULLIFY,
                VariableOperand(pointer_zero),
                Operand(), Operand()));
}
