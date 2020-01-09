#ifndef _AVM_CONSTANT_UTF8_H_
#define _AVM_CONSTANT_UTF8_H_

#include <string>

#include "../types.h"

namespace avm {

class ConstantUtf8 {
public:
	ConstantUtf8(const u2& length, const std::string& value);
	ConstantUtf8(const ConstantUtf8& p);
public:
	inline const u2 getLength() const { return _length; }
	inline const u1* const getBytes() const { return (u1*)_value.c_str(); }
	inline const std::string getValue() const { return _value; }
private:
	u2 _length;
	std::string _value;
};
}
#endif
