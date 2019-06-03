#include "class_parser.h"
#include "format/class_file.h"
#include "exceptions.h"

#include <fstream>
#include <iostream>
#include <netinet/in.h>

using namespace avm;

ClassParser::ClassParser(const char* file) {
	in.open(file, std::fstream::in | std::fstream::binary);
	if (!in.is_open())
		throw OpenFileException();
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

	return out;
}

void ClassParser::readConstants(std::fstream& in) {

}
