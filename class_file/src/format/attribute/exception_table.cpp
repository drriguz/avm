#include "class_file/format/attribute/exception_table.h"

using namespace avm;

ExceptionTable::ExceptionTable(const u2& startPc, const u2& endPc, const u2& handlerPc, const u2& catchType):
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