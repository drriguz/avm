#ifndef _AVM_CLASS_FILE_EXCEPTIONS_H_
#define _AVM_CLASS_FILE_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace avm {
class RuntimeException: public std::exception {
public:
    RuntimeException(const std::string &msg) :
        message(msg) {
    }
    const virtual char* what() const throw () {
        return message.c_str();
    }

private:
    std::string message;
};

class FileOpenFailedException: public RuntimeException {
public:
    FileOpenFailedException(const std::string &msg) :
        RuntimeException(std::string("File open failed:") + msg) {
    }
};

class ReadFileException: public RuntimeException {
public:
    ReadFileException(const std::string &msg) :
        RuntimeException(std::string("Read file failed:") + msg) {
    }
};

class NotClassFileException: public RuntimeException {
public:
    NotClassFileException(const std::string &msg) :
        RuntimeException(std::string("Not a class file:") + msg) {
    }
};

class ClassFormatException: public RuntimeException {
public:
    ClassFormatException(const std::string &msg) :
        RuntimeException(std::string("Class format error:") + msg) {
    }
};

class MethodNotFoundException: public RuntimeException {
public:
    MethodNotFoundException(const std::string &msg) :
        RuntimeException(std::string("Method not found:") + msg) {
    }
};

class AttributeNotFoundException: public RuntimeException {
public:
    AttributeNotFoundException(const std::string &msg) :
        RuntimeException(std::string("Attribute not found:") + msg) {
    }
};
}

#endif
