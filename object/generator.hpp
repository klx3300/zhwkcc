#ifndef ZHWKCC_GENERATOR_H
#define ZHWKCC_GENERATOR_H

#include <string>

#include "objformat.hpp"
#include "instr.hpp"
#include "../semantic/idtable.hpp"
#include "../semantic/ast.hpp"

struct Generator{
    IdTable idtable;
    std::vector<InstructionFormat> codes;
    uint32_t func_id_alloc;
    uint32_t entr_func_id;
    // these zero values are pre-generated to be literals
    // make following processes more swift.
    VariableReference int_zero;
    VariableReference float_zero;
    VariableReference string_zero;
    VariableReference pointer_zero;
    // These constants are pre-generated for convenience
    VariableReference int_one; // the integer 1
    VariableReference int_minusone; // the integer -1
    uint32_t temporals_id;
    Generator();
    std::string toExecutable();
};

typedef void (*NodeOperatorFuncType)(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);

void NodeOperator(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpInvalid(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpMasterList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpGlobalVariable(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpFuncDeclaration(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpFuncDefinition(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpTypeSpecification(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpVariableDeclaration(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpVariableName(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpComplexType(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpFuncPrototype(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpParameterList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpParameter(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpStatementBlock(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpStatementList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpExpression(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpReturn(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpCondIfTrue(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpCondIf(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpLoopWhile(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpVariableDefinition(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpInitializer(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpOperator(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpCall(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpIdentifier(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpLiteralInteger(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpLiteralFloat(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpLiteralString(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpArgumentList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpIndexAccess(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpBreakClause(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpContinueClause(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpInitializerList(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);
void NodeOpLiteralNullptr(ASTNode* node, Generator& G, VariableReference* tmpvar_refr, std::list<TypeSignature>* result_type);

const static NodeOperatorFuncType NodeOperators[] = { 
    NodeOpInvalid,
    NodeOpMasterList,
    NodeOpGlobalVariable,
    NodeOpFuncDeclaration,
    NodeOpFuncDefinition,
    NodeOpTypeSpecification,
    NodeOpVariableDeclaration,
    NodeOpVariableName,
    NodeOpComplexType,
    NodeOpFuncPrototype,
    NodeOpParameterList,
    NodeOpParameter,
    NodeOpStatementBlock,
    NodeOpStatementList,
    NodeOpExpression,
    NodeOpReturn,
    NodeOpCondIfTrue,
    NodeOpCondIf,
    NodeOpLoopWhile,
    NodeOpVariableDefinition,
    NodeOpInitializer,
    NodeOpOperator,
    NodeOpCall,
    NodeOpIdentifier,
    NodeOpLiteralInteger,
    NodeOpLiteralFloat,
    NodeOpLiteralString,
    NodeOpArgumentList,
    NodeOpIndexAccess,
    NodeOpBreakClause,
    NodeOpContinueClause,
    NodeOpInitializerList,
    NodeOpLiteralNullptr,
};



#endif
