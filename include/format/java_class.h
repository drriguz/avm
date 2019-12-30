#ifndef _AVM_JAVA_CLASS_H_
#define _AVM_JAVA_CLASS_H_

#include "types.h"
#include "constant_pool.h"
#include "access_flags.h"

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
	const ConstantInfo* getConstantAt(const u2& index) const;
	inline const u2& getAccessFlags() const { return _accessFlags; }
	inline const u2& getThisClass() const { return _thisClass; }
	inline const u2& getSuperClass() const { return _superClass; }
	inline const u2& getInterfacesCount() const { return _interfacesCount; }
	const u2& getInterfaceAt(const u2& index) const;
public:
	inline bool isPublic() const { return _accessFlags & ACC_PUBLIC; }
	inline bool isFinal() const { return _accessFlags & ACC_FINAL; }
	inline bool isSuper() const { return _accessFlags & ACC_SUPER; }
	inline bool isInterface() const { return _accessFlags & ACC_INTERFACE; }
	inline bool isAbstract() const { return _accessFlags & ACC_ABSTRACT; }
	inline bool isSynthetic() const { return _accessFlags & ACC_SYNTHETIC; }
	inline bool isAnnotation() const { return _accessFlags & ACC_ANNOTATION; }
	inline bool isEnum() const { return _accessFlags & ACC_ENUM; }
private:
	void initializeConstantPool();
	void initializeInterfaces();
private:
	u4 _magic;
	u2 _minorVersion;
	u2 _majorVersion;
	u2 _constantPoolCount;
	ConstantInfo* _constantPool;
	u2 _accessFlags;
	u2 _thisClass;
	u2 _superClass;
	u2 _interfacesCount;
	u2 *_interfaces;
};
}

#endif
