#ifndef _AVM_CONSTANT_POOL_H_
#define _AVM_CONSTANT_POOL_H_

#include "constant/constant_info.h"
#include "constant/constant_types.h"
#include "constant/class.h"
#include "constant/ref.h"
#include "constant/string.h"
#include "constant/number.h"
#include "constant/name_and_type.h"
#include "constant/method_handle.h"
#include "constant/method_type.h"
#include "constant/invoke_dynamic.h"
#include "constant/utf8.h"

#include <vector>
#include <memory>
#include <string>

namespace avm {

class ConstantPool {
    friend class JavaClassParser;
public:
    ConstantPool(u2 count);
    virtual ~ConstantPool();
public:
    inline const u2& getConstantPoolCount() const {
        return _constantCount;
    }
    void push_back(ConstantInfo *info);
    void push_empty();
    const ConstantInfo* at(u2 index) const;
public:
	std::string getString(u2 index) const;
    std::string getClassName(u2 classInfoIndex) const;
protected:
    u2 _constantCount;
    std::vector<std::unique_ptr<ConstantInfo>> _constantPool;
};
}

#endif
