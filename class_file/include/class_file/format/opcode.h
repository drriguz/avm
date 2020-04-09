#ifndef _AVM_OPCODE_H_
#define _AVM_OPCODE_H_

#include "class_file/format/types.h"

namespace avm {
    class Opcode {
    public:
        Opcode(const u2& opcode, const u2& oprandsCount, const u2* oprands);
        virtual ~Opcode();
    protected:
        u2 _opcode;
        u2 _oprandsCount;
        u2* _oprands;
    };
}

#endif
