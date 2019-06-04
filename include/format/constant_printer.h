#ifndef _AVM_CONSTNT_PRINTER_H_
#define _AVM_CONSTNT_PRINTER_H_

#include "format/types.h"
#include "format/constants.h"

#include <string>

namespace avm {

class ConstantPrinter {
public:
	ConstantPrinter(const u2&count, const ConstantInfo* pool);
	~ConstantPrinter();
public:
	void verbose();
	void verbose(const ConstantTypes& type, const u1* info);
	void verbose(const u2& utf8Id);
private:
	std::string getConstantTypeName(const ConstantTypes& type) const;
private:
	const u2 constant_pool_count;
	const ConstantInfo* constant_pool;
};
}

#endif
