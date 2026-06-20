#ifndef _AVM_INSTRUCTION_H_
#define _AVM_INSTRUCTION_H_

#include <vector>

#include "class_file/format/types.h"
#include "class_file/format/opcodes.h"
#include "vm/exceptions.h"

namespace avm {
class Instruction {
    friend class JavaClassParser;
public:
    Instruction(const Mnemonic& mnemonic);
    Instruction(const Mnemonic& mnemonic, const u1 oprand1);
    Instruction(const Mnemonic& mnemonic, const u1 oprand1, const u1 oprand2);
    virtual ~Instruction();
public:
    inline const Mnemonic getOpcode() const {
        return _mnemonic;
    }
    inline const std::string getOpcodeName() const {
        return mnemonic_names[_mnemonic];
    }
    inline u1 getOprand(int i) const {
        Opcode config = instructionSet[_mnemonic];
        if(i < 0 || i > config.oprandCount)
            throw RuntimeException("Oprand index out of range");
        return _oprands[i];
    }
    inline u2 getOprandAsU2() const {
        u2 indexByte1 = _oprands[0], indexByte2 = _oprands[1];
        return indexByte1 << 8 | indexByte2;
    }
    // Byte offset of this instruction in the method's bytecode
    inline int getByteOffset() const {
        return _byteOffset;
    }
    // Length of this instruction in bytes (opcode + operands)
    inline int getLength() const {
        return instructionSet[_mnemonic].oprandCount + 1;
    }
protected:
    Mnemonic _mnemonic;
    std::vector<u1> _oprands;
    int _byteOffset;
};
}

#endif
