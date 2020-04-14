#include "class_file/format/constant/ref.h"
#include "class_file/format/constant/constant_types.h"

#include <iostream>

using namespace avm;

ConstantRef::ConstantRef(const ConstantType &type,
                         const u2 classIndex,
                         const u2 nameAndTypeIndex) :
    ConstantInfo(type),
    _classIndex(classIndex),
    _nameAndTypeIndex(nameAndTypeIndex) {

}

ConstantFieldref::ConstantFieldref(const u2 classIndex,
                                   const u2 nameAndTypeIndex) :
    ConstantRef(ConstantType::Fieldref, classIndex, nameAndTypeIndex) {

}

ConstantMethodref::ConstantMethodref(const u2 classIndex,
                                     const u2 nameAndTypeIndex) :
    ConstantRef(ConstantType::Methodref, classIndex, nameAndTypeIndex) {

}

ConstantInterfaceMethodref::ConstantInterfaceMethodref(const u2 classIndex,
        const u2 nameAndTypeIndex) :
    ConstantRef(ConstantType::InterfaceMethodref, classIndex,
                nameAndTypeIndex) {

}

