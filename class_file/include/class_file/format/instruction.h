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
    protected:
        Mnemonic _mnemonic;
        u1* _oprands;
    };
}

#endif
