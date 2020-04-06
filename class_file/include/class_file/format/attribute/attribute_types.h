#ifndef _AVM_ATTRIBUTE_TYPES_H_
#define _AVM_ATTRIBUTE_TYPES_H_

namespace avm {
	enum AttributeTypes {
		ConstantValue,
		Code,
		StackMapTable,
		Exceptions,
		InnerClasses,
		EnclosingMethod,
		Synthetic,
		Signature,
		SourceFile,
		SourceDebugExtension,
		LineNumberTable,
		LocalVariableTable,
		LocalVariableTypeTable,
		Deprecated,
		RuntimeVisibleAnnotations,
		RuntimeInvisibleAnnotations,
		RuntimeVisibleParameterAnnotations,
		RuntimeInvisibleParameterAnnotations,
		AnnotationDefault,
		BootstrapMethod,
	};
}
#endif
