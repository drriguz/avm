#include "class_file/format/constant_pool_visitor.h"
#include "class_file/exceptions.h"

using namespace avm;

ConstantPoolVisitor::ConstantPoolVisitor() :
        _constantPool(nullptr) {

}
ConstantPoolVisitor::~ConstantPoolVisitor() {

}

void ConstantPoolVisitor::checkConstantPool() {
    if (_constantPool == nullptr)
        throw new RuntimeException("Constant pool havn't been initialized");
}

void ConstantPoolVisitor::setConstantPool(const ConstantPool *constants) {
    if (constants == nullptr)
        throw new RuntimeException("Constant pool should not be nullptr");
    _constantPool = constants;
}

std::string ConstantPoolVisitor::getUtf8(u2 index) const {
    const ConstantUtf8 *info = (ConstantUtf8*) _constantPool->at(index);
    return info->getValue();
}
