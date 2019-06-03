#include "class_parser.h"
#include "format/class_file.h"
#include "exceptions.h"

#include <fstream>
#include <iostream>

using namespace avm;


ClassFile ClassParser::parse(const char* file) const{
	std::fstream in;
	in.open(file, std::fstream::in | std::fstream::binary);
	if(!in.is_open())
		throw OpenFileException();

	ClassFile out;
	in >> out.magic;

	std::cout << out.magic;

	in.close();
	return out;
}
