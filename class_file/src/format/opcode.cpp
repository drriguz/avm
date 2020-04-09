#include "class_file/format/opcode.h"
#include <cstring>

using namespace avm;

Opcode::Opcode(const u2& opcode, const u2& oprandsCount, const u2* oprands):
_opcode(opcode),
_oprandsCount(oprandsCount),
_oprands(nullptr){
    if(_oprandsCount != 0) {
        _oprands = new u2[_oprandsCount];
        std::memcpy(_oprands, oprands, oprandsCount * sizeof(u2));
    }
}

Opcode::~Opcode() {
    if(!_oprands) {
        delete[] _oprands;
        _oprands = nullptr;
    }
}