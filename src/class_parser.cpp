#include "class_parser.h"
#include "exceptions.h"
#include "format/class_file.h"

#include "spdlog/spdlog.h"

#include <fstream>
#include <iostream>
#include <netinet/in.h>

using namespace avm;

ClassParser::ClassParser(const char *file) {
	in.open(file, std::fstream::in | std::fstream::binary);
	if (!in.is_open())
		throw OpenFileException(file);
}

ClassParser::~ClassParser() {
	if (in.is_open())
		in.close();
}

ClassFile* ClassParser::parse() {
	in.clear();
	in.seekg(std::ios::beg);
	
	ClassFile* out = new ClassFile();
	readU4(&out->magic);
	readU2(&out->minor_version);
	readU2(&out->major_version);
	readU2(&out->constant_pool_count);
	spdlog::debug("Parsing constant pool:size={}", out->constant_pool_count);
	out->ensureConstantPool();
	
	readConstants(out->constant_pool_count, out->constant_pool);
	readU2(&out->access_flags);
	readU2(&out->this_class);
	readU2(&out->super_class);
	readU2(&out->interfaces_count);
	
	out->ensureInterfaces();
	readInterfaces(out->interfaces_count, out->interfaces);
	readU2(&out->fields_count);
	
	out->ensureFields();	
	readFields(out->fields_count, out->fields);
	return out;
}

ConstantInfo *ClassParser::readConstant(const ConstantTypes &type) {
	switch (type) {
	case Class: {
		ConstantClass *classInfo = new ConstantClass();
		readU2(&classInfo->name_index);
		spdlog::debug("readed class:{}", classInfo->name_index);
		return new ConstantInfo{type, (u1 *)classInfo};
	}
	case Fieldref: {
		ConstantFieldref *fieldRefInfo = new ConstantFieldref();
		readU2(&fieldRefInfo->class_index);
		readU2(&fieldRefInfo->name_and_type_index);
		return new ConstantInfo{type, (u1 *)fieldRefInfo};
	}
	case Methodref: {
		ConstantMethodref *methodRefInfo = new ConstantMethodref();
		readU2(&methodRefInfo->class_index);
		readU2(&methodRefInfo->name_and_type_index);
		return new ConstantInfo{type, (u1 *)methodRefInfo};
	}
	case InterfaceMethodref: {
		ConstantInterfaceMethodref *interfaceMethodref =
		    new ConstantInterfaceMethodref();
		readU2(&interfaceMethodref->class_index);
		readU2(&interfaceMethodref->name_and_type_index);
		return new ConstantInfo{type, (u1 *)interfaceMethodref};
	}
	case String: {
		ConstantString *stringInfo = new ConstantString();
		readU2(&stringInfo->string_index);
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
		readU4(&longInfo->high_bytes);
		readU4(&longInfo->low_bytes);
		return new ConstantInfo{type, (u1 *)longInfo};
	}
	case Double: {
		ConstantDouble *doubleInfo = new ConstantDouble();
		readU4(&doubleInfo->high_bytes);
		readU4(&doubleInfo->low_bytes);
		return new ConstantInfo{type, (u1 *)doubleInfo};
	}
	case NameAndType: {
		ConstantNameAndType *nameAndTypeInfo = new ConstantNameAndType();
		readU2(&nameAndTypeInfo->name_index);
		readU2(&nameAndTypeInfo->descriptor_index);
		return new ConstantInfo{type, (u1 *)nameAndTypeInfo};
	}
	case Utf8: {
		ConstantUtf8 *utf8Info = new ConstantUtf8();
		readU2(&utf8Info->length);
		utf8Info->ensureStringBuffer();
		in.read(reinterpret_cast<char *>(utf8Info->bytes), utf8Info->length);
		utf8Info->bytes[utf8Info->length] = '\0';
		spdlog::debug("Readed utf8:length={} [{}]", utf8Info->length,
			      utf8Info->bytes);
		return new ConstantInfo{type, (u1 *)utf8Info};
	}
	case MethodHandle: {
		ConstantMethodHandle *methodHandleInfo = new ConstantMethodHandle();
		readU1(&methodHandleInfo->reference_kind);
		readU2(&methodHandleInfo->reference_index);
		return new ConstantInfo{type, (u1 *)methodHandleInfo};
	}
	case MethodType: {
		ConstantMethodType *methodTypeInfo = new ConstantMethodType;
		readU2(&methodTypeInfo->descriptor_index);
		return new ConstantInfo{type, (u1 *)methodTypeInfo};
	}
	case InvokeDynamic: {
		ConstantInvokeDynamic *invokeDynamicInfo = new ConstantInvokeDynamic();
		readU2(&invokeDynamicInfo->bootstrap_method_attr_index);
		readU2(&invokeDynamicInfo->name_and_type_index);
		return new ConstantInfo{type, (u1 *)invokeDynamicInfo};
	}
	default:
		throw ClassFormatException(
		    "Unknown constant type:" + std::to_string(type));
	}
}

void ClassParser::readConstants(const u2 &constant_pool_count,
				ConstantInfo *out) {
	for (u2 i = 1; i < constant_pool_count; i++) {
		u1 tag;
		readU1(&tag);
		const ConstantTypes type = static_cast<ConstantTypes>(tag);
		spdlog::debug("Parsing constant:#{}/{}", i, type);
		out[i] = *(readConstant(type));
		if (type == Long || type == Double)
			i++;
	}
}

void ClassParser::readInterfaces(const u2 &interfaces_count, u2 *out) {
	for (int i = 0; i < interfaces_count; i++)
		readU2(out);
}

void ClassParser::readFields(const u2 &fields_count, FieldInfo *out) {
	readU2(&out->access_flags);
	readU2(&out->name_index);
	readU2(&out->descriptor_index);
	readU2(&out->attributes_count);

	out->ensureAttributes();
	for (int i = 0; i < out->attributes_count; i++) {
		AttributeInfo *attribute = new AttributeInfo();
		readU2(&attribute->attribute_name_index);
		readU2(&attribute->attribute_length);
	}
}
