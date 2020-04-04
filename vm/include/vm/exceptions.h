#ifndef _AVM_VM_EXCEPTIONS_H_
#define _AVM_VM_EXCEPTIONS_H_

#include <exception>
#include <string>

#include "class_file/exceptions.h"

namespace avm {

class ClassNotFoundException : public RuntimeException {
public:
	ClassNotFoundException(const std::string &msg) : RuntimeException(msg) {
	}
};

class ClassAlreadyLoadedException : public RuntimeException {
public:
	ClassAlreadyLoadedException(const std::string &msg) : RuntimeException(msg) {
	}
};
}

#endif
