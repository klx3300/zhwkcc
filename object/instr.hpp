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
    OP_RELOC
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
    "reloc"
};


#endif
