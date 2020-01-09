#include "format/constant/utf8.h"

#include <iostream>

using namespace avm;

ConstantUtf8::ConstantUtf8(const u2& length, const std::string& value)
: _length(length),
  _value(value){

}

ConstantUtf8::ConstantUtf8(const ConstantUtf8& p){
	_length = p._length;
	_value = p._value;
}
