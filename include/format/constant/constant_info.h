#ifndef _AVM_CONSTANT_INFO_H_
#define _AVM_CONSTANT_INFO_H_

#include <string>

#include "../types.h"
#include "constant_types.h"

namespace avm {

class ConstantInfo {
public:
	ConstantInfo(const ConstantType& type);
	virtual ~ConstantInfo();
public:
	inline const ConstantType getType() const { return _type; }
protected:
	const ConstantType _type;
};

}
#endif
