#ifndef _AVM_JAVA_CLASS_PARSER_H_
#define _AVM_JAVA_CLASS_PARSER_H_

#include "format/types.h"
#include "format/java_class.h"

namespace avm {

class JavaClassParser {
public:
	JavaClassParser();
	virtual ~JavaClassParser();
public:
	virtual JavaClass parse();
private:
	void readHeader(JavaClass &out);
	void readConstantPool(JavaClass &out);
	ConstantInfo* readConstant(const ConstantType & type);
protected:
	virtual void reset()=0;
	virtual void readU1(u1* buffer)=0;
	virtual void readU2(u2* buffer)=0;
	virtual void readU4(u4* buffer)=0;
};
}

#endif
