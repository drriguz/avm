#ifndef _AVM_JAVA_CLASS_PARSER_H_
#define _AVM_JAVA_CLASS_PARSER_H_

#include "class_file/format/types.h"
#include "class_file/format/java_class.h"
#include "class_file/format/field_info.h"
#include "class_file/format/method_info.h"
#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class JavaClassParser {
public:
	JavaClassParser();
	virtual ~JavaClassParser();
public:
	virtual void parse(JavaClass& out);
private:
	void readHeader(JavaClass &out);
	void readConstantPool(JavaClass &out);
	void readClassDescriptors(JavaClass &out);
	void readFields(JavaClass &out);
	ConstantInfo* readConstant(const ConstantType & type);
	void readField(FieldInfo &to);
	void readAttribute(AttributeInfo& to);
	void readMethods(JavaClass &out);
	void readMethod(MethodInfo& to);
	void readAttributes(JavaClass &out);
protected:
	virtual void reset()=0;
	virtual void read(char* buffer, unsigned int length)=0;
	virtual void readU1(u1* buffer)=0;
	virtual void readU2(u2* buffer)=0;
	virtual void readU4(u4* buffer)=0;
protected:
	inline u1 readU1() {
		u1 tmp;
		readU1(&tmp);
		return tmp;
	}
	inline u2 readU2() {
		u2 tmp;
		readU2(&tmp);
		return tmp;
	}
	inline u4 readU4() {
		u4 tmp;
		readU4(&tmp);
		return tmp;
	}
};
}

#endif
