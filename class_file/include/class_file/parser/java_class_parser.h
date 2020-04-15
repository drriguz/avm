#ifndef _AVM_JAVA_CLASS_PARSER_H_
#define _AVM_JAVA_CLASS_PARSER_H_

#include "binary_reader.h"
#include "class_file/format/types.h"
#include "class_file/format/java_class.h"
#include "class_file/format/field_info.h"
#include "class_file/format/method_info.h"
#include "class_file/format/attribute/attribute_types.h"
#include "class_file/format/attribute/attribute_info.h"

#include <memory>

namespace avm {

class JavaClassParser {
public:
    JavaClassParser(const char *filePath);
    virtual ~JavaClassParser();
public:
    virtual void parse(JavaClass &out);
private:
    void readHeader(JavaClass &out);
    void readConstantPool(JavaClass &out);
    std::unique_ptr<ConstantInfo> readConstant(const ConstantType &type);
    void readClassDescriptors(JavaClass &out);
    void readFields(JavaClass &out);
    void readField(const ConstantPool* constants, FieldInfo &to);
    void readMethods(JavaClass &out);
    void readMethod(const ConstantPool* constants, MethodInfo &to);
    void readAttributes(const ConstantPool* constants, WithAttributes& out);
    std::unique_ptr<Code> readCode(const ConstantPool* constants);
    std::unique_ptr<Exceptions> readExceptions(const ConstantPool* constants);
    void readInstructions(Code& out);
    void readExceptionTable(Code& out);
protected:
    std::unique_ptr<BinaryReader> _reader;
};
}

#endif
