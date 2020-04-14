#ifndef _AVM_EXCEPTIONS_ATTRIBUTE_H_
#define _AVM_EXCEPTIONS_ATTRIBUTE_H_

#include <string>
#include <vector>

#include "class_file/format/attribute/attribute_info.h"
#include "class_file/exceptions.h"

namespace avm {

class Exceptions: public AttributeInfo {
    friend class JavaClassParser;
public:
    Exceptions();
    virtual ~Exceptions();
public:
    inline u2 getExceptionsCount() const {
        return _exceptionClasses.size();
    }
    inline std::string getExceptionClass(u2 index) const {
        return _exceptionClasses.at(index);
    }
protected:
    std::vector<std::string> _exceptionClasses;
};

}

#endif
