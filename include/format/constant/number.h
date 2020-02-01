#ifndef _AVM_CONSTANT_NUMBER_H_
#define _AVM_CONSTANT_NUMBER_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantInteger: public ConstantInfo {
public:
	ConstantInteger(const u4& bytes);
public:
	inline const u4 getValue() const { return _bytes; }
private:
    u4 _bytes;
};

class ConstantFloat: public ConstantInfo {
public:
	ConstantFloat(const u4& bytes);
public:
	inline const float getValue() const { return *reinterpret_cast<float*>(&_bytes); }
private:
	mutable u4 _bytes;
};

class ConstantLong: public ConstantInfo {
public:
	ConstantLong(const u4& highBytes, const u4& lowBytes);
public:
	inline const float getValue() const { return ((long)_highBytes << 32) + _lowBytes; }
private:
    u4 _highBytes;
    u4 _lowBytes;
};

class ConstantDouble: public ConstantInfo {
public:
	ConstantDouble(const u4& highBytes, const u4& lowBytes);
public:
	inline const double getValue() const {
		long value = ((long)_highBytes << 32) + _lowBytes;
		return *reinterpret_cast<double*>(&value);
	}
private:
	mutable u4 _highBytes;
	mutable u4 _lowBytes;
};

}
#endif
