#ifndef ZHWKVM_OBJFORMAT_H
#define ZHWKVM_OBJFORMAT_H

#include <cstdint>
#include <string>
#include <vector>

struct VMExecutableHeader {
    uint8_t magic0[8]; // = "ZHWKVMEX", no tailing 0
    uint32_t magic1; // = 0xdeadbeef, an old joke
    uint16_t version; // = 1
    VMExecutableHeader();
    VMExecutableHeader(uint16_t vers);
};

enum LiteralType {
    LTYPE_EOLIT = 0,
    LTYPE_INT,
    LTYPE_FLOAT,
    LTYPE_STR,
    LTYPE_ARRINT,
    LTYPE_ARRFLOAT,
    LTYPE_ARRSTR
};

static const char* LiteralTypeStr[] = {
    "EndOfLiterals",
    "Integer", "Float",
    "String",
    "IntegerArray",
    "FloatArray",
    "StringArray"
};


struct LiteralHeader {
    uint8_t type;
    uint16_t varid;
    uint32_t size;
    LiteralHeader();
    LiteralHeader(uint8_t tp, uint16_t vid, uint32_t sz);
};

struct LiteralValue {
    uint8_t type;
    uint16_t varid;
    int32_t integer;
    double floating;
    std::string strlit;
    std::vector<int32_t> intarr;
    std::vector<double> floatarr;
    std::vector<std::string> strarr;
    std::string build() const;
};

std::string build_literal_part(const std::vector<LiteralValue>& literals);

#endif
