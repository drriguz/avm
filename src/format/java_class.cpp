#include "format/java_class.h"
#include "exceptions.h"

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

void JavaClass::initializeConstantPool() {
	if(_constantPool)
		delete[] _constantPool;
	_constantPool = new ConstantInfo[_constantPoolCount];
}

const ConstantInfo* JavaClass::getConstantAt(u2 index) const {
	if((index < 0) || (index >= _constantPoolCount))
			throw new RuntimeException("Index out of bound");
	return &_constantPool[index];
}
