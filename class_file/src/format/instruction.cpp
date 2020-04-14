#include "class_file/format/instruction.h"
#include <cstring>

using namespace avm;

Instruction::Instruction(const Mnemonic& mnemonic):
    _mnemonic(mnemonic),
    _oprands(nullptr) {

}

Instruction::~Instruction() {
    if(!_oprands) {
        delete[] _oprands;
        _oprands = nullptr;
    }
}