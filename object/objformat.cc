#include "objformat.hpp"
#include <cstring>

using namespace std;

VMExecutableHeader::VMExecutableHeader() {
    memcpy(magic0, "ZHWKVMEX", 8);
    magic1 = 0xdeadbeef;
    version = 1;
}

VMExecutableHeader::VMExecutableHeader(uint16_t vers) {
    memcpy(magic0, "ZHWKVMEX", 8);
    magic1 = 0xdeadbeef;
    version = vers;
}

LiteralHeader::LiteralHeader() {
    type = LTYPE_EOLIT;
    varid = 0;
    size = 0;
}

LiteralHeader::LiteralHeader(uint8_t tp, uint16_t vid, uint32_t sz) {
    type = tp;
    varid = vid;
    size = sz;
}

string LiteralValue::build() const {
    string reslt;
    switch(type) {
        case LTYPE_INT: {
            LiteralHeader lh(LTYPE_INT, this->varid, sizeof(int32_t));
            reslt += string((char*)(&lh), sizeof(LiteralHeader));
            reslt += string((char*)(&(this->integer)), sizeof(int32_t));
        }break;
        case LTYPE_FLOAT: {
            LiteralHeader lh(LTYPE_FLOAT, this->varid, sizeof(double));
            reslt += string((char*)(&lh), sizeof(LiteralHeader));
            reslt += string((char*)(&(this->floating)), sizeof(double));
        }break;
        case LTYPE_STR: {
            LiteralHeader lh(LTYPE_STR, this->varid, this->strlit.length());
            reslt += string((char*)(&lh), sizeof(LiteralHeader));
            reslt += this->strlit;
        }break;
        case LTYPE_ARRINT: {
            LiteralHeader lh(LTYPE_ARRINT, this->varid, this->intarr.size() * sizeof(int32_t));
            reslt += string((char*)(&lh), sizeof(LiteralHeader));
            reslt += string((char*)(this->intarr.data()), this->intarr.size() * sizeof(int32_t));
        }break;
        case LTYPE_ARRFLOAT: {
            LiteralHeader lh(LTYPE_ARRFLOAT, this->varid, this->floatarr.size() * sizeof(double));
            reslt += string((char*)(&lh), sizeof(LiteralHeader));
            reslt += string((char*)(this->floatarr.data()), this->floatarr.size() * sizeof(double));
        }break;
        case LTYPE_ARRSTR: {
            LiteralHeader lh(LTYPE_ARRSTR, this->varid, this->strarr.size());
            reslt += string((char*)(&lh), sizeof(LiteralHeader));
            for(int i = 0; i < (int)(this->strarr.size()); i++){
                reslt += this->strarr[i];
            }
        }break;
        default:{
            // ??
        }
    }
    return reslt;
}

string build_literal_part(const vector<LiteralValue>& literals){
    string tmpreslt;
    for(const auto& x: literals){
        tmpreslt += x.build();
    }
    LiteralHeader lh;
    tmpreslt += string((char*)(&lh), sizeof(LiteralHeader));
    return tmpreslt;
}
