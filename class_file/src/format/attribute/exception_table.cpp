#include "class_file/format/attribute/exception_table.h"

using namespace avm;

ExceptionTable::ExceptionTable(u2  startPc, u2  endPc, u2  handlerPc, u2  catchType):
    _startPc(startPc),
    _endPc(endPc),
    _handlerPc(handlerPc),
    _catchType(catchType) {

}

ExceptionTable::ExceptionTable(const ExceptionTable& p):
    _startPc(p._startPc),
    _endPc(p._endPc),
    _handlerPc(p._handlerPc),
    _catchType(p._catchType) {

}

ExceptionTable::~ ExceptionTable() {

}