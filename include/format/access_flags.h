#ifndef _AVM_ACCESS_FLAGS_H_
#define _AVM_ACCESS_FLAGS_H_

#include <string>
#include "types.h"

#define ACC_PUBLIC	    0x0001
#define ACC_FINAL	    0x0010
#define ACC_SUPER	    0x0020
#define ACC_INTERFACE	0x0200
#define ACC_ABSTRACT	0x0400
#define ACC_SYNTHETIC	0x1000
#define ACC_ANNOTATION	0x2000
#define ACC_ENUM	    0x4000

namespace avm {
class AccessFlags {
public:
	static void getAccessFlags(const u2& flags, std::string& names) {
		if (flags & ACC_PUBLIC)
			append("ACC_PUBLIC", names);
		if (flags & ACC_FINAL)
			append("ACC_FINAL", names);
		if (flags & ACC_SUPER)
			append("ACC_SUPER", names);
		if (flags & ACC_INTERFACE)
			append("ACC_INTERFACE", names);
		if (flags & ACC_ABSTRACT)
			append("ACC_ABSTRACT", names);
		if (flags & ACC_SYNTHETIC)
			append("ACC_SYNTHETIC", names);
		if (flags & ACC_ANNOTATION)
			append("ACC_ANNOTATION", names);
		if (flags & ACC_ENUM)
			append("ACC_ENUM", names);
	}
private:
	static void append(const std::string&name, std::string& names) {
		if (!names.empty())
			names += "|";
		names += name;
	}
};
}

#endif
