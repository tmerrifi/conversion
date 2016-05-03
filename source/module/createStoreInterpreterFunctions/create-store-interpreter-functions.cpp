extern "C" {
#include "xed-interface.h"
#include "xed-examples-util.h"
}
//#include "xed-enc-lang.H"
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include <boost/algorithm/string.hpp>

using namespace std;

const char* ASM_NEWLINE = "\\n\\t";

/* NB: GPR_OPCODES and SIMD_OPCODES are "parsed" by the udis86 build scripts
   to ensure that udis86's opcode ordering is identical to the ordering below
   (for these opcodes). No comments are permitted in these arrays as they will
   confuse this (very stupid) parser.
   
   This array should contain only opcodes that operate on general-purpose
   registers (GPRs).
 */
const xed_iclass_enum_t GPR_OPCODES[] = {
  XED_ICLASS_SETB,
  XED_ICLASS_SETNZ,

  XED_ICLASS_MOV,

  XED_ICLASS_ADD,
  XED_ICLASS_AND,
  XED_ICLASS_OR,
  XED_ICLASS_SUB,
  XED_ICLASS_SAR,
  XED_ICLASS_SHL,
  XED_ICLASS_SHR
};

const int NUM_GPR_OPCODES = sizeof(GPR_OPCODES) / sizeof(GPR_OPCODES[0]);

/* This array should contain only opcodes that operate on SIMD registers such as
   MMX or SSE registers.
*/
const xed_iclass_enum_t SIMD_OPCODES[] = { 
  XED_ICLASS_MOVD,
  XED_ICLASS_MOVSS,
  XED_ICLASS_MOVQ,
  XED_ICLASS_MOVUPS,
  XED_ICLASS_MOVUPD,
  XED_ICLASS_MOVLPS,
  XED_ICLASS_MOVLPD,
  XED_ICLASS_MOVHPS,
  XED_ICLASS_MOVHPD,
  XED_ICLASS_MOVAPS,
  XED_ICLASS_MOVAPD,
  XED_ICLASS_MOVDQA,
  XED_ICLASS_MOVDQU
};
/* these are AVX opcodes, which our machines can't execute
  XED_ICLASS_VMOVUPS,
  XED_ICLASS_VMOVUPD,
  XED_ICLASS_VMOVSS,
  XED_ICLASS_VMOVSD,
  XED_ICLASS_VMOVLPS,
  XED_ICLASS_VMOVLPD,
  XED_ICLASS_VMOVHPS,
  XED_ICLASS_VMOVHPD,
  XED_ICLASS_VMOVAPS,
  XED_ICLASS_VMOVAPD,
  XED_ICLASS_VMOVDQA,
  XED_ICLASS_VMOVDQU
*/

  //XED_ICLASS_MOVSD // TODO: doesn't generate any valid code for some reason...
const int NUM_SIMD_OPCODES = sizeof(SIMD_OPCODES) / sizeof(SIMD_OPCODES[0]);

// NB: use RSI for the src value when possible as it's the 2nd arg in x86-64 calling conventions
const xed_reg_enum_t REGISTERS[] = {
  XED_REG_SIL, // low 8b
  XED_REG_AH, // high 8b, there's no "SH" register so have to use AH instead
  XED_REG_SI, // low 16b
  XED_REG_ESI, // low 32b
  XED_REG_RSI, // 64b

  // 64b MMX
  XED_REG_MMX0, 
  XED_REG_MMX1, 
  XED_REG_MMX2, 
  XED_REG_MMX3, 
  XED_REG_MMX4, 
  XED_REG_MMX5, 
  XED_REG_MMX6,
  XED_REG_MMX7,  

  // 128b SSE
  XED_REG_XMM0,
  XED_REG_XMM1,
  XED_REG_XMM2,
  XED_REG_XMM3,
  XED_REG_XMM4,
  XED_REG_XMM5,
  XED_REG_XMM6,
  XED_REG_XMM7,
  XED_REG_XMM8,
  XED_REG_XMM9,
  XED_REG_XMM10,
  XED_REG_XMM11,
  XED_REG_XMM12,
  XED_REG_XMM13,
  XED_REG_XMM14,
  XED_REG_XMM15

  /* NB: there are no AVX instructions on our target platform (Nehalem), so we
     leave them out for now. */
  // XED_REG_YMM0, // 256b AVX 
};
const int NUM_REGISTERS = sizeof(REGISTERS) / sizeof(REGISTERS[0]);

const int FIRST_SIMD_REGISTER_INDEX() {
  for (int i = 0; i < NUM_REGISTERS; i++) {
    if (XED_REG_MMX0 == REGISTERS[i]) return i;
  }
  assert(false);
}


bool generateInsn(xed_encoder_instruction_t* xei, xed_state_t* dstate, string& insnAsm);
void generateLUTs();
void generateVerify();
void generateTests();

bool isOpcodeSET(xed_iclass_enum_t opcode) {
  return (XED_ICLASS_SETB == opcode ||
          XED_ICLASS_SETBE == opcode ||
          XED_ICLASS_SETL == opcode ||
          XED_ICLASS_SETLE == opcode ||
          XED_ICLASS_SETNB == opcode ||
          XED_ICLASS_SETNBE == opcode ||
          XED_ICLASS_SETNL == opcode ||
          XED_ICLASS_SETNLE == opcode ||
          XED_ICLASS_SETNO == opcode ||
          XED_ICLASS_SETNP == opcode ||
          XED_ICLASS_SETNS == opcode ||
          XED_ICLASS_SETNZ == opcode ||
          XED_ICLASS_SETO == opcode ||
          XED_ICLASS_SETP == opcode ||
          XED_ICLASS_SETS == opcode ||
          XED_ICLASS_SETZ == opcode);
}

bool isOpcodeShift(xed_iclass_enum_t opcode) {
  return (XED_ICLASS_SAR == opcode ||
          XED_ICLASS_SHL == opcode ||
          XED_ICLASS_SHR == opcode);
}

bool opcodeWritesFlags(xed_iclass_enum_t opcode) {
  return (XED_ICLASS_ADD == opcode ||
          XED_ICLASS_AND == opcode ||
          XED_ICLASS_OR == opcode ||
          XED_ICLASS_SUB == opcode ||
          XED_ICLASS_SAR == opcode ||
          XED_ICLASS_SHL == opcode ||
          XED_ICLASS_SHR == opcode);
}

string makeInsnFunName(xed_iclass_enum_t opcode, xed_reg_enum_t srcReg) {
  string funName = "";

  if (isOpcodeSET(opcode)) {
    srcReg = XED_REG_FLAGS;
  } else if (XED_REG_SIL == srcReg && isOpcodeShift(opcode)) {
    srcReg = XED_REG_CL;    
  }

  funName += xed_iclass_enum_t2str(opcode);
  funName += "_";
  funName += xed_reg_enum_t2str(srcReg);
  return funName;
}

unordered_map<string,int> AllFunctions;

bool isGprOpcode(xed_iclass_enum_t opcode) {
  return (opcodeWritesFlags(opcode) || isOpcodeSET(opcode) || XED_ICLASS_MOV == opcode);
}

string udis86MnemonicNameOfXedIclass(xed_iclass_enum_t opcode) {
    string op = xed_iclass_enum_t2str(opcode);
    boost::algorithm::to_lower(op);
    return "UD_I" + op;
}


void verify() {
  // ensure that opcode arrays have the expected contents
  for (int opi = 0; opi < NUM_GPR_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = GPR_OPCODES[opi];
    assert(isGprOpcode(opcode));
  }
  for (int opi = 0; opi < NUM_SIMD_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = SIMD_OPCODES[opi];
    assert(!isGprOpcode(opcode));
  }
}

int main(int argc, char** argv) {

  xed_tables_init();

  verify();

  xed_state_t dstate;
  xed_state_zero(&dstate);
  dstate.mmode=XED_MACHINE_MODE_LONG_64;
  dstate.stack_addr_width=XED_ADDRESS_WIDTH_64b;
  //dstate.mmode=XED_MACHINE_MODE_LEGACY_32;
  //dstate.stack_addr_width=XED_ADDRESS_WIDTH_32b;

  cout << "// AUTO-GENERATED FILE - DO NOT EDIT!!" << endl << endl;
  cout << "#ifdef TEST_INTERPRETER" << endl;
  cout << "#include <stdint.h>" << endl;
  cout << "#include <assert.h>" << endl;
  cout << "#include \"libudis86/extern.h\"" << endl << endl;
  cout << "#endif" << endl;

  cout << "#define CV_LAST_GPR_OPCODE " << (NUM_GPR_OPCODES - 1) << endl;
  cout << "#define CV_LAST_SIMD_OPCODE " << (NUM_GPR_OPCODES + NUM_SIMD_OPCODES - 1) << endl;
  cout << "#define CV_LAST_VALID_OPCODE " << (NUM_GPR_OPCODES + NUM_SIMD_OPCODES - 1) << endl << endl; 

  for (int opi = 0; opi < NUM_GPR_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = GPR_OPCODES[opi];

    // SET* insns have only FLAGS as a source register
    if (isOpcodeSET(opcode)) {
      xed_encoder_instruction_t xei; 
      // NB: use RDI for the dst addr as it holds the 1st arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RDI, 8);
      xed_inst1(&xei, dstate, opcode, 0, kwDst);

      const string funName = makeInsnFunName(opcode, XED_REG_FLAGS); 
      cout << "void " << funName << "(void* dstAddress, uint64_t flags) { ";
      AllFunctions.insert( {{funName,1}} );

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        cerr << " ERROR generating code for SET opcode:" << xed_iclass_enum_t2str(opcode) << endl;

        // this insnFun should never get called
        //cout << " assert(0); }" << endl;
        assert(false);
        return 1;
      }

      cout << endl;
      cout << " __asm__(\"push %%rsi" << ASM_NEWLINE << "\"" << endl;
      cout << "         \"popf" << ASM_NEWLINE << "\"" << endl;
      cout << "         \"" << insnAsm << ASM_NEWLINE << "\"" << endl;
      cout << "         : /*no output registers*/" << endl;
      cout << "         : \"D\"(dstAddress), \"S\"(flags) /*input registers*/" << endl;
      cout << "         : /*no clobbered registers*/" << endl;
      cout << "         );" << endl;

      cout << "}" << endl << endl;
      
      continue;
    }

    bool madeCode = false;

    if (opcodeWritesFlags(opcode)) {
      for (int regi = 0; regi < NUM_REGISTERS; regi++) {
        xed_reg_enum_t srcReg = REGISTERS[regi];

        xed_uint32_t srcRegWidthBits = xed_get_register_width_bits64(srcReg);
      
        if (XED_REG_SIL == srcReg && isOpcodeShift(opcode)) {
          // shift insns require the shift amount be placed in CL
          srcReg = XED_REG_CL;
          srcRegWidthBits = 8;
        }

        // NB: use RDI for the dest addr as it holds the 1st arg in x86-64 calling conventions
        xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RDI, srcRegWidthBits);
        xed_encoder_operand_t kwSrc = xed_reg(srcReg);
        
        xed_encoder_instruction_t xei; 

        // two-operand insn
        xed_inst2(&xei, dstate, opcode, srcRegWidthBits, kwDst, kwSrc); 
        
        string insnAsm = "";
        if (!generateInsn(&xei, &dstate, insnAsm)) {
          //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << " srcReg:" << xed_reg_enum_t2str(srcReg) << endl;
          continue;
        }
        // NB: we don't support FLAGS-using insns with SIMD registers, and I don't believe there are any
        assert(xed_reg_class(srcReg) != XED_REG_CLASS_MMX &&
               xed_reg_class(srcReg) != XED_REG_CLASS_XMM);

        const string funName = makeInsnFunName(opcode, srcReg);
        cout << "void " << funName << "(void* dstAddress, uint64_t srcValue, unsigned long * flags) {" << endl;
        AllFunctions.insert( {{funName,1}} );

        string srcRegCanonicalName = string(xed_reg_enum_t2str(srcReg));
        if (xed_get_register_width_bits64(srcReg) < 64) { // canonicalize to 64-bit registers (or xmm, ymm)
          srcRegCanonicalName = string(xed_reg_enum_t2str(xed_get_largest_enclosing_register(srcReg)));
        }
        boost::algorithm::to_lower(srcRegCanonicalName);

        cout << " __asm__(\"push %2" << ASM_NEWLINE << "\"" << endl;
        cout << "         \"popf" << ASM_NEWLINE << "\"" << endl;
        cout << "         \"" << insnAsm << ASM_NEWLINE << "\"" << endl;
        cout << "         \"pushf" << ASM_NEWLINE << "\"" << endl;
        cout << "         \"pop %0" << ASM_NEWLINE << "\"" << endl;
        cout << "         : \"=r\"(*flags) /*output registers*/" << endl;
        cout << "         : \"D\"(dstAddress), \"r\"(*flags), \"" << srcRegCanonicalName << "\"(srcValue) /*input registers*/" << endl;
        cout << "         : /*no clobbered registers*/" << endl;
        cout << "         );" << endl;
        
        cout << "}" << endl << endl;
        madeCode = true;
        
      } // end register loop
      
      continue;
    } // end if insn sets FLAGS

    // STORES FROM A REGISTER

    for (int regi = 0; regi < NUM_REGISTERS; regi++) {
      const xed_reg_enum_t srcReg = REGISTERS[regi];
      const xed_uint32_t srcRegWidthBits = xed_get_register_width_bits64(srcReg);

      assert(!isOpcodeShift(opcode));

      // NB: use RDI for the dest addr as it holds the 1st arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RDI, srcRegWidthBits);
      string dstAddrReg = "D";
      xed_encoder_operand_t kwSrc = xed_reg(srcReg);

      xed_encoder_instruction_t xei; 

      // two-operand insn
      xed_inst2(&xei, dstate, opcode, srcRegWidthBits, kwDst, kwSrc); 

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << " srcReg:" << xed_reg_enum_t2str(srcReg) << endl;
        continue;
      }

      const string funName = makeInsnFunName(opcode, srcReg);
      cout << "void " << funName << "(void* dstAddress, uint64_t srcValue) {" << endl;
      AllFunctions.insert( {{funName,1}} );

      string srcRegCanonicalName = string(xed_reg_enum_t2str(srcReg));
      if (xed_get_register_width_bits64(srcReg) < 64) { // canonicalize to 64-bit registers
        srcRegCanonicalName = string(xed_reg_enum_t2str(xed_get_largest_enclosing_register(srcReg)));
      }
      boost::algorithm::to_lower(srcRegCanonicalName);

      cout << " __asm__(\"" << insnAsm << ASM_NEWLINE << "\"" << endl;
      cout << "         : /*no output registers*/" << endl;
      cout << "         : \"" << dstAddrReg << "\"(dstAddress), \"" << srcRegCanonicalName << "\"(srcValue) /*input registers*/" << endl;
      cout << "         : /*no clobbered registers*/" << endl;
      cout << "         );" << endl;

      cout << "}" << endl << endl;
      madeCode = true;      
    }

    if (!madeCode) {
      cerr << "ERROR: did not generate any code for opcode: " << xed_iclass_enum_t2str(opcode) << endl;
      exit(1);
    }

    // NB: stores from an immediate just pass the src value like any other store value
    // TODO: may need to handle various immediate formats, signed vs unsigned, sign extension, etc in the decoder?

  } // loop over GPR opcodes

  // SIMD STORES FROM A REGISTER

  for (int opi = 0; opi < NUM_SIMD_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = SIMD_OPCODES[opi];
    bool madeCode = false;

    for (int regi = 0; regi < NUM_REGISTERS; regi++) {
      const xed_reg_enum_t srcReg = REGISTERS[regi];
      xed_uint32_t srcRegWidthBits = xed_get_register_width_bits64(srcReg);

      assert(!isOpcodeShift(opcode));
      
      if (XED_ICLASS_MOVSS == opcode ||
          XED_ICLASS_MOVD == opcode ||
          XED_ICLASS_VMOVSS == opcode) {
        // move one float
        srcRegWidthBits = 32;

      } else if (XED_ICLASS_MOVSD == opcode ||
                 XED_ICLASS_MOVQ == opcode ||
                 XED_ICLASS_VMOVSD == opcode ||
                 XED_ICLASS_MOVLPS == opcode ||
                 XED_ICLASS_VMOVLPS == opcode ||
                 XED_ICLASS_MOVLPD == opcode ||
                 XED_ICLASS_VMOVLPD == opcode ||
                 XED_ICLASS_MOVHPS == opcode ||
                 XED_ICLASS_MOVHPD == opcode ||
                 XED_ICLASS_VMOVHPS == opcode ||
                 XED_ICLASS_VMOVHPD == opcode) {
        // move two floats or one double
        srcRegWidthBits = 64;

      }

      // NB: use RDI for the dest addr as it holds the 1st arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RDI, srcRegWidthBits);
      string dstAddrReg = "D";
      xed_encoder_operand_t kwSrc = xed_reg(srcReg);

      xed_encoder_instruction_t xei; 

      // two-operand insn
      xed_inst2(&xei, dstate, opcode, srcRegWidthBits, kwDst, kwSrc); 

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << " srcReg:" << xed_reg_enum_t2str(srcReg) << endl;
        continue;
      }

      assert(xed_reg_class(srcReg) == XED_REG_CLASS_MMX ||
             xed_reg_class(srcReg) == XED_REG_CLASS_XMM);

      const string funName = makeInsnFunName(opcode, srcReg);
      // MMX/XMM registers aren't clobbered by the kernel, so the value to be
      // stored is still present in the source register
      cout << "void " << funName << "(void* dstAddress) {" << endl;
      AllFunctions.insert( {{funName,1}} );

      cout << " __asm__(\"" << insnAsm << ASM_NEWLINE << "\"" << endl;
      cout << "         : /*no output registers*/" << endl;
      cout << "         : \"" << dstAddrReg << "\"(dstAddress) /*input registers*/" << endl;
      cout << "         : /*no clobbered registers*/" << endl;
      cout << "         );" << endl;

      cout << "}" << endl << endl;
      madeCode = true;
    }

    if (!madeCode) {
      cerr << "ERROR: did not generate any code for opcode: " << xed_iclass_enum_t2str(opcode) << endl;
      exit(1);
    }

  } // loop over SIMD opcodes
  
  generateLUTs();
  generateVerify();
  generateTests();

}

void generateLUTs() {

  // typedefs
  cout << endl << "typedef void (*movInsnFun)(void* dstAddress, uint64_t srcValue);" << endl << endl;
  cout << endl << "typedef void (*simdMovInsnFun)(void* dstAddress);" << endl << endl;
  cout << endl << "typedef void (*writeFlagsInsnFun)(void* dstAddress, uint64_t srcValue, unsigned long* flags);" << endl << endl;

  const string nullPtr = "NULL";

  // GPR opcode2fun tables
  for (int regi = 0; regi < NUM_REGISTERS; regi++) {
    const xed_reg_enum_t srcReg = REGISTERS[regi];

    if (xed_reg_class(srcReg) == XED_REG_CLASS_MMX ||
        xed_reg_class(srcReg) == XED_REG_CLASS_XMM) {
      continue;
    }

    string funPtrName = "movInsnFun";

    // no-write-FLAGS insn table

    cout << funPtrName << " NoWriteFlagsOpcode2FunTable_" << xed_reg_enum_t2str(srcReg) << "[] = {" << endl;

    for (int opi = 0; opi < NUM_GPR_OPCODES; opi++) {
      const xed_iclass_enum_t opcode = GPR_OPCODES[opi];
      string funName = makeInsnFunName(opcode, srcReg);
      if (opcodeWritesFlags(opcode) || 
          (xed_reg_class(srcReg) == XED_REG_CLASS_XMM && isOpcodeSET(opcode)) ||
          AllFunctions.count(funName) == 0) {
        funName = nullPtr;
      }
      cout << " " << funName << "," << endl;
    }

    cout << " " << nullPtr << endl;
    cout << "};" << endl << endl;

    // write-FLAGS insn table

    funPtrName = "writeFlagsInsnFun";
    cout << funPtrName << " WriteFlagsOpcode2FunTable_" << xed_reg_enum_t2str(srcReg) << "[] = {" << endl;

    for (int opi = 0; opi < NUM_GPR_OPCODES; opi++) {
      const xed_iclass_enum_t opcode = GPR_OPCODES[opi];
      string funName = makeInsnFunName(opcode, srcReg);
      if (!opcodeWritesFlags(opcode) || AllFunctions.count(funName) == 0) {
        funName = nullPtr;
      }
      cout << " " << funName << "," << endl;      
    }

    cout << " " << nullPtr << endl;
    cout << "};" << endl << endl;    

  } // loop over GPRs


  // SIMD reg2fun tables

  const string funPtrName = "simdMovInsnFun";

  for (int opi = 0; opi < NUM_SIMD_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = SIMD_OPCODES[opi];

    cout << funPtrName << " SIMDReg2FunTable_" << xed_iclass_enum_t2str(opcode) << "[] = {" << endl;

    for (int regi = FIRST_SIMD_REGISTER_INDEX(); regi < NUM_REGISTERS; regi++) {
      const xed_reg_enum_t srcReg = REGISTERS[regi];
      string funName = makeInsnFunName(opcode, srcReg);
      
      if ((xed_reg_class(srcReg) != XED_REG_CLASS_MMX &&
           xed_reg_class(srcReg) != XED_REG_CLASS_XMM) ||
          AllFunctions.count(funName) == 0) {
        funName = nullPtr;
      }
      cout << " " << funName << "," << endl;
    }

    cout << " " << nullPtr << endl;
    cout << "};" << endl << endl;
  }

  // SIMD opcode2reg tables

  cout << funPtrName << "* SIMDOpcode2RegTable[] = {" << endl;

  for (int opi = 0; opi < NUM_GPR_OPCODES; opi++) {
    cout << " " << nullPtr << "," << endl;    
  } 
  for (int opi = 0; opi < NUM_SIMD_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = SIMD_OPCODES[opi];
    const string tableName = string("SIMDReg2FunTable_") + xed_iclass_enum_t2str(opcode);
    cout << " " << tableName << "," << endl;
  }
  
  cout << " " << nullPtr << endl;
  cout << "};" << endl << endl;

}

void generateVerify() {
  cout << "void verifyOpcodesAndRegisters() {" << endl;

  cout << "// verify opcodes" << endl;
  int x = 0;
  for (int i = 0; i < NUM_GPR_OPCODES; i++, x++) {
    const xed_iclass_enum_t opcode = GPR_OPCODES[i];
    string op = udis86MnemonicNameOfXedIclass(opcode);
    cout << " assert(" << x << " == " << op << ");" << endl;
  }
  for (int i = 0; i < NUM_SIMD_OPCODES; i++, x++) {
    const xed_iclass_enum_t opcode = SIMD_OPCODES[i];
    string op = udis86MnemonicNameOfXedIclass(opcode);
    cout << " assert(" << x << " == " << op << ");" << endl;
  }

  cout << "// verify register mapping" << endl;
  int r = 0;
  for (int mm = 0; mm < 8; mm++, r++) { // MMX registers
    cout << " assert(" << r << " == (UD_R_MM" << mm << " - UD_R_MM0));" << endl;
  }
  for (int xmm = 0; xmm < 16; xmm++, r++) { // XMM registers
    cout << " assert(" << r << " == (UD_R_XMM" << xmm << " - UD_R_MM0));" << endl;
  }

  cout << "}" << endl;
}

unsigned NumTestInsns = 0;

unsigned generateTestInsn(const xed_iclass_enum_t opcode, const xed_encoder_operand_t dstOp, 
                          const xed_encoder_operand_t srcOp, const uint32_t srcRegWidthBits) {
  xed_state_t dstate;
  xed_state_zero(&dstate);
  dstate.mmode = XED_MACHINE_MODE_LONG_64;
  dstate.stack_addr_width = XED_ADDRESS_WIDTH_64b;
  
  xed_encoder_instruction_t xei; 
  
  // two-operand insn
  xed_inst2(&xei, dstate, opcode, srcRegWidthBits, dstOp, srcOp);
  
  xed_error_enum_t xed_error = XED_ERROR_NONE;
  xed_encoder_request_t enc_req;

  xed_encoder_request_zero_set_mode(&enc_req, &dstate);
  xed_bool_t convert_ok = xed_convert_to_encoder_request(&enc_req, &xei);
  if (!convert_ok) {
    return 0;
  }

  xed_uint8_t ibytes[XED_MAX_INSTRUCTION_BYTES];
  const unsigned ilen = XED_MAX_INSTRUCTION_BYTES;
  unsigned olen = 0;
  xed_error = xed_encode(&enc_req, ibytes, ilen, &olen);
  if (XED_ERROR_NONE != xed_error || 0 == olen) {
    return 0;
  }

 // re-decode the insn so we can print it out
  xed_decoded_inst_t redec;
  xed_decoded_inst_zero(&redec);
  xed_decoded_inst_zero_set_mode(&redec, &dstate);
  xed_error = xed_decode(&redec, ibytes, olen);
  if (XED_ERROR_NONE != xed_error) {
    return 0;
  }

  char outbuf[256];
  xed_bool_t formatOk = xed_format_context(XED_SYNTAX_ATT, &redec, outbuf, 256, 0/*PC*/, NULL, NULL);
  if (!formatOk) {
    return 0;
  }
  string insnAsm = string(outbuf);

  cout << " { " ; // start struct
  cout << ".bytes = { " << hex; // bytes array
  for (unsigned i = 0; i < olen; i++) {
    cout << "0x" << setw(2) << setfill('0') << int(ibytes[i]) << ",";
  }
  cout << " }, " << dec;
  cout << ".expectedOpcode = " << udis86MnemonicNameOfXedIclass(opcode) << ", ";
  cout << ".storeWidthBytes = " << srcRegWidthBits/8 << ", ";
  cout << ".disasm = \"" << insnAsm << "\"";
  cout << " }, // " << NumTestInsns << endl; // end struct

  NumTestInsns++;
  return 1;
}

void generateTests() {

  cout << "#ifdef TEST_INTERPRETER" << endl;

  cout << "struct test_insn { const uint8_t bytes[" << XED_MAX_INSTRUCTION_BYTES << "]; const ud_mnemonic_code_t expectedOpcode; const uint8_t storeWidthBytes; const char* disasm; };" << endl;
  cout << "struct test_insn TEST_INSNS[] = {" << endl;

  for (int opi = 0; opi < NUM_GPR_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = GPR_OPCODES[opi];

    for (unsigned dsti = XED_REG_AX; dsti <= XED_REG_BH; dsti++) {
      const xed_reg_enum_t dstReg = static_cast<xed_reg_enum_t>(dsti);
      for (unsigned srci = XED_REG_AX; srci <= XED_REG_BH; srci++) {
        const xed_reg_enum_t srcReg = static_cast<xed_reg_enum_t>(srci);

        for (unsigned storeWidthBits = 8; storeWidthBits <= 64; storeWidthBits <<= 1) { // stores of different widths
          const xed_encoder_operand_t dstOp = xed_mem_b(dstReg, storeWidthBits);
          const xed_encoder_operand_t srcOp = xed_reg(srcReg);
          generateTestInsn(opcode, dstOp, srcOp, storeWidthBits);
          
          // base+displacement destination
          for (unsigned immWidthBits = 8; immWidthBits <= 32; immWidthBits <<= 1) {
            const xed_enc_displacement_t disp = xed_disp(rand() % (1 << immWidthBits), immWidthBits);
            const xed_encoder_operand_t dstOp = xed_mem_bd(dstReg, disp, storeWidthBits);
            generateTestInsn(opcode, dstOp, srcOp, storeWidthBits);
          }

          // TODO: base+index+scale+displacement destination
        }
      }

      // immediate src
      for (unsigned immWidthBits = 8; immWidthBits <= 32; immWidthBits <<= 1) {
        const xed_encoder_operand_t srcOp = xed_imm0(rand() % (1 << immWidthBits), immWidthBits);

        // base destination
        xed_encoder_operand_t dstOp = xed_mem_b(dstReg, immWidthBits);
        generateTestInsn(opcode, dstOp, srcOp, immWidthBits);

        // base+displacement destination
        xed_enc_displacement_t disp = xed_disp(rand() % (1 << immWidthBits), immWidthBits);
        dstOp = xed_mem_bd(dstReg, disp, immWidthBits);
        generateTestInsn(opcode, dstOp, srcOp, immWidthBits);

        // TODO: base+index+scale+displacement destination
      }
    }

  }
  for (int opi = 0; opi < NUM_SIMD_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = SIMD_OPCODES[opi];

    for (unsigned dsti = XED_REG_AX; dsti <= XED_REG_BH; dsti++) {
      for (unsigned srci = XED_REG_MMX0; srci <= XED_REG_MMX7; srci++) { // MMX registers
        const xed_reg_enum_t dstReg = static_cast<xed_reg_enum_t>(dsti);
        const xed_reg_enum_t srcReg = static_cast<xed_reg_enum_t>(srci);
        const unsigned storeWidthBits = xed_get_register_width_bits64(srcReg);
        const xed_encoder_operand_t dstOp = xed_mem_b(dstReg, storeWidthBits);
        const xed_encoder_operand_t srcOp = xed_reg(srcReg);
        generateTestInsn(opcode, dstOp, srcOp, storeWidthBits);
      }
      for (unsigned srci = XED_REG_XMM0; srci <= XED_REG_XMM15; srci++) { // SSE registers
        const xed_reg_enum_t dstReg = static_cast<xed_reg_enum_t>(dsti);
        const xed_reg_enum_t srcReg = static_cast<xed_reg_enum_t>(srci);
        const unsigned storeWidthBits = xed_get_register_width_bits64(srcReg);
        const xed_encoder_operand_t dstOp = xed_mem_b(dstReg, storeWidthBits);
        const xed_encoder_operand_t srcOp = xed_reg(srcReg);
        generateTestInsn(opcode, dstOp, srcOp, storeWidthBits);
      }
    }
  }

  cout << "};" << endl;
  cout << "#define NUM_TEST_INSNS " << NumTestInsns << endl;
  cout << "#define MAX_INSN_BYTES " << XED_MAX_INSTRUCTION_BYTES << endl << endl;

  cout << "#endif" << endl;

}

bool generateInsn(xed_encoder_instruction_t* xei, xed_state_t* dstate, string& insnAsm) {
  insnAsm = "";
  xed_error_enum_t xed_error = XED_ERROR_NONE;
  xed_encoder_request_t enc_req;

  xed_encoder_request_zero_set_mode(&enc_req, dstate);
  xed_bool_t convert_ok = xed_convert_to_encoder_request(&enc_req, xei);
  if (!convert_ok) {
    cerr << "ERROR conversion to encode request failed" << endl;
    return false;
  }

  xed_uint8_t ibytes[XED_MAX_INSTRUCTION_BYTES];
  const unsigned ilen = XED_MAX_INSTRUCTION_BYTES;
  unsigned olen = 0;
  xed_error = xed_encode(&enc_req, ibytes, ilen, &olen);
  if (XED_ERROR_NONE != xed_error) {
    //cerr << "ERROR encoding failed: " << xed_error_enum_t2str(xed_error) <<  " (" << olen << " bytes)" << endl;
    return false;
  }
  
  // print bytes of kernel write insn
  for (unsigned i = 0; i < olen; i++) {
    //cout << hex << setw(2) << setfill('0') << int(ibytes[i]) << dec;
  }
  //cout << " ";

  // re-decode the insn so we can print it out
  xed_decoded_inst_t redec;
  xed_decoded_inst_zero(&redec);
  xed_decoded_inst_zero_set_mode(&redec, dstate);
  xed_error = xed_decode(&redec, ibytes, olen);
  if (XED_ERROR_NONE != xed_error) {
    cerr <<  "ERROR decoding kernel write insn: " << xed_error_enum_t2str(xed_error) << endl;
    return false;
  }

  // verify that we have identified all the insns that read/write FLAGS
  const xed_simple_flag_t* flagsUsage = xed_decoded_inst_get_rflags_info(&redec);
  if (opcodeWritesFlags(xed_decoded_inst_get_iclass(&redec))) {
    assert(flagsUsage != NULL);
    assert(flagsUsage->may_write || flagsUsage->must_write);
  } else if (!isOpcodeSET(xed_decoded_inst_get_iclass(&redec))) {
    // SET* insns read flags; everything else should completely ignore FLAGS
    assert(flagsUsage == NULL);
  }
  
  char outbuf[256];
  xed_bool_t formatOk = xed_format_context(XED_SYNTAX_ATT, &redec, outbuf, 256, 0/*PC*/, NULL, NULL);
  if (!formatOk) {
    cerr << "ERROR disassembling kernel write insn" << endl;
    return false;
  }

  insnAsm = string(outbuf);

  // clean up generated assembly for GCC's inline assembly requirements

  // hard-coded register names must be prefixed with %%
  boost::replace_all(insnAsm, "%", "%%");
  // gcc uses mm0, mm1, etc. for the MMX registers
  boost::replace_all(insnAsm, "%%mmx", "%%mm");

  // translate opcodes that gcc doesn't understand
  boost::replace_all(insnAsm, "movdqax ",  "movdqa ");
  boost::replace_all(insnAsm, "movupdx ",  "movupd ");
  boost::replace_all(insnAsm, "movupsx ",  "movups ");
  boost::replace_all(insnAsm, "movssl ",   "movss ");
  boost::replace_all(insnAsm, "movdl ",    "movd ");
  boost::replace_all(insnAsm, "movqq ",    "movq ");
  boost::replace_all(insnAsm, "vmovsdq ",  "vmovsd ");
  boost::replace_all(insnAsm, "vmovlpsq ", "vmovlps ");
  boost::replace_all(insnAsm, "movlpsq ",  "movlps ");
  boost::replace_all(insnAsm, "vmovlpdq ", "vmovlpd ");
  boost::replace_all(insnAsm, "movlpdq ",  "movlpd ");
  boost::replace_all(insnAsm, "vmovhpsq ", "vmovhps ");
  boost::replace_all(insnAsm, "movhpsq ",  "movhps ");
  boost::replace_all(insnAsm, "vmovhpdq ", "vmovhpd ");
  boost::replace_all(insnAsm, "movhpdq ",  "movhpd ");
  boost::replace_all(insnAsm, "movapsx ",  "movaps ");
  boost::replace_all(insnAsm, "vmovapsx ", "vmovaps ");
  boost::replace_all(insnAsm, "movapdx ",  "movapd ");
  boost::replace_all(insnAsm, "vmovapdx ", "vmovapd ");
  boost::replace_all(insnAsm, "vmovdqux ", "vmovdqu ");
  boost::replace_all(insnAsm, "movdqux ",  "movdqu ");

  return true;
}
