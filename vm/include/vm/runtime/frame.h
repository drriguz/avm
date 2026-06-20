#ifndef _AVM_FRAME_H_
#define _AVM_FRAME_H_

#include "local_variables.h"
#include "operand_stack.h"
#include "class_file/format/constant_pool.h"

namespace avm {

class Frame {
public:
    Frame(int locals, int stack, const ConstantPool *constantPool, Frame* previousFrame);
    virtual ~Frame();
public:
    inline OperandStack* getOperandStack() {
        return &_operandStack;
    }
    inline LocalVariables* getLocalVariables() {
        return &_localVariables;
    }
    inline const ConstantPool * getRuntimeConstantPool() const {
        return _runtimeConstants;
    }
    inline Frame* getPreviousFrame() const {
        return _previousFrame;
    }
    inline int getNextPc() {
        return _pc++;
    }
    inline int getPc() const {
        return _pc;
    }
    // Returns the index of the most recently fetched instruction
    inline int getCurrentInstructionIndex() const {
        return _pc - 1;
    }
    inline void setPc(int pc) {
        _pc = pc;
    }
    void dump() const;
protected:
    int _pc;
    LocalVariables _localVariables;
    OperandStack _operandStack;
    const ConstantPool *_runtimeConstants;
    Frame* _previousFrame;
};
}
#endif
