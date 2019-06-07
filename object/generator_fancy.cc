#include "generator.hpp"
#include <iostream>
#include <cstdio>
#include "../utility/utility.hpp"

using namespace std;

static void print_varef(VariableReference vr) {
    cout << vr.scope << ":" << vr.varid;
}

void Generator::dump_intercode() {
    // we dump literals first
    cout << " ============== Intercode Part ============== " << endl;
    cout << "# Literals " << endl;
    for(auto &x:idtable.literals){
        cout << "0:" << x.varid << " " << LiteralTypeStr[x.type] << " ";
        switch(x.type){
            case LTYPE_INT:
                cout << x.integer << endl;
                break;
            case LTYPE_FLOAT:
                cout << x.floating << endl;
                break;
            case LTYPE_STR:
                cout << x.strlit << endl;
                break;
            default:
                cout << endl;
        }
    }
    cout << "# Codes " << endl;
    cout.flush();
    int mxlen = 0;
    for(int i = 0; i < OP_COUNT_GUARD; i++){
        if((int)(string(OpNames[i]).length()) > mxlen){
            mxlen = ((string(OpNames[i])).length());
        }
    }
    auto fmtstr = "  %" + uint_to_string(mxlen) + "s    ";
    for(auto &x:codes){
        printf(fmtstr.c_str(), OpNames[x.opcode]);
        auto disp_part = OpParamUsage[x.opcode];
        if(x.opcode == OP_VARDEF) {
            printf("%s[%u]", ITypeStr[x.srcB.as_imm], x.srcA.as_imm);
        } else {
            if(disp_part & OpParamSrcAv) {
                printf("%hu:%hu", x.srcA.as_var.scope, x.srcA.as_var.varid);
            }
            if(disp_part & OpParamSrcAi) {
                printf("%u", x.srcA.as_imm);
            }
            if((disp_part & (OpParamSrcAi | OpParamSrcAv)) &&
                    (disp_part & (OpParamSrcBi | OpParamSrcBv))){
                printf(", ");
            }
            if(disp_part & OpParamSrcBv) {
                printf("%hu:%hu", x.srcB.as_var.scope, x.srcB.as_var.varid);
            }
            if(disp_part & OpParamSrcBi) {
                printf("%u", x.srcB.as_imm);
            }
        }
        if((disp_part & (OpParamSrcAi | OpParamSrcAv | OpParamSrcBi | OpParamSrcBv)) &&
                (disp_part & (OpParamDsti | OpParamDstv))){
            printf(", ");
        }
        if(x.opcode == OP_FUNCARG){
            printf("func:argument[%hu]", x.dest.as_var.varid);
        } else {
            if(disp_part & OpParamDstv) {
                printf("%hu:%hu", x.dest.as_var.scope, x.dest.as_var.varid);
            }
            if(disp_part & OpParamDsti) {
                printf("%u", x.dest.as_imm);
            }
        }
        printf("\n");
    }
    printf(" ENTRANCE_FUNCTION 1:%u\n", entr_func_id);
    printf(" -------------- Dump End ----------------\n");
}
