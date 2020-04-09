#ifndef _AVM_BINARY_READER_H_
#define _AVM_BINARY_READER_H_

#include <fstream>
#include "class_file/format/types.h"

namespace avm {

class BinaryReader {
public:
    explicit BinaryReader(const char *file);
    virtual ~BinaryReader();
public:
    virtual void reset();
	virtual inline void skip(u2 length);
    virtual inline void read(char *buffer, unsigned int length);
    virtual inline void readU1(u1 *buffer);
    virtual inline void readU2(u2 *buffer);
    virtual inline void readU4(u4 *buffer);
protected:
    std::fstream _fileStream;
};
}

#endif
