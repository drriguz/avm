#include "class_file/parser/java_class_parser.h"
#include "class_file/parser/file_reader.h"
#include "class_file/exceptions.h"
#include "class_file/format/attribute/attribute_types.h"
#include "class_file/format/opcodes.h"
#include "class_file/format/instruction.h"

#include <iostream>
#include <memory>

using namespace avm;

JavaClassParser::JavaClassParser(const char *filePath)
    :_reader(std::unique_ptr<BinaryReader>(new BinaryFileReader(filePath))) {

}

JavaClassParser::~JavaClassParser() {
}

void JavaClassParser::readHeader(JavaClass &out) {
    try {
        _reader->readU4(&out._magic);
        if (out._magic != 0xCAFEBABE) {
            std::cerr << "Unknown file type:" << out._magic << std::endl;
            throw NotClassFileException(
                "Not a class file format: magic not valid");
        }
    } catch (const ReadFileException &ex) {
        throw NotClassFileException(
            "Not a class file format:failed to read magic");
    }
}

void JavaClassParser::readConstantPool(JavaClass &out) {
    u2 count = _reader->readU2();
    out._constantPool = std::unique_ptr<ConstantPool>(new ConstantPool(count));
    ConstantPool *constantPool = out._constantPool.get();
    constantPool->push_empty();
    for (u2 i = 1; i < constantPool->_constantCount; i++) {
        u1 tag;
        _reader->readU1(&tag);
        const ConstantType type = static_cast<ConstantType>(tag);
        auto info = readConstant(type);
        constantPool->push_back(std::move(info));
        /*
         * If a CONSTANT_Long_info or CONSTANT_Double_info structure is the item in the constant_pool table at index n, then the next usable item in the pool is located at index n+2. The constant_pool index n+1 must be valid but is considered unusable.
         */
        if (type == CONSTANT_Long || type == CONSTANT_Double) {
            constantPool->push_empty();
            i++;
        }
    }
}

std::unique_ptr<ConstantInfo> JavaClassParser::readConstant(const ConstantType &type) {
    switch (type) {
    case CONSTANT_Class:
        return std::unique_ptr<ConstantInfo>(new ConstantClass(_reader->readU2()));
    case CONSTANT_Fieldref: {
        u2 classIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
        return std::unique_ptr<ConstantInfo>(new ConstantFieldref(classIndex, nameAndTypeIndex));
    }
    case CONSTANT_Methodref: {
        u2 classIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
        return std::unique_ptr<ConstantInfo>(new ConstantMethodref(classIndex, nameAndTypeIndex));
    }
    case CONSTANT_InterfaceMethodref: {
        u2 classIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
        return std::unique_ptr<ConstantInfo>(new ConstantInterfaceMethodref(classIndex, nameAndTypeIndex));
    }
    case CONSTANT_String:
        return std::unique_ptr<ConstantInfo>(new ConstantString(_reader->readU2()));
    case CONSTANT_Integer:
        return std::unique_ptr<ConstantInfo>(new ConstantInteger(_reader->readU4()));
    case CONSTANT_Float:
        return std::unique_ptr<ConstantInfo>(new ConstantFloat(_reader->readU4()));
    case CONSTANT_Long: {
        u4 highBytes = _reader->readU4(), lowBytes = _reader->readU4();
        return std::unique_ptr<ConstantInfo>(new ConstantLong(highBytes, lowBytes));
    }
    case CONSTANT_Double: {
        u4 highBytes = _reader->readU4(), lowBytes = _reader->readU4();
        return std::unique_ptr<ConstantInfo>(new ConstantDouble(highBytes, lowBytes));
    }
    case CONSTANT_NameAndType: {
        u2 nameIndex = _reader->readU2(), descriptionIndex = _reader->readU2();
        return std::unique_ptr<ConstantInfo>(new ConstantNameAndType(nameIndex, descriptionIndex));
    }
    case CONSTANT_Utf8: {
        u2 length;
        char *buffer;
        _reader->readU2(&length);

        buffer = new char[length + 1];
        _reader->read(buffer, length);
        buffer[length] = '\0';
        return std::unique_ptr<ConstantInfo>(new ConstantUtf8(length, std::string(buffer)));
    }
    case CONSTANT_MethodHandle: {
        u1 referenceKind = _reader->readU1();
        u2 rererenceIndex = _reader->readU2();
        return std::unique_ptr<ConstantInfo>(new ConstantMethodHandle(referenceKind, rererenceIndex));
    }
    case CONSTANT_MethodType:
        return std::unique_ptr<ConstantInfo>(new ConstantMethodType(_reader->readU2()));
    case CONSTANT_InvokeDynamic: {
        u2 bootstrapMethodAttrIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
        return std::unique_ptr<ConstantInfo>(new ConstantInvokeDynamic(bootstrapMethodAttrIndex,
                                         nameAndTypeIndex));
    }
    default:
        throw ClassFormatException(
            "Unknown constant type:"
            + std::to_string((long long) type));
    }
}

void JavaClassParser::parse(JavaClass &out) {
    _reader->reset();
    readHeader(out);
    _reader->readU2(&out._minorVersion);
    _reader->readU2(&out._majorVersion);
    readConstantPool(out);
    readClassDescriptors(out);
    readFields(out);
    readMethods(out);
    readAttributes(out._constantPool.get(), out);

    out.setConstantPoolReferences();
}

void JavaClassParser::readClassDescriptors(JavaClass &out) {
    _reader->readU2(&out._accessFlags);
    _reader->readU2(&out._thisClass);
    _reader->readU2(&out._superClass);
    _reader->readU2(&out._interfacesCount);
    out.initializeInterfaces();
    for (u2 i = 0; i < out._interfacesCount; i++) {
        _reader->readU2(&out._interfaces[i]);
    }
}

void JavaClassParser::readFields(JavaClass &out) {
    _reader->readU2(&out._fieldsCount);
    out.initializeFields();
    for (u2 i = 0; i < out._fieldsCount; i++) {
        readField(out._constantPool.get(), out._fields[i]);
    }
}

void JavaClassParser::readMethods(JavaClass &out) {
    _reader->readU2(&out._methodsCount);
    out.initializeMethods();
    for (u2 i = 0; i < out._methodsCount; i++) {
        readMethod(out._constantPool.get(), out._methods[i]);
    }
}

void JavaClassParser::readField(const ConstantPool* constants, FieldInfo &field) {
    _reader->readU2(&field._accessFlags);
    _reader->readU2(&field._nameIndex);
    _reader->readU2(&field._descriptorIndex);
    readAttributes(constants, field);
}

void JavaClassParser::readMethod(const ConstantPool* constants, MethodInfo &method) {
    _reader->readU2(&method._accessFlags);
    _reader->readU2(&method._nameIndex);
    _reader->readU2(&method._descriptorIndex);
    readAttributes(constants, method);
}

void JavaClassParser::readAttributes(const ConstantPool* constants, WithAttributes& out) {
    _reader->readU2(&out._attributesCount);

    u2 nameIndex;
    u4 length;
    for (u2 i = 0; i < out._attributesCount; i++) {
        _reader->readU2(&nameIndex);
        _reader->readU4(&length);

        const std::string name = constants->getString(nameIndex);
        AttributeInfo* attribute = nullptr;
        if(name == "ConstantValue")
            attribute = new ConstantValue(_reader->readU2());
        else if(name == "Code")
            attribute = readCode(constants);
        else if(name == "Exceptions")
            attribute=  readExceptions(constants);
        else
            _reader->skip(length);

        if(attribute)
            out.addAttribute(attribute);
    }
}
Exceptions* JavaClassParser::readExceptions(const ConstantPool* constants) {
    Exceptions* attribute = new Exceptions();
    u2 count = _reader->readU2();
    for(int i = 0; i < count; i ++) {
        u2 index = _reader->readU2();
        attribute->_exceptionClasses.push_back(constants->getClassName(index));
    }
    return attribute;
}

Code* JavaClassParser::readCode(const ConstantPool* constants) {
    u2 maxStack = _reader->readU2();
    u2 maxLocals = _reader->readU2();
    Code* attribute = new Code(maxStack, maxLocals);
    readInstructions(*attribute);
    readExceptionTable(*attribute);
    readAttributes(constants, *attribute);
    return attribute;
}

void JavaClassParser::readExceptionTable(Code& attribute) {
    u2 exceptionTableLength = _reader->readU2();
    for(int i = 0; i < exceptionTableLength; i++) {
        u2 startPc = _reader->readU2();
        u2 endPc = _reader->readU2();
        u2 handlerPc = _reader->readU2();
        u2 catchType = _reader->readU2();
        attribute._exceptionTable.push_back(ExceptionTable(startPc, endPc, handlerPc, catchType));
    }
}

void JavaClassParser::readInstructions(Code& out) {
    /*
        eg. codeLength = 5, code = 2a b7 0 1 b1
        (0x2a)    aload_0
        (0xb7)    invokespecial #0x0001
        (0xb1)    return
    */
    u4 codeLength = _reader->readU4();
    for(int i = 0; i < codeLength; ) {
        u2 opcodeValue = _reader->readU1();
        Mnemonic mnemonic = static_cast<Mnemonic>(opcodeValue);
        Opcode opcode = instructionSet[opcodeValue];
        Instruction *instruction = new Instruction(mnemonic);
        if(opcode.oprandCount > 0) {
            instruction->_oprands =  new u1[opcode.oprandCount];
            for(int j = 0; j < opcode.oprandCount; j++) {
                instruction->_oprands[j] = _reader->readU1();
            }

        }
        i += (opcode.oprandCount + 1) * sizeof(u1);
        out._opcodes.push_back(std::unique_ptr<Instruction>(instruction));
    }
}