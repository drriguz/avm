#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

using invoke_fn = void(Context&, const Instruction*);

invoke_fn* invoke_mapping[] = {
    invoke_nop, invoke_aconst_null, invoke_iconst_m1, invoke_iconst_0, invoke_iconst_1, invoke_iconst_2, invoke_iconst_3, invoke_iconst_4, invoke_iconst_5, invoke_lconst_0, invoke_lconst_1, invoke_fconst_0, invoke_fconst_1, invoke_fconst_2, invoke_dconst_0, invoke_dconst_1, invoke_bipush, invoke_sipush, invoke_ldc, invoke_ldc_w, invoke_ldc2_w,
    invoke_iload, invoke_lload, invoke_fload, invoke_dload, invoke_aload, invoke_iload_0, invoke_iload_1, invoke_iload_2, invoke_iload_3, invoke_lload_0, invoke_lload_1, invoke_lload_2, invoke_lload_3, invoke_fload_0, invoke_fload_1, invoke_fload_2, invoke_fload_3, invoke_dload_0, invoke_dload_1, invoke_dload_2, invoke_dload_3, invoke_aload_0, invoke_aload_1, invoke_aload_2, invoke_aload_3, invoke_iaload, invoke_laload, invoke_faload, invoke_daload, invoke_aaload, invoke_baload, invoke_caload, invoke_saload,
    invoke_istore, invoke_lstore, invoke_fstore, invoke_dstore, invoke_astore, invoke_istore_0, invoke_istore_1, invoke_istore_2, invoke_istore_3, invoke_lstore_0, invoke_lstore_1, invoke_lstore_2, invoke_lstore_3, invoke_fstore_0, invoke_fstore_1, invoke_fstore_2, invoke_fstore_3, invoke_dstore_0, invoke_dstore_1, invoke_dstore_2, invoke_dstore_3, invoke_astore_0, invoke_astore_1, invoke_astore_2, invoke_astore_3, invoke_iastore, invoke_lastore, invoke_fastore, invoke_dastore, invoke_aastore, invoke_bastore, invoke_castore, invoke_sastore,
    invoke_pop, invoke_pop2, invoke_dup, invoke_dup_x1, invoke_dup_x2, invoke_dup2, invoke_dup2_x1, invoke_dup2_x2, invoke_swap,
    invoke_iadd, invoke_ladd, invoke_fadd, invoke_dadd, invoke_isub, invoke_lsub, invoke_fsub, invoke_dsub, invoke_imul, invoke_lmul, invoke_fmul, invoke_dmul, invoke_idiv, invoke_ldiv, invoke_fdiv, invoke_ddiv, invoke_irem, invoke_lrem, invoke_frem, invoke_drem, invoke_ineg, invoke_lneg, invoke_fneg, invoke_dneg, invoke_ishl, invoke_lshl, invoke_ishr, invoke_lshr, invoke_iushr, invoke_lushr, invoke_iand, invoke_land, invoke_ior, invoke_lor, invoke_ixor, invoke_lxor, invoke_iinc,
    invoke_i2l, invoke_i2f, invoke_i2d, invoke_l2i, invoke_l2f, invoke_l2d, invoke_f2i, invoke_f2l, invoke_f2d, invoke_d2i, invoke_d2l, invoke_d2f, invoke_i2b, invoke_i2c, invoke_i2s,
    invoke_lcmp, invoke_fcmpl, invoke_fcmpg, invoke_dcmpl, invoke_dcmpg, invoke_ifeq, invoke_ifne, invoke_iflt, invoke_ifge, invoke_ifgt, invoke_ifle, invoke_if_icmpeq, invoke_if_icmpne, invoke_if_icmplt, invoke_if_icmpge, invoke_if_icmpgt, invoke_if_icmple, invoke_if_acmpeq, invoke_if_acmpne,
    invoke_goto, invoke_jsr, invoke_ret, invoke_tableswitch, invoke_lookupswitch, invoke_ireturn, invoke_lreturn, invoke_freturn, invoke_dreturn, invoke_areturn, invoke_return,
    invoke_getstatic, invoke_putstatic, invoke_getfield, invoke_putfield, invoke_invokevirtual, invoke_invokespecial, invoke_invokestatic, invoke_invokeinterface, invoke_invokedynamic, invoke_new, invoke_newarray, invoke_anewarray, invoke_arraylength, invoke_athrow, invoke_checkcast, invoke_instanceof, invoke_monitorenter, invoke_monitorexit,
    invoke_wide, invoke_multianewarray, invoke_ifnull, invoke_ifnonnull, invoke_goto_w, invoke_jsr_w,
    invoke_breakpoint, invoke_impdep1, invoke_impdep2,
};

Interpreter::Interpreter() {

}

Interpreter::~Interpreter() {

}

void Interpreter::invoke(Context* context, const Instruction* instruction) {
    invoke_fn* invoker = invoke_mapping[instruction->getOpcode()];
    invoker(*context, instruction);
}

VmField* Interpreter::lookupField(Context& context, const u2 fieldRefIndex) {
    const ConstantPool* constantPool = context.frame()->getRuntimeConstantPool();
    const ConstantFieldref* fieldRef = (const ConstantFieldref*)constantPool->at(fieldRefIndex);
    const ConstantClass* classRef = (const ConstantClass*)constantPool->at(fieldRef->getClassIndex());
    std::string className = constantPool->getString(classRef->getNameIndex());

    const ConstantNameAndType* nameAndType = (const ConstantNameAndType*)constantPool->at(fieldRef->getNameAndTypeIndex());
    std::string fieldName = constantPool->getString(nameAndType->getNameIndex());

    auto theClass = context.getJVM()->getClass(className);
    theClass->initialize();

    return theClass->getField(fieldName);
}

VmMethod* Interpreter::lookupMethod(Context& context, const u2 methodRefIndex) {
    const ConstantPool* constantPool = context.frame()->getRuntimeConstantPool();

    ConstantMethodref* methodRef = (ConstantMethodref*) constantPool->at(methodRefIndex);
    
    const ConstantClass* classRef = (const ConstantClass*)constantPool->at(methodRef->getClassIndex());
    std::string className = constantPool->getString(classRef->getNameIndex());

    const ConstantNameAndType* nameAndType = (const ConstantNameAndType*)constantPool->at(methodRef->getNameAndTypeIndex());
    std::string methodName = constantPool->getString(nameAndType->getNameIndex());
    std::string descriptor = constantPool->getString(nameAndType->getDescriptorIndex());

    auto theClass = context.getJVM()->getClass(className);
    theClass->initialize();

    // fixme:
    // return theClass->getRawClass()->getMethod(methodName, descriptor);
    return nullptr;
}