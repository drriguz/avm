#ifndef _AVM_CODE_ATTRIBUTE_H_
#define _AVM_CODE_ATTRIBUTE_H_

#include <vector>
#include <memory>

#include "class_file/format/attribute/attribute_info.h"
#include "class_file/format/with_attributes.h"
#include "exception_table.h"
#include "class_file/format/instruction.h"

namespace avm {

class Code: public AttributeInfo,
    public WithAttributes {
    friend class JavaClassParser;
public:
    Code(u2  maxStack, u2  maxLocals);
    virtual ~Code();
public:
    inline u2 getMaxStack() const {
        return _maxStack;
    }
    inline u2 getMaxLocals() const {
        return _maxLocals;
    }
    inline u2 getInstructionsCount() const {
        return _opcodes.size();
    }
    inline const Instruction* getInstructionAt(u2 index) const {
        return _opcodes.at(index).get();
    }
protected:
    u2 _maxStack;
    u2 _maxLocals;
    std::vector<std::unique_ptr<Instruction>> _opcodes;
    std::vector<ExceptionTable> _exceptionTable;
};

}

#endif
