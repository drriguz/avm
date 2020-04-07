#ifndef _AVM_FRAME_H_
#define _AVM_FRAME_H_

#include "local_variables.h"
#include "operand_stack.h"
#include "class_file/format/constant_pool.h"

namespace avm {

class Frame {
public:
    Frame(int locals, int stack, const ConstantPool *constantPool);
    virtual ~Frame();
protected:
    LocalVariables _localVariables;
    OperandStack _operandStack;
    const ConstantPool *_runtimeConstants;
};
}
#endif
