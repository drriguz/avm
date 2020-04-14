#include "class_file/format/constant_pool.h"
#include "class_file/exceptions.h"

using namespace avm;

ConstantPool::ConstantPool(u2 count) :
    _constantCount(count) {
    _constantPool.reserve(_constantCount + 1);
}

ConstantPool::~ConstantPool() {

}

void ConstantPool::push_empty() {
    _constantPool.push_back(std::unique_ptr<ConstantInfo>());
}

void ConstantPool::push_back(ConstantInfo *info) {
    _constantPool.push_back(std::unique_ptr<ConstantInfo>(info));
}

const ConstantInfo* ConstantPool::at(u2 index) const {
    if ((index < 0) || (index >= _constantCount))
        throw new RuntimeException("Index out of bound");
    return _constantPool.at(index).get();
}

std::string ConstantPool::getString(u2 index) const {
    const ConstantUtf8 *info = (ConstantUtf8*) at(index);
    return info->getValue();
}
std::string ConstantPool::getClassName(u2 classInfoIndex) const {
    const ConstantClass *info = (ConstantClass*) at(classInfoIndex);
    return getString(info->getNameIndex());
}