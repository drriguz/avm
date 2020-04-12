#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "class_file/format/constant_pool.h"

#include <iostream>
#include <string>

using namespace avm;
using invoke_fn = void(Context&, const Instruction*);
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

void Interpreter::execute(Context& context){
    while(true) {
        const Instruction* instruction = context.thread()->nextInstruction();
        if(instruction == nullptr)
            break;
        invoke(context, instruction);
        std::cout << "=>" << instruction->getOpcode() << std::endl;
    }
}

void Interpreter::invoke(Context& context, const Instruction* instruction) {
    invoke_fn* invoker = invoke_mapping[instruction->getOpcode()];
    invoker(context, instruction);
}

/* ------------------- */

void avm::invoke_nop             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aconst_null     (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iconst_m1       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iconst_0        (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(0);
} 
void avm::invoke_iconst_1        (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(1);
} 
void avm::invoke_iconst_2        (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(2);
} 
void avm::invoke_iconst_3        (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(3);
} 
void avm::invoke_iconst_4        (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(4);
} 
void avm::invoke_iconst_5        (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(5);
} 
void avm::invoke_lconst_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lconst_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fconst_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fconst_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fconst_2        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dconst_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dconst_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_bipush          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_sipush          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldc             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldc_w           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldc2_w          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iload           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iload_0         (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(0));
}
void avm::invoke_iload_1         (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(1));
}
void avm::invoke_iload_2         (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(2));
}
void avm::invoke_iload_3         (Context& context, const Instruction* instruction){
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(3));
}
void avm::invoke_lload_0         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload_1         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload_2         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lload_3         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_0         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_1         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_2         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fload_3         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_0         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_1         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_2         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dload_3         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_0         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_1         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_2         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aload_3         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iaload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_laload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_faload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_daload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aaload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_baload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_caload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_saload          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_istore          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_istore_0        (Context& context, const Instruction* instruction){ 
    context.frame()->getLocalVariables()->setInt(0, context.frame()->getOperandStack()->popInt());
 } 
void avm::invoke_istore_1        (Context& context, const Instruction* instruction){ 
    context.frame()->getLocalVariables()->setInt(1, context.frame()->getOperandStack()->popInt());
 } 
void avm::invoke_istore_2        (Context& context, const Instruction* instruction){ 
    context.frame()->getLocalVariables()->setInt(2, context.frame()->getOperandStack()->popInt());
 } 
void avm::invoke_istore_3        (Context& context, const Instruction* instruction){ 
    context.frame()->getLocalVariables()->setInt(3, context.frame()->getOperandStack()->popInt());
 } 
void avm::invoke_lstore_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore_2        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lstore_3        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_2        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fstore_3        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_2        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dstore_3        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_0        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_1        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_2        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_astore_3        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_aastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_bastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_castore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_sastore         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_pop             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_pop2            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup_x1          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup_x2          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup2            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup2_x1         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dup2_x2         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_swap            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iadd            (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushInt(i1 + i2);
}
void avm::invoke_ladd            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fadd            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dadd            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_isub            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lsub            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fsub            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dsub            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_imul            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lmul            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fmul            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dmul            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_idiv            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ldiv            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fdiv            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ddiv            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_irem            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lrem            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_frem            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_drem            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ineg            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lneg            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fneg            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dneg            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ishl            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lshl            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ishr            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lshr            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iushr           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lushr           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iand            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_land            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ior             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lor             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ixor            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lxor            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iinc            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2l             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2f             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2d             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_l2i             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_l2f             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_l2d             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_f2i             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_f2l             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_f2d             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_d2i             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_d2l             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_d2f             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2b             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2c             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_i2s             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lcmp            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fcmpl           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_fcmpg           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dcmpl           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dcmpg           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifeq            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifne            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_iflt            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifge            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifgt            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifle            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpeq       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpne       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmplt       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpge       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmpgt       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_icmple       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_acmpeq       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_if_acmpne       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_goto            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_jsr             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ret             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_tableswitch     (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lookupswitch    (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ireturn         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_lreturn         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_freturn         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_dreturn         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_areturn         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_return          (Context& context, const Instruction* instruction) {
    context.frame()->returnVoid();
} 
void avm::invoke_getstatic       (Context& context, const Instruction* instruction){
    // FIXME:
    u2 fieldRefIndex = instruction->getOprandAsU2();
    
    const ConstantFieldref* fieldRef = (const ConstantFieldref*)context.constantPool()->at(fieldRefIndex);
    const ConstantClass* classRef = (const ConstantClass*)context.constantPool()->at(fieldRef->getClassIndex());
    const ConstantNameAndType* nameAndType = (const ConstantNameAndType*)context.constantPool()->at(fieldRef->getNameAndTypeIndex());
    std::cout << "get_static #" <<context.constantPool()->getString(classRef->getNameIndex()) <<  context.constantPool()->getString(nameAndType->getNameIndex()) << std::endl;
    context.frame()->getOperandStack()->pushInt(-1);
}
void avm::invoke_putstatic       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_getfield        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_putfield        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokevirtual   (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprandAsU2();
    std::cout << "invoke_virtual #" << index << std::endl;
}
void avm::invoke_invokespecial   (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokestatic    (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokeinterface (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_invokedynamic   (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_new             (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_newarray        (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_anewarray       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_arraylength     (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_athrow          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_checkcast       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_instanceof      (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_monitorenter    (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_monitorexit     (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_wide            (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_multianewarray  (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifnull          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_ifnonnull       (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_goto_w          (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_jsr_w           (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_breakpoint      (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_impdep1         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 
void avm::invoke_impdep2         (Context& context, const Instruction* instruction){ throw UnsupportedInstructionException(std::to_string(instruction->getOpcode())); } 