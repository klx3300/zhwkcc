#include <iostream>
#include <string>
#include "semantic/ast.hpp"
#include <cstdio>

using namespace std;

const string PROTOTYPE = "void %s(ASTNode* node, Generator& G)";
const string POINTERDEF = "typedef void (*NodeOperatorFuncType)(ASTNode* node, Generator& G);";

int main(void){
    cout << "// Header" << endl;
    cout << POINTERDEF << endl;
    for(int i = 0; i < TYPE_COUNT; i++){
        printf((string(PROTOTYPE) + ";\n").c_str(), (string("NodeOp") + ASTNodeTypeStr[i]).c_str());
    }
    cout << "const static NodeOperatorFuncType NodeOperators[] = { " << endl;
    for(int i = 0; i < TYPE_COUNT; i++){
        cout << "    NodeOp" << ASTNodeTypeStr[i] << "," << endl;
    }
    cout << "};";
    cout << "// FastDefs" << endl;
    for(int i = 0; i < TYPE_COUNT; i++){
        printf((string(PROTOTYPE) + "{\n\n}\n\n").c_str(), (string("NodeOp") + ASTNodeTypeStr[i]).c_str());
    }
    return 0;
}
