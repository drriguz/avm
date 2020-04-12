#ifndef _AVM_BYTECODE_INTERPRETER_H_
#define _AVM_BYTECODE_INTERPRETER_H_

#include "runtime/vm_thread.h"

namespace avm {
    class Interpreter{
    public:
        Interpreter();
        virtual ~Interpreter();
    public:
        void execute(VmThread* thread);
        void invoke(const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame);
    };
}
#endif