#include "class_parser.h"
#include "exceptions.h"
#include "format/class_file.h"

#include <fstream>
#include <iostream>
#include <netinet/in.h>

using namespace avm;

ClassParser::ClassParser(const char* file) {
	in.open(file, std::fstream::in | std::fstream::binary);
	if (!in.is_open())
		throw OpenFileException(file);
}

ClassParser::~ClassParser() {
	if (in.is_open())
		in.close();
}

ClassFile ClassParser::parse() {
	in.clear();
	in.seekg(std::ios::beg);

	ClassFile out;
	readU4(&out.magic);
	readU2(&out.minor_version);
	readU2(&out.major_version);
	readU2(&out.constant_pool_count);
	out.ensureConstantPool();
	readConstants(out.constant_pool_count, out.constant_pool);
	readU2(&out.access_flags);
	readU2(&out.this_class);
	readU2(&out.super_class);
	return out;
}

ConstantInfo* ClassParser::readConstant(const ConstantTypes& type) {
	switch (type) {
	case Class: {
		ConstantClass classInfo;
		readU2(&classInfo.name_index);
		return new ConstantInfo { type, (u1*) &classInfo };
	}
	case Fieldref: {
		ConstantFieldref fieldRefInfo;
		readU2(&fieldRefInfo.class_index);
		readU2(&fieldRefInfo.name_and_type_index);
		return new ConstantInfo { type, (u1*) &fieldRefInfo };
	}
	case Methodref: {
		ConstantMethodref methodRefInfo;
		readU2(&methodRefInfo.class_index);
		readU2(&methodRefInfo.name_and_type_index);
		return new ConstantInfo { type, (u1*) &methodRefInfo };
	}
	case InterfaceMethodref: {
		ConstantInterfaceMethodref interfaceMethodref;
		readU2(&interfaceMethodref.class_index);
		readU2(&interfaceMethodref.name_and_type_index);
		return new ConstantInfo { type, (u1*) &interfaceMethodref };
	}
	case String: {
		ConstantString stringInfo;
		readU2(&stringInfo.string_index);
		return new ConstantInfo { type, (u1*) &stringInfo };
	}
	case Integer: {
		ConstantInteger integerInfo;
		readU4(&integerInfo.bytes);
		return new ConstantInfo { type, (u1*) &integerInfo };
	}
	case Float: {
		ConstantFloat floatInfo;
		readU4(&floatInfo.bytes);
		return new ConstantInfo { type, (u1*) &floatInfo };
	}
	case Long: {
		ConstantLong longInfo;
		readU4(&longInfo.high_bytes);
		readU4(&longInfo.low_bytes);
		return new ConstantInfo { type, (u1*) &longInfo };
	}
	case Double: {
		ConstantDouble doubleInfo;
		readU4(&doubleInfo.high_bytes);
		readU4(&doubleInfo.low_bytes);
		return new ConstantInfo { type, (u1*) &doubleInfo };
	}
	case NameAndType: {
		ConstantNameAndType nameAndTypeInfo;
		readU2(&nameAndTypeInfo.name_index);
		readU2(&nameAndTypeInfo.descriptor_index);
		return new ConstantInfo { type, (u1*) &nameAndTypeInfo };
	}
	case Utf8: {
		ConstantUtf8 utf8Info;
		readU2(&utf8Info.length);
		utf8Info.ensureStringBuffer();
		in.read(reinterpret_cast<char *>(utf8Info.bytes), utf8Info.length);
		return new ConstantInfo { type, (u1*) &utf8Info };
	}
	case MethodHandle: {
		ConstantMethodHandle methodHandleInfo;
		readU1(&methodHandleInfo.reference_kind);
		readU2(&methodHandleInfo.reference_index);
		return new ConstantInfo { type, (u1*) &methodHandleInfo };
	}
	case MethodType: {
		ConstantMethodType methodTypeInfo;
		readU2(&methodTypeInfo.descriptor_index);
		return new ConstantInfo { type, (u1*) &methodTypeInfo };
	}
	case InvokeDynamic: {
		ConstantInvokeDynamic invokeDynamicInfo;
		readU2(&invokeDynamicInfo.bootstrap_method_attr_index);
		readU2(&invokeDynamicInfo.name_and_type_index);
		return new ConstantInfo { type, (u1*) &invokeDynamicInfo };
	}
	default:
		throw ClassFormatException(
				"Unknown constant type" + std::to_string(type));
	}
}

void ClassParser::readConstants(const u2& constant_pool_count,
		ConstantInfo* out) {
	for (u2 i = 1; i < constant_pool_count; i++) {
		u1 tag;
		readU1(&tag);
		const ConstantTypes type = static_cast<ConstantTypes>(tag);
		out[i] = *(readConstant(type));
	}
}
