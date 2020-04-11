#ifndef _AVM_ATTRIBUTE_TYPES_H_
#define _AVM_ATTRIBUTE_TYPES_H_

namespace avm {
enum AttributeType {
    // The ConstantValue, Code and Exceptions attributes must be recognized and correctly read by a class file reader for correct interpretation of the class file by a Java Virtual Machine implementation. 
    CONSTANT_VALUE,
    CODE,
    Exceptions,

    // The InnerClasses, EnclosingMethod and Synthetic attributes must be recognized and correctly read by a class file reader in order to properly implement the Java SE platform class libraries
    InnerClasses,
    EnclosingMethod,
    Synthetic,

    // The RuntimeVisibleAnnotations, RuntimeInvisibleAnnotations, RuntimeVisibleParameterAnnotations, RuntimeInvisibleParameterAnnotations and AnnotationDefault attributes must be recognized and correctly read by a class file reader in order to properly implement the Java SE platform class libraries
    RuntimeVisibleAnnotations,
    RuntimeInvisibleAnnotations,
    RuntimeVisibleParameterAnnotations,
    RuntimeInvisibleParameterAnnotations,
    AnnotationDefault,

    Signature,
    StackMapTable,
    BootstrapMethod,

/*
 do not requreid:

 SourceFile,
 SourceDebugExtension,
 LineNumberTable,
 LocalVariableTable,
 LocalVariableTypeTable,
 Deprecated,
 */
};
}
#endif
