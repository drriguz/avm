#ifndef _AVM_JAVA_CLASS_PARSER_H_
#define _AVM_JAVA_CLASS_PARSER_H_

#include "format/types.h"
#include "format/java_class.h"
#include "format/constant_pool.h"
#include "format/field_info.h"
#include "format/method_info.h"
#include "format/attribute_info.h"

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
	void readClassDescriptors(JavaClass &out);
	void readFields(JavaClass &out);
	ConstantInfo* readConstant(const ConstantType & type);
	FieldInfo* readField();
	AttributeInfo* readAttribute();
	void readMethods(JavaClass &out);
	MethodInfo* readMethod();
protected:
	virtual void reset()=0;
	virtual void read(char* buffer, unsigned int length)=0;
	virtual void readU1(u1* buffer)=0;
	virtual void readU2(u2* buffer)=0;
	virtual void readU4(u4* buffer)=0;
};
}

#endif
