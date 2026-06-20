#ifndef _AVM_OBJECT_H_
#define _AVM_OBJECT_H_

#include <map>
#include <string>
#include <cstdint>
#include <cstring>

#include "vm_class.h"
#include "vm_field.h"
#include "vm/util/numbers.h"

typedef uint64_t OBJECT_UNIT;

namespace avm {

class Object {
public:
    Object(OBJECT_UNIT* data, int size): _data(data), _size(size) {}
    Object(const Object& p): _data(p._data), _size(p._size) {}
    virtual ~Object() {}

    inline bool isValid() const { return _data != nullptr; }
    inline OBJECT_UNIT* getData() const { return _data; }

    // Field access at OBJECT_UNIT offset (each unit = 8 bytes)
    inline void setIntAt(int offset, int32_t value) {
        uint32_t *uv = reinterpret_cast<uint32_t*>(&value);
        _data[offset] = *uv;
    }
    inline int32_t getIntAt(int offset) const {
        uint32_t val = (uint32_t)_data[offset];
        return *reinterpret_cast<int32_t*>(&val);
    }
    inline void setLongAt(int offset, int64_t value) {
        uint32_t highBytes, lowBytes;
        std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
        _data[offset] = highBytes;
        _data[offset + 1] = lowBytes;
    }
    inline int64_t getLongAt(int offset) const {
        uint32_t highBytes = (uint32_t)_data[offset];
        uint32_t lowBytes = (uint32_t)_data[offset + 1];
        return Numbers::asLong(highBytes, lowBytes);
    }
    inline void setFloatAt(int offset, float value) {
        int32_t *sv = reinterpret_cast<int32_t*>(&value);
        _data[offset] = *sv;
    }
    inline float getFloatAt(int offset) const {
        int32_t val = (int32_t)_data[offset];
        return *reinterpret_cast<float*>(&val);
    }
    inline void setDoubleAt(int offset, double value) {
        int64_t *sv = reinterpret_cast<int64_t*>(&value);
        uint32_t highBytes, lowBytes;
        std::tie(highBytes, lowBytes) = Numbers::splitLong(*sv);
        _data[offset] = highBytes;
        _data[offset + 1] = lowBytes;
    }
    inline double getDoubleAt(int offset) const {
        uint32_t highBytes = (uint32_t)_data[offset];
        uint32_t lowBytes = (uint32_t)_data[offset + 1];
        int64_t val = Numbers::asLong(highBytes, lowBytes);
        return *reinterpret_cast<double*>(&val);
    }
    inline void setReferenceAt(int offset, reference value) {
#ifdef _ARCH_X64_
        setLongAt(offset, value);
#else
        setIntAt(offset, value);
#endif
    }
    inline reference getReferenceAt(int offset) const {
#ifdef _ARCH_X64_
        return getLongAt(offset);
#else
        return getIntAt(offset);
#endif
    }
protected:
    OBJECT_UNIT* _data;
    int _size;
};
}
#endif
