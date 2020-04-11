#ifndef _AVM_EXCEPTIONS_ATTRIBUTE_H_
#define _AVM_EXCEPTIONS_ATTRIBUTE_H_

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
        return _exceptionsCount;
    }
    inline u2 getIndex(u2 i) const  {
        if(i < 0 || i > _exceptionsCount)
            throw AttributeNotFoundException("Exception index out of range");
        return _indexes[i];
    }
protected:
    u2 _exceptionsCount;
    u2* _indexes; 
};

}

#endif
