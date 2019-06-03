#ifndef _AVM_CLASS_PARSER_H_
#define _AVM_CLASS_PARSER_H_

#include "format/types.h"
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
	void readConstants(std::fstream& in);
private:
	inline void readU1(u1* out) {
		in.read(reinterpret_cast<char *>(out), sizeof(u1));
	}

	inline void readU2(u2* out) {
		in.read(reinterpret_cast<char *>(out), sizeof(u2));
		*out = htons(*out);
	}

	inline void readU4(u4* out) {
		in.read(reinterpret_cast<char *>(out), sizeof(u4));
		*out = htonl(*out);
	}
private:
	std::fstream in;
};
}

#endif
