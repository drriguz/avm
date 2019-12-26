#ifndef _AVM_JAVA_CLASS_H_
#define _AVM_JAVA_CLASS_H_

#include "types.h"
#include "constant_pool.h"

namespace avm {
class JavaClassParser;

class JavaClass {
	friend class JavaClassParser;
public:
	JavaClass();
	virtual ~JavaClass();
public:
	inline const u4& getMagic() const {return _magic; }
	inline const u2& getMinorVersion() const { return _minorVersion; }
	inline const u2& getMajorVersion() const { return _majorVersion; }
	inline const u2& getConstantPoolCount() const { return _constantPoolCount; }
private:
	void ensureConstantPool();
private:
	u4 _magic;
	u2 _minorVersion;
	u2 _majorVersion;
	u2 _constantPoolCount;
	ConstantInfo* _constantPool;
};
}

#endif
