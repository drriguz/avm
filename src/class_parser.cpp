#include "class_parser.h"
#include "format/class_file.h"
#include "exceptions.h"

#include <fstream>
#include <iostream>
#include <netinet/in.h>

using namespace avm;

ClassFile ClassParser::parse(const char* file) {
	std::fstream in;
	in.open(file, std::fstream::in | std::fstream::binary);
	if (!in.is_open())
		throw OpenFileException();

	ClassFile out;
	readU4(in, &out.magic);
	readU2(in, &out.minor_version);
	readU2(in, &out.major_version);
	readU2(in, &out.constant_pool_count);
	in.close();
	return out;
}
