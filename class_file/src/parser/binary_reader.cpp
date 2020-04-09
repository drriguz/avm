#include "class_file/parser/binary_reader.h"
#include "class_file/exceptions.h"

#include <iostream>

#ifdef _WIN32
    #include <winsock.h>
#elif  __linux__
    #include <arpa/inet.h>
#endif

using namespace avm;

BinaryReader::BinaryReader(const char *file) {
    _fileStream.open(file, std::fstream::in | std::fstream::binary);

    if (!_fileStream.is_open())
        throw FileOpenFailedException("Could not open:" + std::string(file));

}
BinaryReader::~BinaryReader() {
    if (_fileStream.is_open())
        _fileStream.close();
}

void BinaryReader::reset() {
    _fileStream.clear();
    _fileStream.seekg(0, std::ios::beg);
}

void BinaryReader::skip(u2 length) {
	if (!_fileStream.ignore(length))
        throw ReadFileException("Could not read from file");
}

void BinaryReader::read(char *buffer, unsigned int length) {
    if (!_fileStream.read(buffer, length))
        throw ReadFileException("Could not read from file");
}

void BinaryReader::readU1(u1 *buffer) {
    if (!_fileStream.read(reinterpret_cast<char*>(buffer), sizeof(u1)))
        throw ReadFileException("Could not read u1");
}

void BinaryReader::readU2(u2 *buffer) {
    if (!_fileStream.read(reinterpret_cast<char*>(buffer), sizeof(u2)))
        throw ReadFileException("Could not read u2");
    *buffer = htons(*buffer);
}

void BinaryReader::readU4(u4 *buffer) {
    if (!_fileStream.read(reinterpret_cast<char*>(buffer), sizeof(u4)))
        throw ReadFileException("Could not read u4");
    *buffer = htonl(*buffer);
}

