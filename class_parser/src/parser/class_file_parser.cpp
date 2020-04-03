#include "parser/class_file_parser.h"
#include "exceptions.h"

#include <iostream>

#ifdef _WIN32
#include <winsock.h>
#endif

using namespace avm;

ClassFileParser::ClassFileParser(const char* file)
:_reader(file){
	
}

ClassFileParser::~ClassFileParser(){
}

void ClassFileParser::reset() {
	_reader.reset();
}

void ClassFileParser::read(char* buffer, unsigned int length){
	_reader.read(buffer, length);
}

void ClassFileParser::readU1(u1* buffer) {
	_reader.readU1(buffer);
}

void ClassFileParser::readU2(u2* buffer) {
	_reader.readU2(buffer);
}

void ClassFileParser::readU4(u4* buffer) {
	_reader.readU4(buffer);
}

