#ifndef _AVM_EXCEPTION_TABLE_H_
#define _AVM_EXCEPTION_TABLE_H_

#include "types.h"

namespace avm {

struct ExceptionTable {
	u2 startPc;
	u2 endPc;
	u2 handlerPc;
	u2 catchType;
};
}

#endif
