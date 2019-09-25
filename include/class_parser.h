#ifndef _AVM_CLASS_PARSER_H_
#define _AVM_CLASS_PARSER_H_

#include "format/types.h"
#include "format/constants.h"
#include "format/class_file.h"
#include "format/field_info.h"
#include "exceptions.h"

#include <fstream>

namespace avm {

class ClassParser {
public:
	ClassParser(const char* file);
	virtual ~ClassParser();
public:
	ClassFile* parse();
private:
	ConstantInfo* readConstant(const ConstantTypes& type);
	void readInterfaces(const u2& interfaces_count, u2* out);
	void readConstants(const u2& constant_pool_count, ConstantInfo* out);
	void readFields(const u2& fields_count, FieldInfo* out);
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
