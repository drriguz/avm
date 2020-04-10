#ifndef _AVM_OPCODES_H_
#define _AVM_OPCODES_H_

#include "class_file/format/types.h"

enum Mnemonic {
    j_nop                = 0x00  , /*  00 */   
    j_aconst_null        = 0x01  , /*  01 */   
    j_iconst_m1          = 0x02  , /*  02 */   
    j_iconst_0           = 0x03  , /*  03 */   
    j_iconst_1           = 0x04  , /*  04 */   
    j_iconst_2           = 0x05  , /*  05 */   
    j_iconst_3           = 0x06  , /*  06 */   
    j_iconst_4           = 0x07  , /*  07 */   
    j_iconst_5           = 0x08  , /*  08 */   
    j_lconst_0           = 0x09  , /*  09 */   
    j_lconst_1           = 0x0a  , /*  10 */   
    j_fconst_0           = 0x0b  , /*  11 */   
    j_fconst_1           = 0x0c  , /*  12 */   
    j_fconst_2           = 0x0d  , /*  13 */   
    j_dconst_0           = 0x0e  , /*  14 */   
    j_dconst_1           = 0x0f  , /*  15 */   
    j_bipush             = 0x10  , /*  16 */   
    j_sipush             = 0x11  , /*  17 */   
    j_ldc                = 0x12  , /*  18 */   
    j_ldc_w              = 0x13  , /*  19 */   
    j_ldc2_w             = 0x14  , /*  20 */   
    j_iload              = 0x15  , /*  21 */   
    j_lload              = 0x16  , /*  22 */   
    j_fload              = 0x17  , /*  23 */   
    j_dload              = 0x18  , /*  24 */   
    j_aload              = 0x19  , /*  25 */   
    j_iload_0            = 0x1a  , /*  26 */   
    j_iload_1            = 0x1b  , /*  27 */   
    j_iload_2            = 0x1c  , /*  28 */   
    j_iload_3            = 0x1d  , /*  29 */   
    j_lload_0            = 0x1e  , /*  30 */   
    j_lload_1            = 0x1f  , /*  31 */   
    j_lload_2            = 0x20  , /*  32 */   
    j_lload_3            = 0x21  , /*  33 */   
    j_fload_0            = 0x22  , /*  34 */   
    j_fload_1            = 0x23  , /*  35 */   
    j_fload_2            = 0x24  , /*  36 */   
    j_fload_3            = 0x25  , /*  37 */   
    j_dload_0            = 0x26  , /*  38 */   
    j_dload_1            = 0x27  , /*  39 */   
    j_dload_2            = 0x28  , /*  40 */   
    j_dload_3            = 0x29  , /*  41 */   
    j_aload_0            = 0x2a  , /*  42 */   
    j_aload_1            = 0x2b  , /*  43 */   
    j_aload_2            = 0x2c  , /*  44 */   
    j_aload_3            = 0x2d  , /*  45 */   
    j_iaload             = 0x2e  , /*  46 */   
    j_laload             = 0x2f  , /*  47 */   
    j_faload             = 0x30  , /*  48 */   
    j_daload             = 0x31  , /*  49 */   
    j_aaload             = 0x32  , /*  50 */   
    j_baload             = 0x33  , /*  51 */   
    j_caload             = 0x34  , /*  52 */   
    j_saload             = 0x35  , /*  53 */   
    j_istore             = 0x36  , /*  54 */   
    j_lstore             = 0x37  , /*  55 */   
    j_fstore             = 0x38  , /*  56 */   
    j_dstore             = 0x39  , /*  57 */   
    j_astore             = 0x3a  , /*  58 */   
    j_istore_0           = 0x3b  , /*  59 */   
    j_istore_1           = 0x3c  , /*  60 */   
    j_istore_2           = 0x3d  , /*  61 */   
    j_istore_3           = 0x3e  , /*  62 */   
    j_lstore_0           = 0x3f  , /*  63 */   
    j_lstore_1           = 0x40  , /*  64 */   
    j_lstore_2           = 0x41  , /*  65 */   
    j_lstore_3           = 0x42  , /*  66 */   
    j_fstore_0           = 0x43  , /*  67 */   
    j_fstore_1           = 0x44  , /*  68 */   
    j_fstore_2           = 0x45  , /*  69 */   
    j_fstore_3           = 0x46  , /*  70 */   
    j_dstore_0           = 0x47  , /*  71 */   
    j_dstore_1           = 0x48  , /*  72 */   
    j_dstore_2           = 0x49  , /*  73 */   
    j_dstore_3           = 0x4a  , /*  74 */   
    j_astore_0           = 0x4b  , /*  75 */   
    j_astore_1           = 0x4c  , /*  76 */   
    j_astore_2           = 0x4d  , /*  77 */   
    j_astore_3           = 0x4e  , /*  78 */   
    j_iastore            = 0x4f  , /*  79 */   
    j_lastore            = 0x50  , /*  80 */   
    j_fastore            = 0x51  , /*  81 */   
    j_dastore            = 0x52  , /*  82 */   
    j_aastore            = 0x53  , /*  83 */   
    j_bastore            = 0x54  , /*  84 */   
    j_castore            = 0x55  , /*  85 */   
    j_sastore            = 0x56  , /*  86 */   
    j_pop                = 0x57  , /*  87 */   
    j_pop2               = 0x58  , /*  88 */   
    j_dup                = 0x59  , /*  89 */   
    j_dup_x1             = 0x5a  , /*  90 */   
    j_dup_x2             = 0x5b  , /*  91 */   
    j_dup2               = 0x5c  , /*  92 */   
    j_dup2_x1            = 0x5d  , /*  93 */   
    j_dup2_x2            = 0x5e  , /*  94 */   
    j_swap               = 0x5f  , /*  95 */   
    j_iadd               = 0x60  , /*  96 */   
    j_ladd               = 0x61  , /*  97 */   
    j_fadd               = 0x62  , /*  98 */   
    j_dadd               = 0x63  , /*  99 */   
    j_isub               = 0x64  , /* 100 */   
    j_lsub               = 0x65  , /* 101 */   
    j_fsub               = 0x66  , /* 102 */   
    j_dsub               = 0x67  , /* 103 */   
    j_imul               = 0x68  , /* 104 */   
    j_lmul               = 0x69  , /* 105 */   
    j_fmul               = 0x6a  , /* 106 */   
    j_dmul               = 0x6b  , /* 107 */   
    j_idiv               = 0x6c  , /* 108 */   
    j_ldiv               = 0x6d  , /* 109 */   
    j_fdiv               = 0x6e  , /* 110 */   
    j_ddiv               = 0x6f  , /* 111 */   
    j_irem               = 0x70  , /* 112 */   
    j_lrem               = 0x71  , /* 113 */   
    j_frem               = 0x72  , /* 114 */   
    j_drem               = 0x73  , /* 115 */   
    j_ineg               = 0x74  , /* 116 */   
    j_lneg               = 0x75  , /* 117 */   
    j_fneg               = 0x76  , /* 118 */   
    j_dneg               = 0x77  , /* 119 */   
    j_ishl               = 0x78  , /* 120 */   
    j_lshl               = 0x79  , /* 121 */   
    j_ishr               = 0x7a  , /* 122 */   
    j_lshr               = 0x7b  , /* 123 */   
    j_iushr              = 0x7c  , /* 124 */   
    j_lushr              = 0x7d  , /* 125 */   
    j_iand               = 0x7e  , /* 126 */   
    j_land               = 0x7f  , /* 127 */   
    j_ior                = 0x80  , /* 128 */   
    j_lor                = 0x81  , /* 129 */   
    j_ixor               = 0x82  , /* 130 */   
    j_lxor               = 0x83  , /* 131 */   
    j_iinc               = 0x84  , /* 132 */   
    j_i2l                = 0x85  , /* 133 */   
    j_i2f                = 0x86  , /* 134 */   
    j_i2d                = 0x87  , /* 135 */   
    j_l2i                = 0x88  , /* 136 */   
    j_l2f                = 0x89  , /* 137 */   
    j_l2d                = 0x8a  , /* 138 */   
    j_f2i                = 0x8b  , /* 139 */   
    j_f2l                = 0x8c  , /* 140 */   
    j_f2d                = 0x8d  , /* 141 */   
    j_d2i                = 0x8e  , /* 142 */   
    j_d2l                = 0x8f  , /* 143 */   
    j_d2f                = 0x90  , /* 144 */   
    j_i2b                = 0x91  , /* 145 */   
    j_i2c                = 0x92  , /* 146 */   
    j_i2s                = 0x93  , /* 147 */   
    j_lcmp               = 0x94  , /* 148 */   
    j_fcmpl              = 0x95  , /* 149 */   
    j_fcmpg              = 0x96  , /* 150 */   
    j_dcmpl              = 0x97  , /* 151 */   
    j_dcmpg              = 0x98  , /* 152 */   
    j_ifeq               = 0x99  , /* 153 */   
    j_ifne               = 0x9a  , /* 154 */   
    j_iflt               = 0x9b  , /* 155 */   
    j_ifge               = 0x9c  , /* 156 */   
    j_ifgt               = 0x9d  , /* 157 */   
    j_ifle               = 0x9e  , /* 158 */   
    j_if_icmpeq          = 0x9f  , /* 159 */   
    j_if_icmpne          = 0xa0  , /* 160 */   
    j_if_icmplt          = 0xa1  , /* 161 */   
    j_if_icmpge          = 0xa2  , /* 162 */   
    j_if_icmpgt          = 0xa3  , /* 163 */   
    j_if_icmple          = 0xa4  , /* 164 */   
    j_if_acmpeq          = 0xa5  , /* 165 */   
    j_if_acmpne          = 0xa6  , /* 166 */   
    j_goto               = 0xa7  , /* 167 */   
    j_jsr                = 0xa8  , /* 168 */   
    j_ret                = 0xa9  , /* 169 */   
    j_tableswitch        = 0xaa  , /* 170 */   
    j_lookupswitch       = 0xab  , /* 171 */   
    j_ireturn            = 0xac  , /* 172 */   
    j_lreturn            = 0xad  , /* 173 */   
    j_freturn            = 0xae  , /* 174 */   
    j_dreturn            = 0xaf  , /* 175 */   
    j_areturn            = 0xb0  , /* 176 */   
    j_return             = 0xb1  , /* 177 */   
    j_getstatic          = 0xb2  , /* 178 */   
    j_putstatic          = 0xb3  , /* 179 */   
    j_getfield           = 0xb4  , /* 180 */   
    j_putfield           = 0xb5  , /* 181 */   
    j_invokevirtual      = 0xb6  , /* 182 */   
    j_invokespecial      = 0xb7  , /* 183 */   
    j_invokestatic       = 0xb8  , /* 184 */   
    j_invokeinterface    = 0xb9  , /* 185 */   
    j_invokedynamic      = 0xba  , /* 186 */   
    j_new                = 0xbb  , /* 187 */   
    j_newarray           = 0xbc  , /* 188 */   
    j_anewarray          = 0xbd  , /* 189 */   
    j_arraylength        = 0xbe  , /* 190 */   
    j_athrow             = 0xbf  , /* 191 */   
    j_checkcast          = 0xc0  , /* 192 */   
    j_instanceof         = 0xc1  , /* 193 */   
    j_monitorenter       = 0xc2  , /* 194 */   
    j_monitorexit        = 0xc3  , /* 195 */   
    j_wide               = 0xc4  , /* 196 */   
    j_multianewarray     = 0xc5  , /* 197 */   
    j_ifnull             = 0xc6  , /* 198 */   
    j_ifnonnull          = 0xc7  , /* 199 */   
    j_goto_w             = 0xc8  , /* 200 */   
    j_jsr_w              = 0xc9  , /* 201 */   
    j_breakpoint         = 0xca  , /* 202 */   
    j_impdep1            = 0xfe  , /* 254 */   
    j_impdep2            = 0xff  , /* 255 */  
};

struct Opcode {
    Mnemonic opcode;
    u2 oprandCount;
};

static const Opcode instructionSet[] = {
    { j_nop               , 0 }, /* (0x00)  00 */ 
    { j_aconst_null       , 0 }, /* (0x01)  01 */ 
    { j_iconst_m1         , 0 }, /* (0x02)  02 */ 
    { j_iconst_0          , 0 }, /* (0x03)  03 */ 
    { j_iconst_1          , 0 }, /* (0x04)  04 */ 
    { j_iconst_2          , 0 }, /* (0x05)  05 */ 
    { j_iconst_3          , 0 }, /* (0x06)  06 */ 
    { j_iconst_4          , 0 }, /* (0x07)  07 */ 
    { j_iconst_5          , 0 }, /* (0x08)  08 */ 
    { j_lconst_0          , 0 }, /* (0x09)  09 */ 
    { j_lconst_1          , 0 }, /* (0x0a)  10 */ 
    { j_fconst_0          , 0 }, /* (0x0b)  11 */ 
    { j_fconst_1          , 0 }, /* (0x0c)  12 */ 
    { j_fconst_2          , 0 }, /* (0x0d)  13 */ 
    { j_dconst_0          , 0 }, /* (0x0e)  14 */ 
    { j_dconst_1          , 0 }, /* (0x0f)  15 */ 
    { j_bipush            , 1 }, /* (0x10)  16 */ 
    { j_sipush            , 2 }, /* (0x11)  17 */ 
    { j_ldc               , 1 }, /* (0x12)  18 */ 
    { j_ldc_w             , 2 }, /* (0x13)  19 */ 
    { j_ldc2_w            , 2 }, /* (0x14)  20 */ 
    { j_iload             , 1 }, /* (0x15)  21 */ 
    { j_lload             , 1 }, /* (0x16)  22 */ 
    { j_fload             , 1 }, /* (0x17)  23 */ 
    { j_dload             , 1 }, /* (0x18)  24 */ 
    { j_aload             , 1 }, /* (0x19)  25 */ 
    { j_iload_0           , 0 }, /* (0x1a)  26 */ 
    { j_iload_1           , 0 }, /* (0x1b)  27 */ 
    { j_iload_2           , 0 }, /* (0x1c)  28 */ 
    { j_iload_3           , 0 }, /* (0x1d)  29 */ 
    { j_lload_0           , 0 }, /* (0x1e)  30 */ 
    { j_lload_1           , 0 }, /* (0x1f)  31 */ 
    { j_lload_2           , 0 }, /* (0x20)  32 */ 
    { j_lload_3           , 0 }, /* (0x21)  33 */ 
    { j_fload_0           , 0 }, /* (0x22)  34 */ 
    { j_fload_1           , 0 }, /* (0x23)  35 */ 
    { j_fload_2           , 0 }, /* (0x24)  36 */ 
    { j_fload_3           , 0 }, /* (0x25)  37 */ 
    { j_dload_0           , 0 }, /* (0x26)  38 */ 
    { j_dload_1           , 0 }, /* (0x27)  39 */ 
    { j_dload_2           , 0 }, /* (0x28)  40 */ 
    { j_dload_3           , 0 }, /* (0x29)  41 */ 
    { j_aload_0           , 0 }, /* (0x2a)  42 */ 
    { j_aload_1           , 0 }, /* (0x2b)  43 */ 
    { j_aload_2           , 0 }, /* (0x2c)  44 */ 
    { j_aload_3           , 0 }, /* (0x2d)  45 */ 
    { j_iaload            , 0 }, /* (0x2e)  46 */ 
    { j_laload            , 0 }, /* (0x2f)  47 */ 
    { j_faload            , 0 }, /* (0x30)  48 */ 
    { j_daload            , 0 }, /* (0x31)  49 */ 
    { j_aaload            , 0 }, /* (0x32)  50 */ 
    { j_baload            , 0 }, /* (0x33)  51 */ 
    { j_caload            , 0 }, /* (0x34)  52 */ 
    { j_saload            , 0 }, /* (0x35)  53 */ 
    { j_istore            , 1 }, /* (0x36)  54 */ 
    { j_lstore            , 1 }, /* (0x37)  55 */ 
    { j_fstore            , 1 }, /* (0x38)  56 */ 
    { j_dstore            , 1 }, /* (0x39)  57 */ 
    { j_astore            , 1 }, /* (0x3a)  58 */ 
    { j_istore_0          , 0 }, /* (0x3b)  59 */ 
    { j_istore_1          , 0 }, /* (0x3c)  60 */ 
    { j_istore_2          , 0 }, /* (0x3d)  61 */ 
    { j_istore_3          , 0 }, /* (0x3e)  62 */ 
    { j_lstore_0          , 0 }, /* (0x3f)  63 */ 
    { j_lstore_1          , 0 }, /* (0x40)  64 */ 
    { j_lstore_2          , 0 }, /* (0x41)  65 */ 
    { j_lstore_3          , 0 }, /* (0x42)  66 */ 
    { j_fstore_0          , 0 }, /* (0x43)  67 */ 
    { j_fstore_1          , 0 }, /* (0x44)  68 */ 
    { j_fstore_2          , 0 }, /* (0x45)  69 */ 
    { j_fstore_3          , 0 }, /* (0x46)  70 */ 
    { j_dstore_0          , 0 }, /* (0x47)  71 */ 
    { j_dstore_1          , 0 }, /* (0x48)  72 */ 
    { j_dstore_2          , 0 }, /* (0x49)  73 */ 
    { j_dstore_3          , 0 }, /* (0x4a)  74 */ 
    { j_astore_0          , 0 }, /* (0x4b)  75 */ 
    { j_astore_1          , 0 }, /* (0x4c)  76 */ 
    { j_astore_2          , 0 }, /* (0x4d)  77 */ 
    { j_astore_3          , 0 }, /* (0x4e)  78 */ 
    { j_iastore           , 0 }, /* (0x4f)  79 */ 
    { j_lastore           , 0 }, /* (0x50)  80 */ 
    { j_fastore           , 0 }, /* (0x51)  81 */ 
    { j_dastore           , 0 }, /* (0x52)  82 */ 
    { j_aastore           , 0 }, /* (0x53)  83 */ 
    { j_bastore           , 0 }, /* (0x54)  84 */ 
    { j_castore           , 0 }, /* (0x55)  85 */ 
    { j_sastore           , 0 }, /* (0x56)  86 */ 
    { j_pop               , 0 }, /* (0x57)  87 */ 
    { j_pop2              , 0 }, /* (0x58)  88 */ 
    { j_dup               , 0 }, /* (0x59)  89 */ 
    { j_dup_x1            , 0 }, /* (0x5a)  90 */ 
    { j_dup_x2            , 0 }, /* (0x5b)  91 */ 
    { j_dup2              , 0 }, /* (0x5c)  92 */ 
    { j_dup2_x1           , 0 }, /* (0x5d)  93 */ 
    { j_dup2_x2           , 0 }, /* (0x5e)  94 */ 
    { j_swap              , 0 }, /* (0x5f)  95 */ 
    { j_iadd              , 0 }, /* (0x60)  96 */ 
    { j_ladd              , 0 }, /* (0x61)  97 */ 
    { j_fadd              , 0 }, /* (0x62)  98 */ 
    { j_dadd              , 0 }, /* (0x63)  99 */ 
    { j_isub              , 0 }, /* (0x64) 100 */ 
    { j_lsub              , 0 }, /* (0x65) 101 */ 
    { j_fsub              , 0 }, /* (0x66) 102 */ 
    { j_dsub              , 0 }, /* (0x67) 103 */ 
    { j_imul              , 0 }, /* (0x68) 104 */ 
    { j_lmul              , 0 }, /* (0x69) 105 */ 
    { j_fmul              , 0 }, /* (0x6a) 106 */ 
    { j_dmul              , 0 }, /* (0x6b) 107 */ 
    { j_idiv              , 0 }, /* (0x6c) 108 */ 
    { j_ldiv              , 0 }, /* (0x6d) 109 */ 
    { j_fdiv              , 0 }, /* (0x6e) 110 */ 
    { j_ddiv              , 0 }, /* (0x6f) 111 */ 
    { j_irem              , 0 }, /* (0x70) 112 */ 
    { j_lrem              , 0 }, /* (0x71) 113 */ 
    { j_frem              , 0 }, /* (0x72) 114 */ 
    { j_drem              , 0 }, /* (0x73) 115 */ 
    { j_ineg              , 0 }, /* (0x74) 116 */ 
    { j_lneg              , 0 }, /* (0x75) 117 */ 
    { j_fneg              , 0 }, /* (0x76) 118 */ 
    { j_dneg              , 0 }, /* (0x77) 119 */ 
    { j_ishl              , 0 }, /* (0x78) 120 */ 
    { j_lshl              , 0 }, /* (0x79) 121 */ 
    { j_ishr              , 0 }, /* (0x7a) 122 */ 
    { j_lshr              , 0 }, /* (0x7b) 123 */ 
    { j_iushr             , 0 }, /* (0x7c) 124 */ 
    { j_lushr             , 0 }, /* (0x7d) 125 */ 
    { j_iand              , 0 }, /* (0x7e) 126 */ 
    { j_land              , 0 }, /* (0x7f) 127 */ 
    { j_ior               , 0 }, /* (0x80) 128 */ 
    { j_lor               , 0 }, /* (0x81) 129 */ 
    { j_ixor              , 0 }, /* (0x82) 130 */ 
    { j_lxor              , 0 }, /* (0x83) 131 */ 
    { j_iinc              , 2 }, /* (0x84) 132 */ 
    { j_i2l               , 0 }, /* (0x85) 133 */ 
    { j_i2f               , 0 }, /* (0x86) 134 */ 
    { j_i2d               , 0 }, /* (0x87) 135 */ 
    { j_l2i               , 0 }, /* (0x88) 136 */ 
    { j_l2f               , 0 }, /* (0x89) 137 */ 
    { j_l2d               , 0 }, /* (0x8a) 138 */ 
    { j_f2i               , 0 }, /* (0x8b) 139 */ 
    { j_f2l               , 0 }, /* (0x8c) 140 */ 
    { j_f2d               , 0 }, /* (0x8d) 141 */ 
    { j_d2i               , 0 }, /* (0x8e) 142 */ 
    { j_d2l               , 0 }, /* (0x8f) 143 */ 
    { j_d2f               , 0 }, /* (0x90) 144 */ 
    { j_i2b               , 0 }, /* (0x91) 145 */ 
    { j_i2c               , 0 }, /* (0x92) 146 */ 
    { j_i2s               , 0 }, /* (0x93) 147 */ 
    { j_lcmp              , 0 }, /* (0x94) 148 */ 
    { j_fcmpl             , 0 }, /* (0x95) 149 */ 
    { j_fcmpg             , 0 }, /* (0x96) 150 */ 
    { j_dcmpl             , 0 }, /* (0x97) 151 */ 
    { j_dcmpg             , 0 }, /* (0x98) 152 */ 
    { j_ifeq              , 2 }, /* (0x99) 153 */ 
    { j_ifne              , 2 }, /* (0x9a) 154 */ 
    { j_iflt              , 2 }, /* (0x9b) 155 */ 
    { j_ifge              , 2 }, /* (0x9c) 156 */ 
    { j_ifgt              , 2 }, /* (0x9d) 157 */ 
    { j_ifle              , 2 }, /* (0x9e) 158 */ 
    { j_if_icmpeq         , 2 }, /* (0x9f) 159 */ 
    { j_if_icmpne         , 2 }, /* (0xa0) 160 */ 
    { j_if_icmplt         , 2 }, /* (0xa1) 161 */ 
    { j_if_icmpge         , 2 }, /* (0xa2) 162 */ 
    { j_if_icmpgt         , 2 }, /* (0xa3) 163 */ 
    { j_if_icmple         , 2 }, /* (0xa4) 164 */ 
    { j_if_acmpeq         , 0 }, /* (0xa5) 165 */ 
    { j_if_acmpne         , 0 }, /* (0xa6) 166 */ 
    { j_goto              , 2 }, /* (0xa7) 167 */ 
    { j_jsr               , 0 }, /* (0xa8) 168 */ 
    { j_ret               , 0 }, /* (0xa9) 169 */ 
    { j_tableswitch       , 0 }, /* (0xaa) 170 */ 
    { j_lookupswitch      , 0 }, /* (0xab) 171 */ 
    { j_ireturn           , 0 }, /* (0xac) 172 */ 
    { j_lreturn           , 0 }, /* (0xad) 173 */ 
    { j_freturn           , 0 }, /* (0xae) 174 */ 
    { j_dreturn           , 0 }, /* (0xaf) 175 */ 
    { j_areturn           , 0 }, /* (0xb0) 176 */ 
    { j_return            , 0 }, /* (0xb1) 177 */ 
    { j_getstatic         , 2 }, /* (0xb2) 178 */ 
    { j_putstatic         , 2 }, /* (0xb3) 179 */ 
    { j_getfield          , 2 }, /* (0xb4) 180 */ 
    { j_putfield          , 2 }, /* (0xb5) 181 */ 
    { j_invokevirtual     , 2}, /* (0xb6) 182 */ 
    { j_invokespecial     , 2 }, /* (0xb7) 183 */ 
    { j_invokestatic      , 2 }, /* (0xb8) 184 */ 
    { j_invokeinterface   , 4 }, /* (0xb9) 185 */ 
    { j_invokedynamic     , 2 }, /* (0xba) 186 */ 
    { j_new               , 2 }, /* (0xbb) 187 */ 
    { j_newarray          , 1 }, /* (0xbc) 188 */ 
    { j_anewarray         , 2 }, /* (0xbd) 189 */ 
    { j_arraylength       , 0 }, /* (0xbe) 190 */ 
    { j_athrow            , 0 }, /* (0xbf) 191 */ 
    { j_checkcast         , 2 }, /* (0xc0) 192 */ 
    { j_instanceof        , 0 }, /* (0xc1) 193 */ 
    { j_monitorenter      , 0 }, /* (0xc2) 194 */ 
    { j_monitorexit       , 0 }, /* (0xc3) 195 */ 
    { j_wide              , 0 }, /* (0xc4) 196 */ 
    { j_multianewarray    , 0 }, /* (0xc5) 197 */ 
    { j_ifnull            , 2 }, /* (0xc6) 198 */ 
    { j_ifnonnull         , 2 }, /* (0xc7) 199 */ 
    { j_goto_w            , 0 }, /* (0xc8) 200 */ 
    { j_jsr_w             , 0 }, /* (0xc9) 201 */ 
    { j_breakpoint        , 0 }, /* (0xca) 202 */ 
    { j_impdep1           , 0 }, /* (0xfe) 254 */ 
    { j_impdep2           , 0 }, /* (0xff) 255 */ 
};

 

#endif