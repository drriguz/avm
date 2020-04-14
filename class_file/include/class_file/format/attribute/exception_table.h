#ifndef _AVM_EXCEPTION_TABLE_H_
#define _AVM_EXCEPTION_TABLE_H_

#include "class_file/format/types.h"

namespace avm {
class ExceptionTable {
public:
    ExceptionTable(u2  startPc, u2  endPc, u2  handlerPc, u2  catchType);
    ExceptionTable(const ExceptionTable& p);
    virtual ~ExceptionTable();
protected:
    const u2 _startPc;
    const u2 _endPc;
    const u2 _handlerPc;
    const u2 _catchType;
};
}

#endif