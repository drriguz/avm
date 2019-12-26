#include "format/java_class.h"

using namespace avm;

JavaClass::JavaClass()
:_magic(0),
 _minorVersion(0),
 _majorVersion(0),
 _constantPoolCount(0),
 _constantPool(nullptr){

}

JavaClass::~JavaClass(){
	if(_constantPool){
		delete[] _constantPool;
		_constantPool = nullptr;
	}
}

void JavaClass::ensureConstantPool() {
	if(_constantPool)
		delete[] _constantPool;
	_constantPool = new ConstantInfo[_constantPoolCount];
}
