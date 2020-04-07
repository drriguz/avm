#ifndef _AVM_SOURCE_FILE_ATTRIBUTE_H_
#define _AVM_SOURCE_FILE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class SourceFile: public AttributeInfo {
public:
    SourceFile();
    virtual ~SourceFile();
};

}

#endif
