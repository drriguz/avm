#ifndef _AVM_VM_EXCEPTIONS_H_
#define _AVM_VM_EXCEPTIONS_H_

#include <exception>
#include <string>

#include "class_file/exceptions.h"

namespace avm {

class ClassNotFoundException: public RuntimeException {
public:
    ClassNotFoundException(const std::string &msg) :
        RuntimeException(std::string("Class not found:") + msg) {
    }
};

class ClassAlreadyLoadedException: public RuntimeException {
public:
    ClassAlreadyLoadedException(const std::string &msg) :
        RuntimeException(std::string("Class already loaded:") + msg) {
    }
};

class StackOutOfRangeException: public RuntimeException {
public:
    StackOutOfRangeException(const std::string &msg) :
        RuntimeException(std::string("Stack out of range:") + msg) {
    }
};

class LocalVariablesOutOfRangeException: public RuntimeException {
public:
    LocalVariablesOutOfRangeException(const std::string &msg) :
        RuntimeException(std::string("Local variables out of range:") + msg) {
    }
};

class UnsupportedInstructionException: public RuntimeException {
public:
    UnsupportedInstructionException(const std::string &msg) :
        RuntimeException(std::string("Unsupported instruction:") + msg) {
    }
};

class FieldValueTypeNotMatchException: public RuntimeException {
public:
    FieldValueTypeNotMatchException(const std::string &msg) :
        RuntimeException(std::string("Set wrong type of value to field:") + msg) {
    }
};
}

#endif
