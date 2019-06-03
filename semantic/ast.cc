#include "ast.hpp"
#include <iostream>

using namespace std;


static inline void DumpWordType(WordType wt) {
    if(wt.identifier != "") {
        cout << "id:" << wt.identifier << " ";
        return;
    }
    if(wt.literal_int != 0) {
        cout << "int:" << wt.literal_int << " ";
        return;
    }
    if(wt.literal_string != "") {
        cout << "string:(" << wt.literal_string.length() << ") ";
        return;
    }
    cout << "float:" << wt.literal_float << " ";
}

ASTNode::ASTNode() {
    type = TYPE_INVAL;
    for(int i = 0; i < (int)(sizeof(childs)/sizeof(ASTNode*)); i++) {
        childs[i] = nullptr;
    }
    lineno = -1;
}

ASTNode::ASTNode(ASTNodeType typ,
            ASTNode* chld0, ASTNode* chld1, ASTNode* chld2,
            int lnumber){
    type = typ;
    childs[0] = chld0;
    childs[1] = chld1;
    childs[2] = chld2;
    lineno = lnumber;
}

void ASTNode::recursive_print(int level){
    for(int i = 0; i < level; i++){
        cout << "-";
    }
    cout << "> ";
    int tmptype = (type >= TYPE_COUNT ? TYPE_INVAL : type);
    cout << "(" << lineno << ")[" << ASTNodeTypeStr[tmptype] << "] ";
    DumpWordType(data);
    cout << endl;
    for(int i = 0; i < (int)(sizeof(childs)/sizeof(ASTNode*)); i++) {
        if(childs[i] != nullptr) {
            childs[i]->recursive_print(level+1);
        }
    }
}
