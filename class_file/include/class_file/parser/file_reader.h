#ifndef _AVM_BINARY_FILE_READER_H_
#define _AVM_BINARY_FILE_READER_H_

#include "class_file/format/java_class.h"
#include "binary_reader.h"
#include "java_class_parser.h"

#include <fstream>

namespace avm {

class BinaryFileReader: public BinaryReader {
public:
    explicit BinaryFileReader(const char *file);
    virtual ~BinaryFileReader();
public:
    virtual void skip(u2 length);
    virtual void reset();
    virtual inline void read(char *buffer, unsigned int length);
    virtual inline void readU1(u1 *buffer);
    virtual inline void readU2(u2 *buffer);
    virtual inline void readU4(u4 *buffer);
protected:
    std::fstream _fileStream;
};
}

#endif
