#include "format/class_property.h"
#include "exceptions.h"

using namespace avm;

ClassProperty::ClassProperty()
:_accessFlags(0),
 _nameIndex(0),
 _descriptorIndex(0),
 WithAttributes(){

}

ClassProperty::~ClassProperty(){
}
