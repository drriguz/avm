#ifndef _AVM_FRAME_H_
#define _AVM_FRAME_H_

#include "operand_stack.h"

namespace avm{

	class Frame {
	public:
		Frame();
		virtual ~Frame();
	protected:
		OperandStack* _operandStack;
	};
}
#endif