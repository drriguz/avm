#ifndef _AVM_CONSTANT_POOL_VISIOR_H_
#define _AVM_CONSTANT_POOL_VISIOR_H_

#include <string>

#include "constant_pool.h"

namespace avm {
class ConstantPoolVisitor {
public:
    ConstantPoolVisitor();
    virtual ~ConstantPoolVisitor();
public:
    void setConstantPool(const ConstantPool *constants);
    std::string getUtf8(u2 index) const;
private:
    void checkConstantPool();
protected:
    const ConstantPool *_constantPool;
};
}
#endif
