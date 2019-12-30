#ifndef _AVM_ACCESS_FLAGS_H_
#define _AVM_ACCESS_FLAGS_H_

#define ACC_PUBLIC      0x0001
#define ACC_PRIVATE 	0x0002
#define ACC_PROTECTED 	0x0004
#define ACC_STATIC 	    0x0008
#define ACC_FINAL 	    0x0010
#define ACC_SUPER 	    0x0020 /* Treat superclass methods specially when invoked by the invokespecial instruction. */
#define ACC_VOLATILE    0x0040
#define ACC_TRANSIENT   0x0080
#define ACC_INTERFACE 	0x0200 /* Is an interface, not a class. */
#define ACC_ABSTRACT 	0x0400
#define ACC_SYNTHETIC 	0x1000 /* Declared synthetic; not present in the source code. */
#define ACC_ANNOTATION 	0x2000
#define ACC_ENUM 	    0x4000

#endif
