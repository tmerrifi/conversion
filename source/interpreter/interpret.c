
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "udis86.h"

#include "bar.c"

typedef enum fun_table_kind {
  FUN_NONE,
  FUN_SIL, // low 8b
  FUN_AH, // high 8b
  FUN_SI, // low 16b
  FUN_ESI, // low 32b
  FUN_RSI, // 64b
  FUN_MMX0, // 64b MMX
  FUN_XMM0 // 128b SSE
} fun_table_kind_t;

fun_table_kind_t getFunTable(const ud_operand_t* src) {
  switch (src->type) {

    // for immediates, pick the right size and use the regular src-register fun table
  case UD_OP_IMM: {
    switch (src->size) {
    case  8: return FUN_SIL; 
    case 16: return FUN_SI; 
    case 32: return FUN_ESI; 
    case 64: return FUN_RSI; 
    default: return FUN_NONE;
    }
  }

  case UD_OP_REG: {

    switch (src->base) {
      /* high 8 bit GPRs */
    case UD_R_AH:
    case UD_R_CH:
    case UD_R_DH:
    case UD_R_BH:
      return FUN_AH;

      /* low 8 bit GPRs */
    case UD_R_AL:
    case UD_R_CL:
    case UD_R_DL:
    case UD_R_BL:
    case UD_R_SPL:
    case UD_R_BPL:
    case UD_R_SIL:
    case UD_R_DIL:
    case UD_R_R8B:
    case UD_R_R9B:
    case UD_R_R10B:
    case UD_R_R11B:
    case UD_R_R12B:
    case UD_R_R13B:
    case UD_R_R14B:
    case UD_R_R15B:
      return FUN_SIL;

      /* 16 bit GPRs */
    case UD_R_AX:
    case UD_R_CX:
    case UD_R_DX:
    case UD_R_BX:
    case UD_R_SP:
    case UD_R_BP:
    case UD_R_SI:
    case UD_R_DI:
    case UD_R_R8W:
    case UD_R_R9W:
    case UD_R_R10W:
    case UD_R_R11W:
    case UD_R_R12W:
    case UD_R_R13W:
    case UD_R_R14W:
    case UD_R_R15W:
      return FUN_SI;
  
      /* 32 bit GPRs */
    case UD_R_EAX:
    case UD_R_ECX:
    case UD_R_EDX:
    case UD_R_EBX:
    case UD_R_ESP:
    case UD_R_EBP:
    case UD_R_ESI:
    case UD_R_EDI:
    case UD_R_R8D:
    case UD_R_R9D:
    case UD_R_R10D:
    case UD_R_R11D:
    case UD_R_R12D:
    case UD_R_R13D:
    case UD_R_R14D:
    case UD_R_R15D:
      return FUN_ESI;
  
      /* 64 bit GPRs */
    case UD_R_RAX:
    case UD_R_RCX:
    case UD_R_RDX:
    case UD_R_RBX:
    case UD_R_RSP:
    case UD_R_RBP:
    case UD_R_RSI:
    case UD_R_RDI:
    case UD_R_R8:
    case UD_R_R9:
    case UD_R_R10:
    case UD_R_R11:
    case UD_R_R12:
    case UD_R_R13:
    case UD_R_R14:
    case UD_R_R15:
      return FUN_RSI;

      /* mmx registers */
    case UD_R_MM0:
    case UD_R_MM1:
    case UD_R_MM2:
    case UD_R_MM3:
    case UD_R_MM4:
    case UD_R_MM5:
    case UD_R_MM6:
    case UD_R_MM7:
      return FUN_MMX0;

      /* extended multimedia registers */
    case UD_R_XMM0:
    case UD_R_XMM1:
    case UD_R_XMM2:
    case UD_R_XMM3:
    case UD_R_XMM4:
    case UD_R_XMM5:
    case UD_R_XMM6:
    case UD_R_XMM7:
    case UD_R_XMM8:
    case UD_R_XMM9:
    case UD_R_XMM10:
    case UD_R_XMM11:
    case UD_R_XMM12:
    case UD_R_XMM13:
    case UD_R_XMM14:
    case UD_R_XMM15:
      return FUN_XMM0; 

    default:
      return FUN_NONE; // a register we don't handle
    }
  } // case UD_OP_REG

  default:
    return FUN_NONE; // an operand type we can't handle
  }
}

ud_type_t getCanonicalRegister(ud_type_t reg) {
  switch (reg) {

  case UD_R_AH:
  case UD_R_AL:
  case UD_R_AX:
  case UD_R_EAX:
    return UD_R_RAX;

  case UD_R_CH:
  case UD_R_CL:
  case UD_R_CX:
  case UD_R_ECX:
    return UD_R_RCX;

  case UD_R_DH:
  case UD_R_DL:
  case UD_R_DX:
  case UD_R_EDX:
    return UD_R_RDX;

  case UD_R_BH:
  case UD_R_BL:
  case UD_R_BX:
  case UD_R_EBX:
    return UD_R_RBX;

  case UD_R_SPL:
  case UD_R_SP:
  case UD_R_ESP:
    return UD_R_RSP;

  case UD_R_BPL:
  case UD_R_BP:
  case UD_R_EBP:
    return UD_R_RBP;

  case UD_R_SIL:
  case UD_R_SI:
  case UD_R_ESI:
    return UD_R_RSI;

  case UD_R_DIL:
  case UD_R_DI:
  case UD_R_EDI:
    return UD_R_RDI;

  case UD_R_R8B:
  case UD_R_R8W:
  case UD_R_R8D:
    return UD_R_R8;

  case UD_R_R9B:
  case UD_R_R9W:
  case UD_R_R9D:
    return UD_R_R9;

  case UD_R_R10B:
  case UD_R_R10W:
  case UD_R_R10D:
    return UD_R_R10;

  case UD_R_R11B:
  case UD_R_R11W:
  case UD_R_R11D:
    return UD_R_R11;

  case UD_R_R12B:
  case UD_R_R12W:
  case UD_R_R12D:
    return UD_R_R12;

  case UD_R_R13B:
  case UD_R_R13W:
  case UD_R_R13D:
    return UD_R_R13;

  case UD_R_R14B:
  case UD_R_R14W:
  case UD_R_R14D:
    return UD_R_R14;

  case UD_R_R15B:
  case UD_R_R15W:
  case UD_R_R15D:
    return UD_R_R15;
  
  /* canonical registers */
  case UD_R_RAX:
  case UD_R_RCX:
  case UD_R_RDX:
  case UD_R_RBX:
  case UD_R_RSP:
  case UD_R_RBP:
  case UD_R_RSI:
  case UD_R_RDI:
  case UD_R_R8:
  case UD_R_R9:
  case UD_R_R10:
  case UD_R_R11:
  case UD_R_R12:
  case UD_R_R13:
  case UD_R_R14:
  case UD_R_R15:
  case UD_R_MM0:
  case UD_R_MM1:
  case UD_R_MM2:
  case UD_R_MM3:
  case UD_R_MM4:
  case UD_R_MM5:
  case UD_R_MM6:
  case UD_R_MM7:
  case UD_R_XMM0:
  case UD_R_XMM1:
  case UD_R_XMM2:
  case UD_R_XMM3:
  case UD_R_XMM4:
  case UD_R_XMM5:
  case UD_R_XMM6:
  case UD_R_XMM7:
  case UD_R_XMM8:
  case UD_R_XMM9:
  case UD_R_XMM10:
  case UD_R_XMM11:
  case UD_R_XMM12:
  case UD_R_XMM13:
  case UD_R_XMM14:
  case UD_R_XMM15:
    return reg;

  default:
    return UD_NONE; // a register we don't handle
  }
}

uint8_t isComputeInsn(ud_mnemonic_code_t opcode) {
  return (UD_Iadd == opcode ||
          UD_Iand == opcode ||
          UD_Ior  == opcode ||
          UD_Isub == opcode ||
          UD_Isar == opcode ||
          UD_Ishl == opcode ||
          UD_Ishr == opcode); 
}

unsigned getNumOperands(ud_t* dis) {
  int i = 0;
  while (NULL != ud_insn_opr(dis, i)) {
    i++;
  }
  return i;
}

int main(int argc, char** argv) {

  //uint8_t INPUT_BYTES[] = {0x40, 0x00, 0x37}; // add %sil,(%rdi)
  uint8_t INPUT_BYTES[] = {0x88, 0x27}; // mov %ah,(%rdi)

  ud_t dis;
    
  ud_init(&dis);
  ud_set_input_buffer(&dis, INPUT_BYTES, sizeof(INPUT_BYTES));
  ud_set_mode(&dis, 64);
  ud_set_vendor(&dis, UD_VENDOR_INTEL);
  ud_set_syntax(&dis, UD_SYN_INTEL);
    
  unsigned lengthInBytes = ud_disassemble(&dis);
  if (0 == lengthInBytes) {
    printf("Decoded 0 bytes\n");
    return 1;
  }

  unsigned numOperands = getNumOperands(&dis);
  if (0 == numOperands || numOperands > 2) {
    printf("can't handle %u operands\n", numOperands);
    return 1;
  }

  // TODO: remove this once we handle SET insns
  if (numOperands != 2) {
    printf("can't handle %u operands\n", numOperands);
    return 1;
  }

  printf("\t%s\n", ud_insn_asm(&dis));

  // state used to decide which interpreter function to call

  uint64_t dummy; // for testing

  void* dstAddress = &dummy; // TODO: get this from interrupt handler
  uint64_t srcValue = 0;
  unsigned __int128 srcValue128b = 0;
  uint64_t* flags = &dummy; // TODO: point into user context
  ud_mnemonic_code_t opcode = 0;


  // get srcValue. Assume it's operand 1  
  const struct ud_operand* srcOp = ud_insn_opr(&dis, 1);
  assert(NULL != srcOp);

  opcode = dis.mnemonic;

  if (UD_OP_IMM == srcOp->type) {
    switch (srcOp->size) {
      // NB: code copied from https://github.com/vmt/udis86/blob/master/libudis86/decode.c#L472
      // 8-bit immediates are signed while others are unsigned?
    case  8: srcValue = srcOp->lval.sbyte;  break;
    case 16: srcValue = srcOp->lval.uword;  break;
    case 32: srcValue = srcOp->lval.udword; break;
    case 64: srcValue = srcOp->lval.uqword; break;
    default:
      // TODO: fail over to CoW
      printf("Invalid srcOp size: %d\n", srcOp->size);
      return 2;
    }

  } else if (UD_OP_REG == srcOp->type) { // source value is a register
    ud_type_t canonSrcReg = getCanonicalRegister(srcOp->base); 
    // TODO: read src reg from the user context
    // srcValue = ...; srcValue128b = ...;

  } else {
    printf("Can't handle srcOp type %u\n", srcOp->type);
    return 2;
  }

  if (opcode < 0 || opcode >= UD_Iaaa) {
    printf("opcode out-of-bounds: %u\n", opcode);
    return 2;
  }

  switch (getFunTable(srcOp)) {
  case FUN_SIL: {
    if (isComputeInsn(opcode)) {
      ComputeOpcode2FunTable_SIL[opcode](dstAddress, srcValue, flags);
    } else {
      NonComputeOpcode2FunTable_SIL[opcode](dstAddress, srcValue);
    }
    break;
  }
  case FUN_AH: {
    if (isComputeInsn(opcode)) {
      ComputeOpcode2FunTable_AH[opcode](dstAddress, srcValue, flags);
    } else {
      NonComputeOpcode2FunTable_AH[opcode](dstAddress, srcValue);
    }
    break;
  }
  case FUN_SI: {
    if (isComputeInsn(opcode)) {
      ComputeOpcode2FunTable_SI[opcode](dstAddress, srcValue, flags);
    } else {
      NonComputeOpcode2FunTable_SI[opcode](dstAddress, srcValue);
    }
    break;
  }
  case FUN_ESI: {
    if (isComputeInsn(opcode)) {
      ComputeOpcode2FunTable_ESI[opcode](dstAddress, srcValue, flags);
    } else {
      NonComputeOpcode2FunTable_ESI[opcode](dstAddress, srcValue);
    }
    break;
  }
  case FUN_RSI: {
    if (isComputeInsn(opcode)) {
      ComputeOpcode2FunTable_RSI[opcode](dstAddress, srcValue, flags);
    } else {
      NonComputeOpcode2FunTable_RSI[opcode](dstAddress, srcValue);
    }
    break;
  }
  case FUN_MMX0: {
    if (isComputeInsn(opcode)) {
      ComputeOpcode2FunTable_MMX0[opcode](dstAddress, srcValue, flags);
    } else {
      NonComputeOpcode2FunTable_MMX0[opcode](dstAddress, srcValue);
    }
    break;
  }
  case FUN_XMM0: {
    assert(!isComputeInsn(opcode));
    NonComputeOpcode2FunTable_XMM0[opcode](dstAddress, srcValue);
    break;
  }
  default:
    // TODO: fail over to CoW
    printf("Invalid fun table: %d\n", getFunTable(srcOp));
    return 2;
  }

  return 0;
}
