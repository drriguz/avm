#ifndef _AVM_CONSTANT_UTF8_H_
#define _AVM_CONSTANT_UTF8_H_

#include <string>

#include "../types.h"
#include "constant_info.h"

namespace avm {

class ConstantUtf8: public ConstantInfo {
public:
    ConstantUtf8(const u2 length, const std::string &value);
    ConstantUtf8(const ConstantUtf8 &p);
public:
    inline u2 getLength() const {
        return _length;
    }
    inline u1* const getBytes() const {
        return (u1*) _value.c_str();
    }
    inline std::string getValue() const {
        return _value;
    }
private:
    u2 _length;
    std::string _value;
};
}
#endif
