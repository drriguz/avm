#ifndef _AVM_CLASS_PARSER_H_
#define _AVM_CLASS_PARSER_H_

#include "format/types.h"
#include "exceptions.h"
#include <fstream>

namespace avm {
class ClassFile;
class ClassParser {
public:
	ClassParser(const char* file);
	virtual ~ClassParser();
public:
	ClassFile parse();
private:
	void readConstants(const u2& constant_pool_count);
private:
	inline void readU1(u1* out) {
		if (!in.read(reinterpret_cast<char *>(out), sizeof(u1)))
			throw ReadFileException("Could not read u1");
	}

	inline void readU2(u2* out) {
		if (!in.read(reinterpret_cast<char *>(out), sizeof(u2)))
			throw ReadFileException("Could not read u2");
		*out = htons(*out);
	}

	inline void readU4(u4* out) {
		if (!in.read(reinterpret_cast<char *>(out), sizeof(u4)))
			throw ReadFileException("Could not read u4");
		*out = htonl(*out);
	}
private:
	std::fstream in;
};
}

#endif
