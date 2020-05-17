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
    inline bool isReturned() const {
        return _returned;
    }
    inline int getPcOffset() const {
        return _pcOffset;
    }
    inline const ConstantPool * getRuntimeConstantPool() const {
        return _runtimeConstants;
    }
    inline Frame* getPreviousFrame() const {
        return _previousFrame;
    }
    void returnVoid();
    void dump() const;
protected:
    int _pcOffset;
    bool _returned;
    LocalVariables _localVariables;
    OperandStack _operandStack;
    const ConstantPool *_runtimeConstants;
    Frame* _previousFrame;
};
}
#endif
