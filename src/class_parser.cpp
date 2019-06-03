#include "class_parser.h"
#include "exceptions.h"
#include "format/class_file.h"
#include "format/constants.h"

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

	readConstants(out.constant_pool_count);
	return out;
}

void ClassParser::readConstants(const u2& constant_pool_count) {
	for (u2 i = 1; i < constant_pool_count; i++) {
		u1 tag;
		readU1(&tag);
		const ConstantTypes type = static_cast<ConstantTypes>(tag);
		switch (type) {
		case Class:
		case Fieldref:
		case Methodref:
		case InterfaceMethodref:
		case String:
		case Integer:
		case Float:
		case Long:
		case Double:
		case NameAndType:
		case Utf8:
		case MethodHandle:
		case MethodType:
		case InvokeDynamic:
		default:
			throw ClassFormatException(
					"Unknown constant type:" + std::to_string(type));
		}
	}
}
