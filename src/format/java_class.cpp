#include "format/java_class.h"
#include "exceptions.h"

using namespace avm;

JavaClass::JavaClass()
:_magic(0),
 _minorVersion(0),
 _majorVersion(0),
 _constantPoolCount(0),
 _constantPool(nullptr),
 _accessFlags(0),
 _thisClass(0),
 _superClass(0),
 _interfacesCount(0),
 _interfaces(nullptr){

}

JavaClass::~JavaClass(){
	if(_constantPool){
		delete[] _constantPool;
		_constantPool = nullptr;
	}
	if(_interfaces) {
		delete[] _interfaces;
		_interfaces = nullptr;
	}
}

void JavaClass::initializeConstantPool() {
	if(_constantPool)
		delete[] _constantPool;
	_constantPool = new ConstantInfo[_constantPoolCount];
}

void JavaClass::initializeInterfaces() {
	if(_interfaces)
		delete[] _interfaces;
	_interfaces = new u2[_interfacesCount];
}

const ConstantInfo* JavaClass::getConstantAt(const u2& index) const {
	if((index < 0) || (index >= _constantPoolCount))
		throw new RuntimeException("Index out of bound");
	return &_constantPool[index];
}

const u2& JavaClass::getInterfaceAt(const u2& index) const {
	if((index < 0) || (index >= _interfacesCount))
		throw new RuntimeException("Index out of bound");
	return _interfaces[index];
}
