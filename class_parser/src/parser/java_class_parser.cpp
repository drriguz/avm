#include "parser/java_class_parser.h"
#include "exceptions.h"

#include <iostream>

using namespace avm;

JavaClassParser::JavaClassParser(){

}

JavaClassParser::~JavaClassParser(){
}

void JavaClassParser::readHeader(JavaClass& out) {
	try {
		readU4(&out._magic);
		if (out._magic != 0xCAFEBABE){
			std::cerr << "Unknown file type:" << out._magic << std::endl;
			throw NotClassFileException("Not a class file format: magic not valid");
		}
	} catch (const ReadFileException &ex) {
		throw NotClassFileException("Not a class file format:failed to read magic");
	}
}

void JavaClassParser::readConstantPool(JavaClass& out) {
	readU2(&out._constantPoolCount);
	out._constantPool.clear();
	out._constantPool.reserve(out._constantPoolCount + 1);
	out._constantPool.push_back(std::unique_ptr<ConstantInfo>());
	for (u2 i = 1; i < out._constantPoolCount; i++) {
		u1 tag;
		readU1(&tag);
		const ConstantType type = static_cast<ConstantType>(tag);
		ConstantInfo* info = readConstant(type);
		out._constantPool.push_back(std::unique_ptr<ConstantInfo>(info));
		/*
		 * If a CONSTANT_Long_info or CONSTANT_Double_info structure is the item in the constant_pool table at index n, then the next usable item in the pool is located at index n+2. The constant_pool index n+1 must be valid but is considered unusable.
		 */
		if (type == Long || type == Double){
			out._constantPool.push_back(std::unique_ptr<ConstantInfo>());
			i++;
		}
	}
}

ConstantInfo* JavaClassParser::readConstant(const ConstantType & type){
	switch(type) {
	case Class:
		return new ConstantClass(readU2());
	case Fieldref:
		return new ConstantFieldref(readU2(), readU2());
	case Methodref:
		return new ConstantMethodref(readU2(), readU2());
	case InterfaceMethodref:
		return new ConstantInterfaceMethodref(readU2(), readU2());
	case String:
		return new ConstantString(readU2());
	case Integer:
		return new ConstantInteger(readU4());
	case Float:
		return new ConstantFloat(readU4());
	case Long:
		return new ConstantLong(readU4(), readU4());
	case Double:
		return new ConstantDouble(readU4(), readU4());
	case NameAndType:
		return new ConstantNameAndType(readU2(), readU2());
	case Utf8: {
		u2 length;
		char* buffer;
		readU2(&length);

		buffer = new char[length + 1];
		read(buffer, length);
		buffer[length] = '\0';
		return new ConstantUtf8(length, std::string(buffer));
	}
	case MethodHandle:
		return new ConstantMethodHandle(readU1(), readU2());
	case MethodType:
		return new ConstantMethodType(readU2());
	case InvokeDynamic:
		return new ConstantInvokeDynamic(readU2(), readU2());
	default:
		throw ClassFormatException("Unknown constant type:" + std::to_string((long long)type));
	}
}

void JavaClassParser::parse(JavaClass& out) {
	reset();
	readHeader(out);
	readU2(&out._minorVersion);
	readU2(&out._majorVersion);
	readConstantPool(out);
	readClassDescriptors(out);
	readFields(out);
	readMethods(out);
	readAttributes(out);
}

void JavaClassParser::readClassDescriptors(JavaClass &out) {
	readU2(&out._accessFlags);
	readU2(&out._thisClass);
	readU2(&out._superClass);
	readU2(&out._interfacesCount);
	out.initializeInterfaces();
	for (u2 i = 0; i < out._interfacesCount; i++) {
		readU2(&out._interfaces[i]);
	}
}

void JavaClassParser::readFields(JavaClass &out) {
	readU2(&out._fieldsCount);
	out.initializeFields();
	for (u2 i = 0; i < out._fieldsCount; i++) {
		readField(out._fields[i]);
	}
}

void JavaClassParser::readMethods(JavaClass &out) {
	readU2(&out._methodsCount);
	out.initializeMethods();
	for (u2 i = 0; i < out._methodsCount; i++) {
		readMethod(out._methods[i]);
	}
}

void JavaClassParser::readField(FieldInfo& field) {
	readU2(&field._accessFlags);
	readU2(&field._nameIndex);
	readU2(&field._descriptorIndex);
	readU2(&field._attributesCount);

	field.initializeAttributes();
	for (u2 i = 0; i < field._attributesCount; i++) {
		readAttribute(field._attributes[i]);
	}
}

void JavaClassParser::readMethod(MethodInfo& method) {
	readU2(&method._accessFlags);
	readU2(&method._nameIndex);
	readU2(&method._descriptorIndex);
	readU2(&method._attributesCount);

	method.initializeAttributes();
	for (u2 i = 0; i < method._attributesCount; i++) {
		readAttribute(method._attributes[i]);
	}
}

void JavaClassParser::readAttribute(AttributeInfo &to) {
	readU2(&to.attributeNameIndex);
	readU4(&to.attributeLength);

	char* info = new char[to.attributeLength];

	read(info, to.attributeLength);
	to.info = (u1*)info;
}

void JavaClassParser::readAttributes(JavaClass &out) {
	readU2(&out._attributesCount);
	out.initializeAttributes();
	for (u2 i = 0; i < out._attributesCount; i++) {
		readAttribute(out._attributes[i]);
	}
}
