#include "class_file/format/instruction.h"
#include <cstring>

using namespace avm;

Instruction::Instruction(const Mnemonic& mnemonic):
    _mnemonic(mnemonic),
    _oprands(),
    _byteOffset(0) {

}

Instruction::Instruction(const Mnemonic& mnemonic, const u1 oprand1) :
    _mnemonic(mnemonic),
    _oprands(),
    _byteOffset(0) {
    _oprands.push_back(oprand1);
}

Instruction::Instruction(const Mnemonic& mnemonic, const u1 oprand1, const u1 oprand2) :
    _mnemonic(mnemonic),
    _oprands(),
    _byteOffset(0) {
    _oprands.push_back(oprand1);
    _oprands.push_back(oprand2);
}
Instruction::~Instruction() {
}