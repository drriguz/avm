#ifndef _AVM_CONSTANT_INFO_H_
#define _AVM_CONSTANT_INFO_H_

#include <string>

#include "../types.h"
#include "constant_types.h"

namespace avm {

class ConstantInfo {
public:
    ConstantInfo(const ConstantType &type);
    virtual ~ConstantInfo();
public:
    inline const ConstantType getType() const {
        return _type;
    }
protected:
    ConstantType _type;

protected:
    /*
     * allow copy & move only for children
     * https://stackoverflow.com/questions/8777724/store-derived-class-objects-in-base-class-variables
     */
    ConstantInfo(ConstantInfo&&) {
    }
    ConstantInfo(const ConstantInfo&) {
    }
    ConstantInfo& operator=(const ConstantInfo&) {
    }
};

}
#endif
