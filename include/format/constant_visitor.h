#ifndef _AVM_CONSTNT_PRINTER_H_
#define _AVM_CONSTNT_PRINTER_H_

#include "format/types.h"
#include "format/constants.h"

#include <string>

namespace avm {

class ConstantVisitor {
public:
	ConstantVisitor(const u2&count, const ConstantInfo* pool);
	~ConstantVisitor();
public:
	void verbose();
	std::string visit(const u2& constantId, const ConstantTypes* expceted =
			nullptr) const;
private:
	std::string getConstantTypeName(const ConstantTypes& type) const;
private:
	const u2 constant_pool_count;
	const ConstantInfo* constant_pool;
};
}

#endif
