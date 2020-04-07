#ifndef _AVM_CONSTANT_NUMBER_H_
#define _AVM_CONSTANT_NUMBER_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantInteger: public ConstantInfo {
public:
    ConstantInteger(const u4 &bytes);
public:
    inline const u4 getValue() const {
        return _bytes;
    }
private:
    u4 _bytes;
};

class ConstantFloat: public ConstantInfo {
public:
    ConstantFloat(const u4 &bytes);
public:
    inline const float getValue() const {
        return *reinterpret_cast<float*>(&_bytes);
    }
private:
    mutable u4 _bytes;
};

class ConstantLong: public ConstantInfo {
public:
    ConstantLong(const u4 &highBytes, const u4 &lowBytes);
public:
    inline const uint64_t getValue() const {
        return ((uint64_t) _highBytes << 32) + _lowBytes;
    }
private:
    u4 _highBytes;
    u4 _lowBytes;
};

class ConstantDouble: public ConstantInfo {
public:
    /*
     06 | 40 09 21 FB | 4D 12 D8 4A (3.1415926d)
     06 | 40 09 21 FB | 54 44 2D 28 (3.1415926535898d)
     highBytes = 0x400921FB = 1074340347 = 01000000000010010010000111111011
     lowBytes  = 0x54442d28 = 1413754152 = 01010100010001000010110100101000
     value     = ((long)0x400921FB << 32) + 0x54442d28
     = 0x400921FB54442D28
     = 4614256656552045864
     = 0100000000001001001000011111101101010100010001000010110100101000
     */
    ConstantDouble(const u4 &highBytes, const u4 &lowBytes);
public:
    inline const double getValue() const {
        uint64_t value = ((uint64_t) _highBytes << 32) + _lowBytes;
        return *reinterpret_cast<double*>(&value);
    }
private:
    mutable u4 _highBytes;
    mutable u4 _lowBytes;
};

}
#endif
