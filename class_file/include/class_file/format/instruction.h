#ifndef _AVM_INSTRUCTION_H_
#define _AVM_INSTRUCTION_H_

#include <vector>

#include "class_file/format/types.h"
#include "class_file/format/opcodes.h"

namespace avm {
    class Instruction {
    friend class JavaClassParser;
    public:
        Instruction(const Mnemonic& mnemonic);
        virtual ~Instruction();
    public:
        inline const Mnemonic getOpcode() const { return _mnemonic; }
        inline const u1 getOprand(int i) const {
            Opcode config = instructionSet[_mnemonic];
            if(i < 0 || i > config.oprandCount)
                // FIXME:
                throw "error";
            return _oprands[i];
        }
        inline const u2 getOprandAsU2() const {
            u2 indexByte1 = _oprands[0], indexByte2 = _oprands[1];
            return indexByte1 << 8 | indexByte2;
        }
    protected:
        Mnemonic _mnemonic;
        u1* _oprands;
    };
}

#endif
