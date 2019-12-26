#ifndef _AVM_CLASS_FILE_PARSER_H_
#define _AVM_CLASS_FILE_PARSER_H_

#include "format/java_class.h"
#include "java_class_parser.h"

#include <fstream>

namespace avm {

class ClassFileParser :public JavaClassParser{
public:
	explicit ClassFileParser(const char* file);
	virtual ~ClassFileParser();
public:
	virtual void reset();
	virtual inline void readU1(u1* buffer);
	virtual inline void readU2(u2* buffer);
	virtual inline void readU4(u4* buffer);
protected:
	std::fstream _fileStream;
};
}

#endif
