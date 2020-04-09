#ifndef _AVM_BINARY_READER_H_
#define _AVM_BINARY_READER_H_

#include "class_file/format/types.h"

namespace avm {

class BinaryReader {
public:
	virtual void reset()=0;
	virtual inline void skip(u2 length)=0;
	virtual inline void read(char *buffer, unsigned int length)=0;
	virtual inline void readU1(u1 *buffer)=0;
	virtual inline void readU2(u2 *buffer)=0;
	virtual inline void readU4(u4 *buffer)=0;
public:
	inline u1 readU1() {
        u1 tmp;
        readU1(&tmp);
        return tmp;
    }
    inline u2 readU2() {
        u2 tmp;
        readU2(&tmp);
        return tmp;
    }
    inline u4 readU4() {
        u4 tmp;
        readU4(&tmp);
        return tmp;
    }
};
}

#endif
