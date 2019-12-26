#include "parser/class_file_parser.h"
#include "exceptions.h"

#include <iostream>

using namespace avm;

ClassFileParser::ClassFileParser(const char* file){
	_fileStream.open(file, std::fstream::in | std::fstream::binary);

	if(!_fileStream.is_open())
		throw FileOpenFailedException(file);

}
ClassFileParser::~ClassFileParser(){
	if(_fileStream.is_open())
		_fileStream.close();
}

void ClassFileParser::reset() {
	_fileStream.clear();
	_fileStream.seekg(0, std::ios::beg);
}

void ClassFileParser::readU1(u1* buffer) {
	if (!_fileStream.read(reinterpret_cast<char *>(buffer), sizeof(u1)))
		throw ReadFileException("Could not read u1");
}

void ClassFileParser::readU2(u2* buffer) {
	if (!_fileStream.read(reinterpret_cast<char *>(buffer), sizeof(u2)))
		throw ReadFileException("Could not read u2");
	*buffer = htons(*buffer);
}

void ClassFileParser::readU4(u4* buffer) {
	if (!_fileStream.read(reinterpret_cast<char *>(buffer), sizeof(u4)))
		throw ReadFileException("Could not read u4");
	*buffer = htonl(*buffer);
}

