#ifndef _AVM_CONSTANT_INFO_H_
#define _AVM_CONSTANT_INFO_H_

#include <string>

#include "../types.h"
#include "constant_types.h"

namespace avm {

class Constant {
public:
	Constant(const ConstantType& type);
	virtual ~Constant();
public:
	inline const ConstantType getType() const { return _type; }
protected:
	const ConstantType _type;
};

class ConstantInfo {
public:
	ConstantInfo();
	ConstantInfo(const ConstantType& type, const u1* info, const u2& size);
	ConstantInfo(const ConstantInfo& p);
	virtual ~ConstantInfo();
public:
	void initialize(const u1* info, u2 size);
public:
	inline const u2 getSize() const { return _size; }
	inline const u1* const getInfo() const { return _info; }
private:
	void clear();
private:
	ConstantType _type;
	u2 _size;
	u1* _info;
};

}
#endif
