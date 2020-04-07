#ifndef _AVM_SOURCE_DEBUG_EXTENSION_ATTRIBUTE_H_
#define _AVM_SOURCE_DEBUG_EXTENSION_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class SourceDebugExtension: public AttributeInfo {
public:
    SourceDebugExtension();
    virtual ~SourceDebugExtension();
};

}

#endif
