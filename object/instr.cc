#include "instr.hpp"

InstructionFormat::InstructionFormat() {
    opcode = OP_NOP;
    srcA = ImmediateOperand(0);
    srcB = ImmediateOperand(0);
    dest = ImmediateOperand(0);
}

InstructionFormat::InstructionFormat(uint8_t op,
        Operand sA, Operand sB, Operand dst) {
    opcode = op;
    srcA = sA;
    srcB = sB;
    dest = dst;
}


