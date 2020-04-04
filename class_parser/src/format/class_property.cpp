#include "class_file/format/class_property.h"
#include "class_file/exceptions.h"

using namespace avm;

ClassProperty::ClassProperty()
:_accessFlags(0),
 _nameIndex(0),
 _descriptorIndex(0),
 WithAttributes(){

}

ClassProperty::~ClassProperty(){
}
