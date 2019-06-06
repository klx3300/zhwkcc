#ifndef ZHWKVM_INSTRUCTION_H
#define ZHWKVM_INSTRUCTION_H

#include <cstdint>

const uint16_t VREF_CURRSCOPE = 0xFFFFu;

struct VariableReference {
    uint16_t scope;
    uint16_t varid;
};

union Operand {
    VariableReference as_var;
    uint32_t as_imm;
};

static inline Operand VariableOperand(VariableReference vr){
    Operand op;
    op.as_var = vr;
    return op;
}

static inline Operand VariableOperand(uint16_t scope, uint16_t varid) {
    Operand op;
    op.as_var.scope = scope;
    op.as_var.varid = varid;
    return op;
}

static inline Operand ImmediateOperand(uint32_t imm){
    Operand op;
    op.as_imm = imm;
    return op;
}

struct InstructionFormat {
    uint8_t opcode;
    Operand srcA;
    Operand srcB;
    Operand dest;
    InstructionFormat();
    InstructionFormat(uint8_t op, Operand sA, Operand sB, Operand dst);
};

enum InstructionTypeOperand {
    ITYPE_INTEGER = 0,
    ITYPE_FLOAT,
    ITYPE_STRING,
    ITYPE_POINTER
};

enum OpCodes {
    OP_NOP = 0,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_LES,
    OP_GRE,
    OP_LEQ,
    OP_GEQ,
    OP_EQU,
    OP_IF,
    OP_ELSE,
    OP_IFEND,
    OP_LOOPCOND,
    OP_LOOP,
    OP_LOOPEND,
    OP_FUNC,
    OP_RET,
    OP_FUNCARG,
    OP_FUNCCALL,
    OP_FUNCABRT,
    OP_SPUSH,
    OP_SPOP,
    OP_VARDEF,
    OP_ARRLEN,
    OP_ARRCPY,
    OP_ARRSET,
    OP_GETADDR,
    OP_LOAD,
    OP_STORE,
    OP_ALLOC,
    OP_FREE,
    OP_RELOC,
    OP_NULLIFY,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_BWAND,
    OP_BWOR,
    OP_BWNOT,
    OP_BWXOR,
    OP_ARRRESET,
    OP_BREAK,
    OP_CONTINUE,
    OP_COUNT_GUARD
};

static const char* OpNames[] = {
    "nop",
    "add",
    "sub",
    "mul",
    "div",
    "les",
    "gre",
    "leq",
    "geq",
    "equ",
    "if",
    "else",
    "ifend",
    "loopcond",
    "loop",
    "loopend",
    "func",
    "ret",
    "funcarg",
    "funccall",
    "funcabrt",
    "spush",
    "spop",
    "vardef",
    "arrlen",
    "arrcpy",
    "arrset",
    "getaddr",
    "load",
    "store",
    "alloc",
    "free",
    "reloc",
    "nullify",
    "and",
    "or",
    "not",
    "bwand",
    "bwor",
    "bwnot",
    "bwxor",
    "arrreset",
    "break",
    "continue",
    "!!Opcode Counts!!"
};


#endif
