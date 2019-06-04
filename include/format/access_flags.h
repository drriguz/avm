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

inline void getAccessFlags(const u2& flags, std::string& names) {
	if (flags & ACC_PUBLIC)
		names += "ACC_PUBLIC,";
	if (flags & ACC_FINAL)
		names += "ACC_FINAL,";
	if (flags & ACC_SUPER)
		names += "ACC_SUPER,";
	if (flags & ACC_INTERFACE)
		names += "ACC_INTERFACE,";
	if (flags & ACC_ABSTRACT)
		names += "ACC_ABSTRACT,";
	if (flags & ACC_SYNTHETIC)
		names += "ACC_SYNTHETIC,";
	if (flags & ACC_ANNOTATION)
		names += "ACC_ANNOTATION,";
	if (flags & ACC_ENUM)
		names += "ACC_ENUM,";
}

#endif
