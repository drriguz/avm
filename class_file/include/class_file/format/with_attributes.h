#ifndef _AVM_WITH_ATTRIBUTE_INFO_H_
#define _AVM_WITH_ATTRIBUTE_INFO_H_

#include <vector>
#include <memory>

#include "constant_pool.h"
#include "types.h"
#include "attribute/attribute_info.h"
#include "class_file/exceptions.h"

namespace avm {
class WithAttributes {
	friend class JavaClassParser;
public:
    WithAttributes();
    virtual ~WithAttributes();
public:
    void addAttribute(AttributeInfo* attribute);
    inline const u2& getAttributesCount() const {
        return _attributesCount;
    }
    const AttributeInfo* getAttributeAt(const u2 &index) const;
protected:
    u2 _attributesCount;
    std::vector<std::unique_ptr<AttributeInfo>> _attributes;
};
}

#endif
