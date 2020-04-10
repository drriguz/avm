#ifndef _AVM_ATTRIBUTE_INFO_H_
#define _AVM_ATTRIBUTE_INFO_H_

#include "class_file/format/types.h"
#include "class_file/format/constant_pool.h"
#include "attribute_types.h"

namespace avm {

class AttributeInfo {
public:
    AttributeInfo(const AttributeTypes& type);
    virtual ~AttributeInfo();
public:
    inline const AttributeTypes getType() const {
        return _type;
    }
protected:
    AttributeInfo(AttributeInfo&&) {
    }
    AttributeInfo(const AttributeInfo&) {
    }
    AttributeInfo& operator=(const AttributeInfo&) {
    }
protected:
    AttributeTypes _type;
};

}

#endif
