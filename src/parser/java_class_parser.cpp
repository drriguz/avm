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
	out.initializeConstantPool();
	for (u2 i = 1; i < out._constantPoolCount; i++) {
		u1 tag;
		readU1(&tag);
		const ConstantType type = static_cast<ConstantType>(tag);
		out._constantPool[i] = *(readConstant(type));
		/*
		 * If a CONSTANT_Long_info or CONSTANT_Double_info structure is the item in the constant_pool table at index n, then the next usable item in the pool is located at index n+2. The constant_pool index n+1 must be valid but is considered unusable.
		 */
		if (type == Long || type == Double)
			i++;
	}
}

ConstantInfo* JavaClassParser::readConstant(const ConstantType & type) {
	switch(type) {
	case Class:{
		ConstantClass *classInfo = new ConstantClass();
		readU2(&classInfo->nameIndex);
		return new ConstantInfo{type, (u1 *)classInfo};
	}
	case Fieldref: {
		ConstantFieldref *fieldRefInfo = new ConstantFieldref();
		readU2(&fieldRefInfo->classIndex);
		readU2(&fieldRefInfo->nameAndTypeIndex);
		return new ConstantInfo{type, (u1 *)fieldRefInfo};
	}
	case Methodref: {
		ConstantMethodref *methodRefInfo = new ConstantMethodref();
		readU2(&methodRefInfo->classIndex);
		readU2(&methodRefInfo->nameAndTypeIndex);
		return new ConstantInfo{type, (u1 *)methodRefInfo};
	}
	case InterfaceMethodref: {
		ConstantInterfaceMethodref *interfaceMethodref = new ConstantInterfaceMethodref();
		readU2(&interfaceMethodref->classIndex);
		readU2(&interfaceMethodref->nameAndTypeIndex);
		return new ConstantInfo{type, (u1 *)interfaceMethodref};
	}
	case String: {
		ConstantString *stringInfo = new ConstantString();
		readU2(&stringInfo->stringIndex);
		return new ConstantInfo{type, (u1 *)stringInfo};
	}
	case Integer: {
		ConstantInteger *integerInfo = new ConstantInteger();
		readU4(&integerInfo->bytes);
		return new ConstantInfo{type, (u1 *)integerInfo};
	}
	case Float: {
		ConstantFloat *floatInfo = new ConstantFloat();
		readU4(&floatInfo->bytes);
		return new ConstantInfo{type, (u1 *)floatInfo};
	}
	case Long: {
		ConstantLong *longInfo = new ConstantLong();
		readU4(&longInfo->highBytes);
		readU4(&longInfo->lowBytes);
		return new ConstantInfo{type, (u1 *)longInfo};
	}
	case Double: {
		ConstantDouble *doubleInfo = new ConstantDouble();
		readU4(&doubleInfo->highBytes);
		readU4(&doubleInfo->lowBytes);
		return new ConstantInfo{type, (u1 *)doubleInfo};
	}
	case NameAndType: {
		ConstantNameAndType *nameAndTypeInfo = new ConstantNameAndType();
		readU2(&nameAndTypeInfo->nameIndex);
		readU2(&nameAndTypeInfo->descriptorIndex);
		return new ConstantInfo{type, (u1 *)nameAndTypeInfo};
	}
	case Utf8: {
		ConstantUtf8 *utf8Info = new ConstantUtf8();
		readU2(&utf8Info->length);
		utf8Info->initializeStringBuffer();
		read(reinterpret_cast<char *>(utf8Info->bytes), utf8Info->length);
		utf8Info->bytes[utf8Info->length] = '\0';
		return new ConstantInfo{type, (u1 *)utf8Info};
	}
	case MethodHandle: {
		ConstantMethodHandle *methodHandleInfo = new ConstantMethodHandle();
		readU1(&methodHandleInfo->referenceKind);
		readU2(&methodHandleInfo->referenceIndex);
		return new ConstantInfo{type, (u1 *)methodHandleInfo};
	}
	case MethodType: {
		ConstantMethodType *methodTypeInfo = new ConstantMethodType;
		readU2(&methodTypeInfo->descriptorIndex);
		return new ConstantInfo{type, (u1 *)methodTypeInfo};
	}
	case InvokeDynamic: {
		ConstantInvokeDynamic *invokeDynamicInfo = new ConstantInvokeDynamic();
		readU2(&invokeDynamicInfo->bootstrapMethodAttrIndex);
		readU2(&invokeDynamicInfo->nameAndTypeIndex);
		return new ConstantInfo{type, (u1 *)invokeDynamicInfo};
	}
	default:
		throw ClassFormatException("Unknown constant type:" + std::to_string(type));
	}
}

JavaClass JavaClassParser::parse() {
	reset();
	JavaClass out;
	readHeader(out);
	readU2(&out._minorVersion);
	readU2(&out._majorVersion);
	readConstantPool(out);
	readClassDescriptors(out);
	readFields(out);
	readMethods(out);
	readAttributes(out);
	return out;
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
		out._fields[i] = *readField();
	}
}

void JavaClassParser::readMethods(JavaClass &out) {
	readU2(&out._methodsCount);
	out.initializeMethods();
	for (u2 i = 0; i < out._methodsCount; i++) {
		out._methods[i] = *readMethod();
	}
}

FieldInfo* JavaClassParser::readField() {
	FieldInfo* field = new FieldInfo();
	readU2(&field->_accessFlags);
	readU2(&field->_nameIndex);
	readU2(&field->_descriptorIndex);
	readU2(&field->_attributesCount);

	field->initializeAttributes();
	for (u2 i = 0; i < field->_attributesCount; i++) {
		field->_attributes[i] = *readAttribute();
	}
	return field;
}

MethodInfo* JavaClassParser::readMethod() {
	MethodInfo* method = new MethodInfo();
	readU2(&method->_accessFlags);
	readU2(&method->_nameIndex);
	readU2(&method->_descriptorIndex);
	readU2(&method->_attributesCount);

	method->initializeAttributes();
	for (u2 i = 0; i < method->_attributesCount; i++) {
		method->_attributes[i] = *readAttribute();
	}
	return method;
}

AttributeInfo* JavaClassParser::readAttribute() {
	u2 attributeNameIndex;
	u4 attributeLength;
	readU2(&attributeNameIndex);
	readU4(&attributeLength);

	char* info = new char[attributeLength];

	read(info, attributeLength);
	return new AttributeInfo{attributeNameIndex, attributeLength, (u1*)info};
}

void JavaClassParser::readAttributes(JavaClass &out) {
	readU2(&out._attributesCount);
	out.initializeAttributes();
	for (u2 i = 0; i < out._attributesCount; i++) {
		out._attributes[i] = *readAttribute();
	}
}
