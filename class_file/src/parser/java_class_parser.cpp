#include "class_file/parser/java_class_parser.h"
#include "class_file/parser/file_reader.h"
#include "class_file/exceptions.h"
#include "class_file/format/attribute/attribute_types.h"

#include <iostream>

using namespace avm;

JavaClassParser::JavaClassParser(const char *filePath)
:_reader(new BinaryFileReader(filePath)) {

}

JavaClassParser::~JavaClassParser() {
	if(_reader)
		delete _reader;
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
    out._constantPool = new ConstantPool(count);
    ConstantPool *constantPool = out._constantPool;
    constantPool->push_empty();
    for (u2 i = 1; i < constantPool->_constantCount; i++) {
        u1 tag;
        _reader->readU1(&tag);
        const ConstantType type = static_cast<ConstantType>(tag);
        ConstantInfo *info = readConstant(type);
        constantPool->push_back(info);
        /*
         * If a CONSTANT_Long_info or CONSTANT_Double_info structure is the item in the constant_pool table at index n, then the next usable item in the pool is located at index n+2. The constant_pool index n+1 must be valid but is considered unusable.
         */
        if (type == Long || type == Double) {
            constantPool->push_empty();
            i++;
        }
    }
}

ConstantInfo* JavaClassParser::readConstant(const ConstantType &type) {
    switch (type) {
        case Class:
            return new ConstantClass(_reader->readU2());
        case Fieldref: {
            u2 classIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
            return new ConstantFieldref(classIndex, nameAndTypeIndex);
        }
        case Methodref: {
            u2 classIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
            return new ConstantMethodref(classIndex, nameAndTypeIndex);
        }
        case InterfaceMethodref: {
            u2 classIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
            return new ConstantInterfaceMethodref(classIndex, nameAndTypeIndex);
        }
        case String:
            return new ConstantString(_reader->readU2());
        case Integer:
            return new ConstantInteger(_reader->readU4());
        case Float:
            return new ConstantFloat(_reader->readU4());
        case Long: {
            u4 highBytes = _reader->readU4(), lowBytes = _reader->readU4();
            return new ConstantLong(highBytes, lowBytes);
        }
        case Double: {
            u4 highBytes = _reader->readU4(), lowBytes = _reader->readU4();
            return new ConstantDouble(highBytes, lowBytes);
        }
        case NameAndType: {
            u2 nameIndex = _reader->readU2(), descriptionIndex = _reader->readU2();
            return new ConstantNameAndType(nameIndex, descriptionIndex);
        }
        case Utf8: {
            u2 length;
            char *buffer;
            _reader->readU2(&length);

            buffer = new char[length + 1];
            _reader->read(buffer, length);
            buffer[length] = '\0';
            return new ConstantUtf8(length, std::string(buffer));
        }
        case MethodHandle: {
            u1 referenceKind = _reader->readU1();
            u2 rererenceIndex = _reader->readU2();
            return new ConstantMethodHandle(referenceKind, rererenceIndex);
        }
        case MethodType:
            return new ConstantMethodType(_reader->readU2());
        case InvokeDynamic: {
            u2 bootstrapMethodAttrIndex = _reader->readU2(), nameAndTypeIndex = _reader->readU2();
            return new ConstantInvokeDynamic(bootstrapMethodAttrIndex,
                    nameAndTypeIndex);
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
	readAttributes(out._constantPool, out);

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
		readField(out._constantPool, out._fields[i]);
    }
}

void JavaClassParser::readMethods(JavaClass &out) {
    _reader->readU2(&out._methodsCount);
    out.initializeMethods();
    for (u2 i = 0; i < out._methodsCount; i++) {
        readMethod(out._constantPool, out._methods[i]);
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

AttributeInfo* JavaClassParser::readAttribute(const ConstantPool* constants, const AttributeTypes &type) {
	switch(type) {
	case CONSTANT_VALUE:
		return new ConstantValue(_reader->readU2());
	}
    return nullptr;
}

void JavaClassParser::readAttributes(const ConstantPool* constants, WithAttributes& out) {
	_reader->readU2(&out._attributesCount);

	u2 nameIndex;
	u4 length;
	for (u2 i = 0; i < out._attributesCount; i++) {
		_reader->readU2(&nameIndex);
		_reader->readU4(&length);

		const std::string name = constants->getString(nameIndex);
		if(name == "ConstantValue")
			readAttribute(constants, AttributeTypes::CONSTANT_VALUE);
		else{
			_reader->skip(length);
		}
	}
}
