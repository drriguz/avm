#ifndef _AVM_SLOT_H_
#define _AVM_SLOT_H_

#include <cstdint>

#ifdef _ARCH_X64_
#define SLOT uint64_t
#else
#define SLOT uint32_t
#pragma message "32bit system detetectd, will not use 8-bytes references"
#endif

typedef SLOT reference;

#endif
