#include "class_file/format/java_class.h"
#include "class_file/exceptions.h"

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace avm;

JavaClass::JavaClass()
:_magic(0),
 _minorVersion(0),
 _majorVersion(0),
 _constantPool(nullptr),
 _accessFlags(0),
 _thisClass(0),
 _superClass(0),
 _interfacesCount(0),
 _interfaces(nullptr),
 _fieldsCount(0),
 _fields(nullptr),
 _methodsCount(0),
 _methods(nullptr){

}

JavaClass::~JavaClass(){
	clearInterfaces();
	clearFields();
	clearMethods();
	if(_constantPool) {
		delete _constantPool;
		_constantPool = nullptr;
	}
}

void JavaClass::clearInterfaces(){
	if(_interfaces) {
		delete[] _interfaces;
		_interfaces = nullptr;
	}
}

void JavaClass::clearFields(){
	if(_fields) {
		delete[] _fields;
		_fields = nullptr;
	}
}

void JavaClass::clearMethods(){
	if(_methods) {
		delete[] _methods;
		_methods = nullptr;
	}
}

void JavaClass::initializeInterfaces() {
	clearInterfaces();
	if(_interfacesCount>0)
		_interfaces = new u2[_interfacesCount];
}

void JavaClass::initializeFields() {
	clearFields();
	if(_fieldsCount > 0)
		_fields = new FieldInfo[_fieldsCount];
}

void JavaClass::initializeMethods() {
	clearMethods();
	if(_methodsCount > 0)
		_methods = new MethodInfo[_methodsCount];
}

void JavaClass::setConstantPoolReferences() {
	// TODO:
}

const ConstantInfo* JavaClass::getConstantAt(const u2& index) const {
	return _constantPool->at(index);
}

const u2& JavaClass::getInterfaceAt(const u2& index) const {
	if((index < 0) || (index >= _interfacesCount))
		throw new RuntimeException("Index out of bound");
	return _interfaces[index];
}

const FieldInfo* JavaClass::getFieldAt(const u2& index) const {
	if((index < 0) || (index >= _fieldsCount))
		throw new RuntimeException("Index out of bound");
	return &_fields[index];
}

const MethodInfo* JavaClass::getMethodAt(const u2& index) const {
	if((index < 0) || (index >= _methodsCount))
		throw new RuntimeException("Index out of bound");
	return &_methods[index];
}
