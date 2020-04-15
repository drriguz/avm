#ifndef _AVM_WITH_ATTRIBUTE_INFO_H_
#define _AVM_WITH_ATTRIBUTE_INFO_H_

#include <vector>
#include <memory>
#include <string>

#include "constant_pool.h"
#include "types.h"
#include "class_file/exceptions.h"

#include "attribute/attribute_info.h"

namespace avm {
class WithAttributes {
    friend class JavaClassParser;
public:
    WithAttributes();
    virtual ~WithAttributes();
public:
    void addAttribute(std::unique_ptr<AttributeInfo> attribute);
    inline u2  getAttributesCount() const {
        return _attributesCount;
    }
    const AttributeInfo* getAttributeAt(const u2 index) const;
    const AttributeInfo* getAttrinute(AttributeType type) const;
    const AttributeInfo* getAttrinuteIfPresent(AttributeType type) const;
protected:
    u2 _attributesCount;
    std::vector<std::unique_ptr<AttributeInfo>> _attributes;
};
}

#endif
