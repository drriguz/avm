#include "class_file/format/instruction.h"
#include <cstring>

using namespace avm;

Instruction::Instruction(const Mnemonic& mnemonic):
    _mnemonic(mnemonic),
    _oprands() {

}

Instruction::~Instruction() {
}