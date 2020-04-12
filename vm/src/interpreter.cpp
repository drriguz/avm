#include "vm/interpreter.h"
#include "vm/exceptions.h"

#include <iostream>
#include <string>

using namespace avm;
using invoke_fn = void(const ConstantPool*, const Instruction*, Frame*);
invoke_fn* invoke_mapping[] = {
invoke_nop             ,
invoke_aconst_null     ,
invoke_iconst_m1       ,
invoke_iconst_0        ,
invoke_iconst_1        ,
invoke_iconst_2        ,
invoke_iconst_3        ,
invoke_iconst_4        ,
invoke_iconst_5        ,
invoke_lconst_0        ,
invoke_lconst_1        ,
invoke_fconst_0        ,
invoke_fconst_1        ,
invoke_fconst_2        ,
invoke_dconst_0        ,
invoke_dconst_1        ,
invoke_bipush          ,
invoke_sipush          ,
invoke_ldc             ,
invoke_ldc_w           ,
invoke_ldc2_w          ,
invoke_iload           ,
invoke_lload           ,
invoke_fload           ,
invoke_dload           ,
invoke_aload           ,
invoke_iload_0         ,
invoke_iload_1         ,
invoke_iload_2         ,
invoke_iload_3         ,
invoke_lload_0         ,
invoke_lload_1         ,
invoke_lload_2         ,
invoke_lload_3         ,
invoke_fload_0         ,
invoke_fload_1         ,
invoke_fload_2         ,
invoke_fload_3         ,
invoke_dload_0         ,
invoke_dload_1         ,
invoke_dload_2         ,
invoke_dload_3         ,
invoke_aload_0         ,
invoke_aload_1         ,
invoke_aload_2         ,
invoke_aload_3         ,
invoke_iaload          ,
invoke_laload          ,
invoke_faload          ,
invoke_daload          ,
invoke_aaload          ,
invoke_baload          ,
invoke_caload          ,
invoke_saload          ,
invoke_istore          ,
invoke_lstore          ,
invoke_fstore          ,
invoke_dstore          ,
invoke_astore          ,
invoke_istore_0        ,
invoke_istore_1        ,
invoke_istore_2        ,
invoke_istore_3        ,
invoke_lstore_0        ,
invoke_lstore_1        ,
invoke_lstore_2        ,
invoke_lstore_3        ,
invoke_fstore_0        ,
invoke_fstore_1        ,
invoke_fstore_2        ,
invoke_fstore_3        ,
invoke_dstore_0        ,
invoke_dstore_1        ,
invoke_dstore_2        ,
invoke_dstore_3        ,
invoke_astore_0        ,
invoke_astore_1        ,
invoke_astore_2        ,
invoke_astore_3        ,
invoke_iastore         ,
invoke_lastore         ,
invoke_fastore         ,
invoke_dastore         ,
invoke_aastore         ,
invoke_bastore         ,
invoke_castore         ,
invoke_sastore         ,
invoke_pop             ,
invoke_pop2            ,
invoke_dup             ,
invoke_dup_x1          ,
invoke_dup_x2          ,
invoke_dup2            ,
invoke_dup2_x1         ,
invoke_dup2_x2         ,
invoke_swap            ,
invoke_iadd            ,
invoke_ladd            ,
invoke_fadd            ,
invoke_dadd            ,
invoke_isub            ,
invoke_lsub            ,
invoke_fsub            ,
invoke_dsub            ,
invoke_imul            ,
invoke_lmul            ,
invoke_fmul            ,
invoke_dmul            ,
invoke_idiv            ,
invoke_ldiv            ,
invoke_fdiv            ,
invoke_ddiv            ,
invoke_irem            ,
invoke_lrem            ,
invoke_frem            ,
invoke_drem            ,
invoke_ineg            ,
invoke_lneg            ,
invoke_fneg            ,
invoke_dneg            ,
invoke_ishl            ,
invoke_lshl            ,
invoke_ishr            ,
invoke_lshr            ,
invoke_iushr           ,
invoke_lushr           ,
invoke_iand            ,
invoke_land            ,
invoke_ior             ,
invoke_lor             ,
invoke_ixor            ,
invoke_lxor            ,
invoke_iinc            ,
invoke_i2l             ,
invoke_i2f             ,
invoke_i2d             ,
invoke_l2i             ,
invoke_l2f             ,
invoke_l2d             ,
invoke_f2i             ,
invoke_f2l             ,
invoke_f2d             ,
invoke_d2i             ,
invoke_d2l             ,
invoke_d2f             ,
invoke_i2b             ,
invoke_i2c             ,
invoke_i2s             ,
invoke_lcmp            ,
invoke_fcmpl           ,
invoke_fcmpg           ,
invoke_dcmpl           ,
invoke_dcmpg           ,
invoke_ifeq            ,
invoke_ifne            ,
invoke_iflt            ,
invoke_ifge            ,
invoke_ifgt            ,
invoke_ifle            ,
invoke_if_icmpeq       ,
invoke_if_icmpne       ,
invoke_if_icmplt       ,
invoke_if_icmpge       ,
invoke_if_icmpgt       ,
invoke_if_icmple       ,
invoke_if_acmpeq       ,
invoke_if_acmpne       ,
invoke_goto            ,
invoke_jsr             ,
invoke_ret             ,
invoke_tableswitch     ,
invoke_lookupswitch    ,
invoke_ireturn         ,
invoke_lreturn         ,
invoke_freturn         ,
invoke_dreturn         ,
invoke_areturn         ,
invoke_return          ,
invoke_getstatic       ,
invoke_putstatic       ,
invoke_getfield        ,
invoke_putfield        ,
invoke_invokevirtual   ,
invoke_invokespecial   ,
invoke_invokestatic    ,
invoke_invokeinterface ,
invoke_invokedynamic   ,
invoke_new             ,
invoke_newarray        ,
invoke_anewarray       ,
invoke_arraylength     ,
invoke_athrow          ,
invoke_checkcast       ,
invoke_instanceof      ,
invoke_monitorenter    ,
invoke_monitorexit     ,
invoke_wide            ,
invoke_multianewarray  ,
invoke_ifnull          ,
invoke_ifnonnull       ,
invoke_goto_w          ,
invoke_jsr_w           ,
invoke_breakpoint      ,
invoke_impdep1         ,
invoke_impdep2         ,

};

Interpreter::Interpreter(){

}

Interpreter::~Interpreter(){

}

void Interpreter::execute(VmThread* thread){
    while(true) {
        const Instruction* instruction = thread->nextInstruction();
        if(instruction == nullptr)
            break;
        invoke(thread->currentClass()->getRuntimeConstantPool(), instruction, thread->currentFrame());
        std::cout << "=>" << instruction->getOpcode() << std::endl;
    }
}

void Interpreter::invoke(const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame) {
    invoke_fn* invoker = invoke_mapping[instruction->getOpcode()];
    invoker(runtimeConstantPool, instruction, frame);
}

/* ------------------- */

void avm::invoke_nop             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aconst_null     (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iconst_m1       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iconst_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(0);
} 
void avm::invoke_iconst_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(1);
} 
void avm::invoke_iconst_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(2);
} 
void avm::invoke_iconst_3        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(3);
} 
void avm::invoke_iconst_4        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(4);
} 
void avm::invoke_iconst_5        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(5);
} 
void avm::invoke_lconst_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lconst_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fconst_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fconst_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fconst_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dconst_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dconst_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_bipush          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_sipush          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldc             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldc_w           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldc2_w          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iload           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iload_0         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame) {
    frame->getOperandStack()->pushInt(frame->getLocalVariables()->getInt(0));
}
void avm::invoke_iload_1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(frame->getLocalVariables()->getInt(1));
}
void avm::invoke_iload_2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(frame->getLocalVariables()->getInt(2));
}
void avm::invoke_iload_3         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    frame->getOperandStack()->pushInt(frame->getLocalVariables()->getInt(3));
}
void avm::invoke_lload_0         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload_1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload_2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload_3         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_0         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_3         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_0         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_3         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_0         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_3         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iaload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_laload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_faload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_daload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aaload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_baload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_caload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_saload          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_istore          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_istore_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ 
    frame->getLocalVariables()->setInt(0, frame->getOperandStack()->popInt());
 } 
void avm::invoke_istore_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ 
    frame->getLocalVariables()->setInt(1, frame->getOperandStack()->popInt());
 } 
void avm::invoke_istore_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ 
    frame->getLocalVariables()->setInt(2, frame->getOperandStack()->popInt());
 } 
void avm::invoke_istore_3        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ 
    frame->getLocalVariables()->setInt(3, frame->getOperandStack()->popInt());
 } 
void avm::invoke_lstore_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore_3        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_3        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_3        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_0        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_1        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_2        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_3        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_bastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_castore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_sastore         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_pop             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_pop2            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup_x1          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup_x2          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup2            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup2_x1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup2_x2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_swap            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iadd            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame) {
    int32_t i1 = frame->getOperandStack()->popInt();
    int32_t i2 = frame->getOperandStack()->popInt();
    frame->getOperandStack()->pushInt(i1 + i2);
}
void avm::invoke_ladd            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fadd            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dadd            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_isub            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lsub            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fsub            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dsub            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_imul            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lmul            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fmul            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dmul            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_idiv            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldiv            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fdiv            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ddiv            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_irem            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lrem            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_frem            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_drem            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ineg            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lneg            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fneg            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dneg            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ishl            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lshl            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ishr            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lshr            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iushr           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lushr           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iand            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_land            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ior             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lor             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ixor            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lxor            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iinc            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2l             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2f             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2d             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_l2i             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_l2f             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_l2d             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_f2i             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_f2l             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_f2d             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_d2i             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_d2l             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_d2f             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2b             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2c             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2s             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lcmp            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fcmpl           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fcmpg           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dcmpl           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dcmpg           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifeq            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifne            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iflt            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifge            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifgt            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifle            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpeq       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpne       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmplt       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpge       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpgt       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmple       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_acmpeq       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_acmpne       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_goto            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_jsr             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ret             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_tableswitch     (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lookupswitch    (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ireturn         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lreturn         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_freturn         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dreturn         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_areturn         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_return          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame) {
    frame->returnVoid();
} 
void avm::invoke_getstatic       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){
    // FIXME:
    u2 index = instruction->getOprandAsU2();
    std::cout << "get_static #" << index << std::endl;
    frame->getOperandStack()->pushInt(-1);
}
void avm::invoke_putstatic       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_getfield        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_putfield        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokevirtual   (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame) {
    u2 index = instruction->getOprandAsU2();
    std::cout << "invoke_virtual #" << index << std::endl;
}
void avm::invoke_invokespecial   (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokestatic    (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokeinterface (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokedynamic   (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_new             (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_newarray        (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_anewarray       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_arraylength     (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_athrow          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_checkcast       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_instanceof      (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_monitorenter    (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_monitorexit     (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_wide            (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_multianewarray  (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifnull          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifnonnull       (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_goto_w          (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_jsr_w           (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_breakpoint      (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_impdep1         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_impdep2         (const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 