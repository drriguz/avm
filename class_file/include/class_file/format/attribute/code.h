#ifndef _AVM_CODE_ATTRIBUTE_H_
#define _AVM_CODE_ATTRIBUTE_H_

#include <vector>
#include <memory>

#include "class_file/format/attribute/attribute_info.h"
#include "class_file/format/with_attributes.h"
#include "exception_table.h"
#include "class_file/format/opcode.h"

namespace avm {

class Code: public AttributeInfo,
            public WithAttributes {
friend class JavaClassParser;
public:
    Code(const u2& maxStack, const u2& maxLocals);
    virtual ~Code();
protected:
    u2 _maxStack;
    u2 _maxLocals;
    std::vector<std::unique_ptr<Opcode>> _opcodes;
    std::vector<ExceptionTable> _exceptionTable;
};

}

#endif
