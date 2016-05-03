
#ifdef TEST_INTERPRETER
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#endif

#include "libudis86/extern.h"

#ifdef __KERNEL__
#include "linux/ptrace.h"
#else
// the kernel version of pt_regs has fields named differently than userland version, so we replicate the kernel version here
struct pt_regs {
  unsigned long r15;
  unsigned long r14;
  unsigned long r13;
  unsigned long r12;
  unsigned long bp;
  unsigned long bx;
  /* arguments: non interrupts/non tracing syscalls only save up to here*/
  unsigned long r11;
  unsigned long r10;
  unsigned long r9;
  unsigned long r8;
  unsigned long ax;
  unsigned long cx;
  unsigned long dx;
  unsigned long si;
  unsigned long di;
  unsigned long orig_ax;
  /* end of arguments */
  /* cpu exception frame or undefined */
  unsigned long ip;
  unsigned long cs;
  unsigned long flags;
  unsigned long sp;
  unsigned long ss;
  /* top of stack page */
};
#endif

#include "cv_store_interpreter_functions.h"
#include "createStoreInterpreterFunctions/cv_store_interpreter_functions.c"

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

  case UD_OP_CONST:
    // NB: I've only seen UD_OP_CONST with shift insns, and those require the
    // shift amount be passed via CL (which is held in the SIL entry)
    return FUN_SIL;
    
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

uint8_t isGPR(ud_type_t reg) {
  return (reg > UD_NONE && reg <= UD_R_R15);
}

uint8_t isSIMDreg(ud_type_t reg) {
  return (reg >= UD_R_MM0  && reg <= UD_R_XMM15);
}

uint8_t insnWritesFlags(ud_mnemonic_code_t opcode) {
  return (UD_Iadd == opcode ||
          UD_Iand == opcode ||
          UD_Ior  == opcode ||
          UD_Isub == opcode ||
          UD_Isar == opcode ||
          UD_Ishl == opcode ||
          UD_Ishr == opcode); 
}

uint8_t isOpcodeSET(ud_mnemonic_code_t opcode) {
  return (UD_Iseta == opcode ||
          UD_Isetae == opcode ||
          UD_Isetb == opcode ||
          UD_Isetbe == opcode ||
          UD_Isetg == opcode ||
          UD_Isetge == opcode ||
          UD_Isetl == opcode ||
          UD_Isetle == opcode ||
          UD_Isetno == opcode ||
          UD_Isetnp == opcode ||
          UD_Isetns == opcode ||
          UD_Isetnz == opcode ||
          UD_Iseto == opcode ||
          UD_Isetp == opcode ||
          UD_Isets == opcode ||
          UD_Isetz == opcode);
}

unsigned getNumOperands(ud_t* dis) {
  int i = 0;
  while (NULL != ud_insn_opr(dis, i)) {
    i++;
  }
  return i;
}

#ifdef TEST_INTERPRETER
ud_mnemonic_code_t IdentifiedOpcode = UD_Inone;
#endif

/* Perform the store (pointed to by bytes). Returns the number of bytes written
   by the store. If 0, the store could not be performed. */
int interpret(const uint8_t* bytes, const uint32_t bytesLength, void* dstAddress, struct pt_regs* context) {
#ifdef TEST_INTERPRETER
  IdentifiedOpcode = UD_Inone;
#endif

  ud_t dis;
    
  ud_init(&dis);
  ud_set_input_buffer(&dis, bytes, bytesLength);
  ud_set_mode(&dis, 64);
  ud_set_vendor(&dis, UD_VENDOR_INTEL);
  ud_set_syntax(&dis, UD_SYN_INTEL);
    
  unsigned lengthInBytes = ud_disassemble(&dis);
  if (0 == lengthInBytes) {
    printf("Decoded 0 bytes\n");
    return 0;
  }

  unsigned numOperands = getNumOperands(&dis);
  if (0 == numOperands || numOperands > 2) {
    printf("can't handle %u operands\n", numOperands);
    return 0;
  }

  //printf("\t%s\n", ud_insn_asm(&dis));

  // state used to decide which interpreter function to call

  uint64_t srcValue = 0;
  uint64_t* flags = &(context->flags);
  ud_mnemonic_code_t opcode = dis.mnemonic;

#ifdef TEST_INTERPRETER
  IdentifiedOpcode = opcode;
#endif

  if (1 == numOperands) {
    if (isOpcodeSET(opcode)) {
      if (opcode < 0 || opcode > CV_LAST_VALID_OPCODE) {
        printf("single-operand opcode out of bounds %u", opcode);
        return 0;
      }
      NoWriteFlagsOpcode2FunTable_SIL[opcode](dstAddress, *flags);
      return 1; // SET insns always write 1 byte
    } else {
      printf("Can't handle 1-operand insn\n");
      return 0;
    }
  }

  // get srcValue which is operand 1
  const struct ud_operand* srcOp = ud_insn_opr(&dis, 1);
  assert(NULL != srcOp);

  if (UD_OP_CONST == srcOp->type) {
    // from decode.c:763
    srcValue = srcOp->lval.udword;

  } else if (UD_OP_IMM == srcOp->type) {
    switch (srcOp->size) {
      // NB: code copied from https://github.com/vmt/udis86/blob/master/libudis86/decode.c#L472
      // 8-bit immediates are signed while others are unsigned?
    case  8: srcValue = srcOp->lval.sbyte;  break;
    case 16: srcValue = srcOp->lval.uword;  break;
    case 32: srcValue = srcOp->lval.udword; break;
    case 64: srcValue = srcOp->lval.uqword; break;
    default:
      printf("Invalid srcOp size: %d\n", srcOp->size);
      return 0;
    }

  } else if (UD_OP_REG == srcOp->type) { // source value is a register
    ud_type_t canonSrcReg = getCanonicalRegister(srcOp->base);
    if (isGPR(canonSrcReg)) {
      // read src reg from the user context
      switch (canonSrcReg) {
      case UD_R_RAX:
        srcValue = context->ax;
        break;
      case UD_R_RCX:
        srcValue = context->cx;
        break;
      case UD_R_RDX:
        srcValue = context->dx;
        break;
      case UD_R_RBX:
        srcValue = context->bx;
        break;
      case UD_R_RSP:
        srcValue = context->sp;
        break;
      case UD_R_RBP:
        srcValue = context->bp;
        break;
      case UD_R_RSI:
        srcValue = context->si;
        break;
      case UD_R_RDI:
        srcValue = context->di;
        break;
      case UD_R_R8:
        srcValue = context->r8;
        break;
      case UD_R_R9:
        srcValue = context->r9;
        break;
      case UD_R_R10:
        srcValue = context->r10;
        break;
      case UD_R_R11:
        srcValue = context->r11;
        break;
      case UD_R_R12:
        srcValue = context->r12;
        break;
      case UD_R_R13:
        srcValue = context->r13;
        break;
      case UD_R_R14:
        srcValue = context->r14;
        break;
      case UD_R_R15:
        srcValue = context->r15;
        break;
      default:
        printf("Invalid GPR source register %u", canonSrcReg);
        return 0;
      }

    } else if (isSIMDreg(canonSrcReg)) {
      // SIMD regs don't need to be read from context; they're already in the register file
    } else {
      printf("Invalid source register %u", canonSrcReg);
      return 0;
    }

  } else {
    printf("Can't handle srcOp type %u\n", srcOp->type);
    return 0;
  }

  if (opcode < 0 || opcode > CV_LAST_VALID_OPCODE) {
    printf("opcode out-of-bounds: %u\n", opcode);
    return 0;
  }

  const struct ud_operand* dstOp = ud_insn_opr(&dis, 0);
  assert(NULL != dstOp);
  assert(UD_OP_MEM == dstOp->type); 
  const unsigned storeWidthBytes = dstOp->size / 8; // convert bits => bytes

  movInsnFun movFun = NULL;
  writeFlagsInsnFun flagsFun = NULL;

  switch (getFunTable(srcOp)) {
  case FUN_SIL: {
    movFun = NoWriteFlagsOpcode2FunTable_SIL[opcode];
    flagsFun = WriteFlagsOpcode2FunTable_SIL[opcode];
    break;
  }
  case FUN_AH: {
    movFun = NoWriteFlagsOpcode2FunTable_AH[opcode];
    flagsFun = WriteFlagsOpcode2FunTable_AH[opcode];
    break;
  }
  case FUN_SI: {
    movFun = NoWriteFlagsOpcode2FunTable_SI[opcode];
    flagsFun = WriteFlagsOpcode2FunTable_SI[opcode];
    break;
  }
  case FUN_ESI: {
    movFun = NoWriteFlagsOpcode2FunTable_ESI[opcode];
    flagsFun = WriteFlagsOpcode2FunTable_ESI[opcode];
    break;
  }
  case FUN_RSI: {
    movFun = NoWriteFlagsOpcode2FunTable_RSI[opcode];
    flagsFun = WriteFlagsOpcode2FunTable_RSI[opcode];
    break;
  }
  case FUN_MMX0: 
  case FUN_XMM0: {
    simdMovInsnFun* regTable = SIMDOpcode2RegTable[opcode];
    if (NULL == regTable) {
      printf("Invalid SIMD opcode %u", opcode);
      return 0;
    }
    ud_type_t srcReg = getCanonicalRegister(srcOp->base);
    if (srcReg < UD_R_MM0 || srcReg > UD_R_XMM15) {
      printf("Invalid SIMD src register %u", srcReg);
      return 0;
    }
    unsigned index = srcReg - UD_R_MM0; // TODO: HORRIBLE HACK!!
    simdMovInsnFun fun = regTable[index];
    if (NULL == fun) {
      printf("No function to interpret SIMD src register %u", index);
      return 0;
    }
    fun(dstAddress);
    return storeWidthBytes;
  }
  default:
    printf("Invalid fun table: %d\n", getFunTable(srcOp));
    return 0;
  }

  // non-SIMD insn
  if (opcode < 0 || opcode > CV_LAST_GPR_OPCODE) {
    printf("OOB GPR opcode %u", opcode);
    return 0;
  }

  if (insnWritesFlags(opcode)) {
    if (NULL == flagsFun) {
      printf("No function to interpret flag-writing opcode %u", opcode);
      return 0;
    }
    flagsFun(dstAddress, srcValue, flags);

  } else {
    if (NULL == movFun) {
      printf("No function to interpret non-flag-writing opcode %u", opcode);
      return 0;
    }
    movFun(dstAddress, srcValue);
  }

  return storeWidthBytes;
}

#ifndef __KERNEL__
int main(int argc, char** argv) {

  verifyOpcodesAndRegisters();

  uint8_t INPUT_BYTES[1][4] = {
    {0x67,0xd0,0x3f,0x0} // sarb $0x1, (%edi)
    /* {0x0f, 0x92, 0x07, 0x90}, // setb (%rdi) 3B */
    /* {0x88, 0x27, 0x90, 0x90}, // mov %ah,(%rdi) 2B */
    /* {0x40, 0x00, 0x37, 0x90}, // add %sil,(%rdi) 3B */
    /* {0x66, 0x0f, 0x7e, 0x07}  // movd %xmm0,(%rdi) 4B */
  };

  unsigned __int128 dummy; // for testing
  
  struct pt_regs regs;

  for (int i = 0; i < sizeof(INPUT_BYTES) / sizeof(INPUT_BYTES[0]); i++) {
    regs.flags = 0x202;
    int bw = interpret(INPUT_BYTES[i], sizeof(INPUT_BYTES[0]), &dummy, &regs);
    assert(1 == bw);
  }

#ifdef TEST_INTERPRETER
  unsigned totalTests = 0, testsPassed = 0, testsFailed = 0;

  for (unsigned i = 0; i < NUM_TEST_INSNS; i++) {
    regs.flags = 0x202;
    int bytesWritten = interpret(TEST_INSNS[i].bytes, MAX_INSN_BYTES, &dummy, &regs);
    totalTests++;
    if (0 == bytesWritten) {
      printf("FAILURE couldn't interpret test insn #%u (%s), expected opcode %u\n", i, TEST_INSNS[i].disasm, TEST_INSNS[i].expectedOpcode);
      continue;
    }
    if (TEST_INSNS[i].expectedOpcode != IdentifiedOpcode) {
      printf("FAILURE wrong opcode identified for test insn #%u (%s), expected opcode %u but got %u\n", 
             i, TEST_INSNS[i].disasm, TEST_INSNS[i].expectedOpcode, IdentifiedOpcode);
      continue;
    }
    if (TEST_INSNS[i].storeWidthBytes != bytesWritten) {
      printf("FAILURE wrong opcode identified for test insn #%u (%s), expected %u bytes written but actually wrote %u\n", 
             i, TEST_INSNS[i].disasm, TEST_INSNS[i].storeWidthBytes, bytesWritten);
      continue;
    }

    testsPassed++;
  }

  testsFailed = totalTests - testsPassed;
  printf("Ran %u tests: %u passed and %u failed.\n", totalTests, testsPassed, testsFailed);
#endif

  return 0;
}
#endif
