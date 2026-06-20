#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"

#include <iostream>
#include <string>

using namespace avm;

/*
References

178 (0xb2)    getstatic
179 (0xb3)    putstatic
180 (0xb4)    getfield
181 (0xb5)    putfield
182 (0xb6)    invokevirtual
183 (0xb7)    invokespecial
184 (0xb8)    invokestatic
185 (0xb9)    invokeinterface
186 (0xba)    invokedynamic
187 (0xbb)    new
188 (0xbc)    newarray
189 (0xbd)    anewarray
190 (0xbe)    arraylength
191 (0xbf)    athrow
192 (0xc0)    checkcast
193 (0xc1)    instanceof
194 (0xc2)    monitorenter
195 (0xc3)    monitorexit
*/

void avm::invoke_getstatic       (Context& context, const Instruction* instruction) {
    VmField* theField = Interpreter::lookupField(context, instruction->getOprandAsU2());
    context.frame()->getOperandStack()->pushField(theField);
}

void avm::invoke_putstatic       (Context& context, const Instruction* instruction) {
    VmField* theField = Interpreter::lookupField(context, instruction->getOprandAsU2());
    context.frame()->getOperandStack()->popField(theField);
}
void avm::invoke_getfield        (Context& context, const Instruction* instruction) {
    VmField* theField = Interpreter::lookupField(context, instruction->getOprandAsU2());
    reference objectref = context.frame()->getOperandStack()->popReference();
    if(objectref == 0) throw RuntimeException("NullPointerException: getfield on null");
    Object obj((OBJECT_UNIT*)objectref, 0);
    int offset = theField->getOffset();
    const FieldType* type = theField->getDescriptor();
    if(type->isBaseType()) {
        switch(((BaseType*)type)->getType()) {
        case FIELD_Byte:
        case FIELD_Short:
        case FIELD_Char:
        case FIELD_Int:
        case FIELD_Boolean:
            context.frame()->getOperandStack()->pushInt(obj.getIntAt(offset));
            break;
        case FIELD_Float:
            context.frame()->getOperandStack()->pushFloat(obj.getFloatAt(offset));
            break;
        case FIELD_Long:
            context.frame()->getOperandStack()->pushLong(obj.getLongAt(offset));
            break;
        case FIELD_Double:
            context.frame()->getOperandStack()->pushDouble(obj.getDoubleAt(offset));
            break;
        default:
            break;
        }
    } else if(type->isObject()) {
        context.frame()->getOperandStack()->pushReference(obj.getReferenceAt(offset));
    } else {
        throw UnsupportedInstructionException("getfield: array type not supported");
    }
}
void avm::invoke_putfield        (Context& context, const Instruction* instruction) {
    VmField* theField = Interpreter::lookupField(context, instruction->getOprandAsU2());
    int offset = theField->getOffset();
    const FieldType* type = theField->getDescriptor();

    // Pop value first, then objectref (value is on top)
    // For category 2 types (long/double), value occupies 2 stack slots
    if(type->isBaseType()) {
        switch(((BaseType*)type)->getType()) {
        case FIELD_Long: {
            int64_t value = context.frame()->getOperandStack()->popLong();
            reference objectref = context.frame()->getOperandStack()->popReference();
            if(objectref == 0) throw RuntimeException("NullPointerException: putfield on null");
            Object obj((OBJECT_UNIT*)objectref, 0);
            obj.setLongAt(offset, value);
            break;
        }
        case FIELD_Double: {
            double value = context.frame()->getOperandStack()->popDouble();
            reference objectref = context.frame()->getOperandStack()->popReference();
            if(objectref == 0) throw RuntimeException("NullPointerException: putfield on null");
            Object obj((OBJECT_UNIT*)objectref, 0);
            obj.setDoubleAt(offset, value);
            break;
        }
        case FIELD_Float: {
            float value = context.frame()->getOperandStack()->popFloat();
            reference objectref = context.frame()->getOperandStack()->popReference();
            if(objectref == 0) throw RuntimeException("NullPointerException: putfield on null");
            Object obj((OBJECT_UNIT*)objectref, 0);
            obj.setFloatAt(offset, value);
            break;
        }
        default: {
            int32_t value = context.frame()->getOperandStack()->popInt();
            reference objectref = context.frame()->getOperandStack()->popReference();
            if(objectref == 0) throw RuntimeException("NullPointerException: putfield on null");
            Object obj((OBJECT_UNIT*)objectref, 0);
            obj.setIntAt(offset, value);
            break;
        }
        }
    } else if(type->isObject()) {
        reference value = context.frame()->getOperandStack()->popReference();
        reference objectref = context.frame()->getOperandStack()->popReference();
        if(objectref == 0) throw RuntimeException("NullPointerException: putfield on null");
        Object obj((OBJECT_UNIT*)objectref, 0);
        obj.setReferenceAt(offset, value);
    } else {
        throw UnsupportedInstructionException("putfield: array type not supported");
    }
}
void avm::invoke_invokevirtual   (Context& context, const Instruction* instruction) {
    VmMethod* method = Interpreter::lookupMethod(context, instruction->getOprandAsU2());
    Interpreter interpreter;
    if(method->isNative()) {
        interpreter.invokeNative(method, *context.getJVM(), *context.getStack());
    } else {
        interpreter.invoke(method, *context.getJVM(), *context.getStack());
    }
}
void avm::invoke_invokespecial   (Context& context, const Instruction* instruction) {
    VmMethod* method = Interpreter::lookupMethod(context, instruction->getOprandAsU2());
    // Skip java.lang.Object.<init> to prevent infinite recursion
    // (the stub Object constructor calls itself via invokespecial)
    if(method->getName() == "<init>" && method->getClass()->getClassName() == "java/lang/Object") {
        // invoke() would pop the objectref for local 0, so we must do it manually
        context.frame()->getOperandStack()->popReference();
        return;
    }
    Interpreter interpreter;
    if(method->isNative()) {
        interpreter.invokeNative(method, *context.getJVM(), *context.getStack());
    } else {
        interpreter.invoke(method, *context.getJVM(), *context.getStack());
    }
}
void avm::invoke_invokestatic    (Context& context, const Instruction* instruction) {
    VmMethod* staticMethod = Interpreter::lookupMethod(context, instruction->getOprandAsU2());

    Interpreter interpreter;
    if(staticMethod->isNative())
        interpreter.invokeNative(staticMethod, *context.getJVM(), *context.getStack());
    else
        interpreter.invoke(staticMethod, *context.getJVM(), *context.getStack());
}
void avm::invoke_invokeinterface (Context& context, const Instruction* instruction) {
    // For now, treat invokeinterface the same as invokevirtual
    // (no itable needed until real polymorphism)
    VmMethod* method = Interpreter::lookupMethod(context, instruction->getOprandAsU2());
    Interpreter interpreter;
    if(method->isNative()) {
        interpreter.invokeNative(method, *context.getJVM(), *context.getStack());
    } else {
        interpreter.invoke(method, *context.getJVM(), *context.getStack());
    }
}
void avm::invoke_invokedynamic   (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("invokedynamic: not supported (Java 7+ feature)");
}
void avm::invoke_new             (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprandAsU2();
    const ConstantPool* cp = context.frame()->getRuntimeConstantPool();
    const ConstantClass* classRef = (const ConstantClass*)cp->at(index);
    std::string className = cp->getString(classRef->getNameIndex());

    auto vmClass = context.getJVM()->getClass(className);
    vmClass->initialize();

    Object obj = context.getJVM()->getHeap()->newInstance(*vmClass);
    // Push the pointer to the object as a reference
    reference ref = reinterpret_cast<reference>(obj.getData());
    context.frame()->getOperandStack()->pushReference(ref);
}
void avm::invoke_newarray        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("newarray: arrays not yet supported");
}
void avm::invoke_anewarray       (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("anewarray: arrays not yet supported");
}
void avm::invoke_arraylength     (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("arraylength: arrays not yet supported");
}
void avm::invoke_athrow          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("athrow: exception handling not yet supported");
}
void avm::invoke_checkcast       (Context& context, const Instruction* instruction) {
    // For now, no-op (skip the check) - just leave the reference on the stack
    // Proper implementation would check the type hierarchy
}
void avm::invoke_instanceof      (Context& context, const Instruction* instruction) {
    // For now, push 1 if reference is non-null, 0 if null
    // Proper implementation would check the type hierarchy
    reference ref = context.frame()->getOperandStack()->popReference();
    context.frame()->getOperandStack()->pushInt(ref != 0 ? 1 : 0);
}
void avm::invoke_monitorenter    (Context& context, const Instruction* instruction) {
    // Pop the reference - no actual synchronization for now
    context.frame()->getOperandStack()->popReference();
}
void avm::invoke_monitorexit     (Context& context, const Instruction* instruction) {
    // Pop the reference - no actual synchronization for now
    context.frame()->getOperandStack()->popReference();
}
