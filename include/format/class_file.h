#ifndef _AVM_CLASS_FILE_H_
#define _AVM_CLASS_FILE_H_

#include <cstdint>

namespace avm {
    class ClassFile {
    	friend class ClassParser;

        private:
    		uint32_t magic;
    		uint16_t minor_version;
    		uint16_t major_version;
    		uint16_t constant_pool_count;
    };
}

#endif
