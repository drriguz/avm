#include "class_file/parser/java_class_parser.h"
#include "class_file/exceptions.h"

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
	u2 count = readU2();
	out._constantPool = new ConstantPool(count);
	ConstantPool* constantPool = out._constantPool;
	constantPool->push_empty();
	for (u2 i = 1; i < constantPool->_constantCount; i++) {
		u1 tag;
		readU1(&tag);
		const ConstantType type = static_cast<ConstantType>(tag);
		ConstantInfo* info = readConstant(type);
		constantPool->push_back(info);
		/*
		 * If a CONSTANT_Long_info or CONSTANT_Double_info structure is the item in the constant_pool table at index n, then the next usable item in the pool is located at index n+2. The constant_pool index n+1 must be valid but is considered unusable.
		 */
		if (type == Long || type == Double){
			constantPool->push_empty();
			i++;
		}
	}
}

ConstantInfo* JavaClassParser::readConstant(const ConstantType & type){
	switch(type) {
	case Class:
		return new ConstantClass(readU2());
	case Fieldref: {
			u2 classIndex = readU2(), nameAndTypeIndex = readU2();
			return new ConstantFieldref(classIndex, nameAndTypeIndex);
		}
	case Methodref:{
			u2 classIndex = readU2(), nameAndTypeIndex = readU2();
			return new ConstantMethodref(classIndex, nameAndTypeIndex);
		}
	case InterfaceMethodref:
		{
			u2 classIndex = readU2(), nameAndTypeIndex = readU2();
			return new ConstantInterfaceMethodref(classIndex, nameAndTypeIndex);
		}
	case String:
		return new ConstantString(readU2());
	case Integer:
		return new ConstantInteger(readU4());
	case Float:
		return new ConstantFloat(readU4());
	case Long: {
			u4 highBytes = readU4(), lowBytes = readU4();
			return new ConstantLong(highBytes, lowBytes);
		}
	case Double: {
			u4 highBytes = readU4(), lowBytes = readU4();
			return new ConstantDouble(highBytes, lowBytes);
		}
	case NameAndType: {
			u2 nameIndex = readU2(), descriptionIndex= readU2();
			return new ConstantNameAndType(nameIndex, descriptionIndex);
		}
	case Utf8: {
		u2 length;
		char* buffer;
		readU2(&length);

		buffer = new char[length + 1];
		read(buffer, length);
		buffer[length] = '\0';
		return new ConstantUtf8(length, std::string(buffer));
	}
	case MethodHandle: {
			u1 referenceKind = readU1();
			u2 rererenceIndex = readU2();
			return new ConstantMethodHandle(referenceKind, rererenceIndex);
		}
	case MethodType:
		return new ConstantMethodType(readU2());
	case InvokeDynamic: {
			u2 bootstrapMethodAttrIndex = readU2(), nameAndTypeIndex= readU2();
			return new ConstantInvokeDynamic(bootstrapMethodAttrIndex, nameAndTypeIndex);
		}
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

	out.setConstantPoolReferences();
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
