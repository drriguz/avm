#ifndef _AVM_CLASS_PARSER_H_
#define _AVM_CLASS_PARSER_H_

#include "format/types.h"
#include <fstream>

namespace avm {
class ClassFile;
class ClassParser {
public:
	ClassFile parse(const char* file);
private:
	inline void readU1(std::fstream& in, u1* out) {
		in.read(reinterpret_cast<char *>(out), sizeof(u1));
	}

	inline void readU2(std::fstream& in, u2* out) {
		in.read(reinterpret_cast<char *>(out), sizeof(u2));
		*out = htons(*out);
	}

	inline void readU4(std::fstream& in, u4* out) {
		in.read(reinterpret_cast<char *>(out), sizeof(u4));
		*out = htonl(*out);
	}
};
}

#endif
