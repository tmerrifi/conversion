extern "C" {
#include "xed-interface.h"
#include "xed-examples-util.h"
}
//#include "xed-enc-lang.H"
#include <iostream>
#include <string>
#include <cstdlib>

#include <boost/algorithm/string.hpp>

using namespace std;

const char* ASM_NEWLINE = "\\n\\t";

const xed_iclass_enum_t OPCODES[] = { 

  // TODO: handle insns that set FLAGS: void ADD_RSI(uint64_t dstAddress, uint64_t srcValue, uint64_t* theFlags);
  // XED_ICLASS_ADD,
  // XED_ICLASS_AND,
  // XED_ICLASS_OR,
  // XED_ICLASS_SUB,
  //XED_ICLASS_SAL, // doesn't exist in xed!!
  XED_ICLASS_SAR,
  XED_ICLASS_SHL,
  XED_ICLASS_SHR,

  XED_ICLASS_SETB,
  XED_ICLASS_SETNZ,

  XED_ICLASS_MOV,
  XED_ICLASS_MOVD,
  XED_ICLASS_MOVSS,
  XED_ICLASS_MOVQ,
  XED_ICLASS_MOVUPS,
  XED_ICLASS_MOVUPD,
  XED_ICLASS_VMOVUPS,
  XED_ICLASS_VMOVUPD,
  XED_ICLASS_VMOVSS,
  XED_ICLASS_VMOVSD,
  XED_ICLASS_MOVLPS,
  XED_ICLASS_MOVLPD,
  XED_ICLASS_VMOVLPS,
  XED_ICLASS_VMOVLPD,
  XED_ICLASS_MOVHPS,
  XED_ICLASS_MOVHPD,
  XED_ICLASS_VMOVHPS,
  XED_ICLASS_VMOVHPD,
  XED_ICLASS_MOVAPS,
  XED_ICLASS_MOVAPD,
  XED_ICLASS_VMOVAPS,
  XED_ICLASS_VMOVAPD,
  XED_ICLASS_MOVDQA,
  XED_ICLASS_MOVDQU,
  XED_ICLASS_VMOVDQA,
  XED_ICLASS_VMOVDQU

  //XED_ICLASS_MOVSD // TODO: doesn't generate any valid code for some reason...
};
const int NUM_OPCODES = sizeof(OPCODES) / sizeof(OPCODES[0]);

// NB: use RSI for the src value if possible as it's the 2nd arg in x86-64 calling conventions
const xed_reg_enum_t REGISTERS[] = {
  XED_REG_SIL, // low 8b
  XED_REG_AH, // high 8b
  XED_REG_SI, // low 16b
  XED_REG_ESI, // low 32b
  XED_REG_RSI, // 64b
  XED_REG_MMX0, // 64b MMX
  XED_REG_XMM0 // 128b SSE

  /* NB: there are no AVX instructions on our target platform (Nehalem). Adding
     AVX support here would be tricky as gcc doesn't have any built-in 256b
     integer types, so we'd have to pack up the ymm src register manually. */
  // XED_REG_YMM0, // 256b AVX 
};
const int NUM_REGISTERS = sizeof(REGISTERS) / sizeof(REGISTERS[0]);

bool generateInsn(xed_encoder_instruction_t* xei, xed_state_t* dstate, string& insnAsm);
void generateLUTs();

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

bool isOpcodeCompute(xed_iclass_enum_t opcode) {
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

int main(int argc, char** argv) {

  xed_tables_init();

  xed_state_t dstate;
  xed_state_zero(&dstate);
  dstate.mmode=XED_MACHINE_MODE_LONG_64;
  dstate.stack_addr_width=XED_ADDRESS_WIDTH_64b;
  //dstate.mmode=XED_MACHINE_MODE_LEGACY_32;
  //dstate.stack_addr_width=XED_ADDRESS_WIDTH_32b;

  cout << "#include <stdlib.h>" << endl;
  cout << "#include <stdint.h>" << endl;
  cout << "#include <assert.h>" << endl << endl;

  for (int opi = 0; opi < NUM_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = OPCODES[opi];

    // SET* insns have only FLAGS as a source register
    if (isOpcodeSET(opcode)) {
      xed_encoder_instruction_t xei; 
      // NB: use RDI for the dst addr as it holds the 1st arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RDI, 8);
      xed_inst1(&xei, dstate, opcode, 0, kwDst);

      const string funName = makeInsnFunName(opcode, XED_REG_FLAGS); 
      cout << "void " << funName << "(uint64_t dstAddress, uint64_t flags) { ";

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << endl;

        // this insnFun should never get called
        cout << " assert(0); }" << endl;

        continue;
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

    // STORES FROM A REGISTER

    bool madeCode = false;

    for (int regi = 0; regi < NUM_REGISTERS; regi++) {
      xed_reg_enum_t srcReg = REGISTERS[regi];

      xed_uint32_t srcRegWidthBits = xed_get_register_width_bits64(srcReg);
      
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

      } else if (XED_REG_SIL == srcReg && isOpcodeShift(opcode)) {
        // shift insns require the shift amount be placed in CL
        srcReg = XED_REG_CL;
        srcRegWidthBits = 8;
      }

      // NB: use RDI for the dest addr as it holds the 1st arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RDI, srcRegWidthBits);
      string dstAddrReg = "D";
      xed_encoder_operand_t kwSrc = xed_reg(srcReg);

      xed_encoder_instruction_t xei; 

      // two-operand insn
      xed_inst2(&xei, dstate, opcode, srcRegWidthBits, kwDst, kwSrc); 

      const string funName = makeInsnFunName(opcode, srcReg);
      if (xed_reg_class(srcReg) == XED_REG_CLASS_XMM) {
        cout << "void " << funName << "(uint64_t dstAddress, unsigned __int128 srcValue) {" << endl;
      } else { // includes MM registers
        cout << "void " << funName << "(uint64_t dstAddress, uint64_t srcValue) {" << endl;
      }

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << " srcReg:" << xed_reg_enum_t2str(srcReg) << endl;

        // this insnFun should never get called
        cout << " assert(0);" << endl << "}" << endl;

        continue;
      }

      string srcRegCanonicalName = string(xed_reg_enum_t2str(srcReg));
      if (xed_get_register_width_bits64(srcReg) < 64) { // canonicalize to 64-bit registers (or xmm, ymm)
        srcRegCanonicalName = string(xed_reg_enum_t2str(xed_get_largest_enclosing_register(srcReg)));
      }
      boost::algorithm::to_lower(srcRegCanonicalName);

      if (xed_reg_class(srcReg) == XED_REG_CLASS_XMM) {
        srcRegCanonicalName = "x"; // use any xmm register
        boost::replace_all(insnAsm, "%%xmm0", "%1");
      } else if (xed_reg_class(srcReg) == XED_REG_CLASS_MMX) {
        srcRegCanonicalName = "y"; // use any mm register
        boost::replace_all(insnAsm, "%%mmx0", "%1");
      }

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

  }
  
  generateLUTs();

}

void generateLUTs() {

  // typedefs
  cout << endl << "typedef void (*movInsnFun)(uint64_t dstAddress, uint64_t srcValue);" << endl << endl;
  cout << endl << "typedef void (*wideMovInsnFun)(uint64_t dstAddress, unsigned __int128 srcValue);" << endl << endl;
  cout << endl << "typedef void (*compInsnFun)(uint64_t dstAddress, uint64_t srcValue, uint64_t* flags);" << endl << endl;

  // opcode2fun tables
  for (int regi = 0; regi < NUM_REGISTERS; regi++) {
    const xed_reg_enum_t srcReg = REGISTERS[regi];

    string funPtrName = "movInsnFun";
    if (xed_reg_class(srcReg) == XED_REG_CLASS_XMM) {
      funPtrName = "wideMovInsnFun";
    }
    string nullPtr = "(" + funPtrName + ") NULL";

    // non-compute insn table
    cout << funPtrName << " NonComputeOpcode2FunTable_" << xed_reg_enum_t2str(srcReg) << "[] = {" << endl;

    for (int opi = 0; opi < NUM_OPCODES; opi++) {
      const xed_iclass_enum_t opcode = OPCODES[opi];
      string funName = makeInsnFunName(opcode, srcReg);
      if (isOpcodeCompute(opcode)) {
        funName = nullPtr;
      }
      cout << " " << funName << "," << endl;
    }

    cout << " " << nullPtr << endl;
    cout << "};" << endl << endl;

    // compute insn table
    if (xed_reg_class(srcReg) == XED_REG_CLASS_XMM) {
      // NB: I don't think x86 has wide computation insn functions
      continue;
    }
    funPtrName = "compInsnFun";
    nullPtr = "(" + funPtrName + ") NULL";
    cout << funPtrName << " ComputeOpcode2FunTable_" << xed_reg_enum_t2str(srcReg) << "[] = {" << endl;

    for (int opi = 0; opi < NUM_OPCODES; opi++) {
      const xed_iclass_enum_t opcode = OPCODES[opi];
      string funName = makeInsnFunName(opcode, srcReg);
      if (!isOpcodeCompute(opcode)) {
        funName = nullPtr;
      }
      cout << " " << funName << "," << endl;      
    }

    cout << " " << nullPtr << endl;
    cout << "};" << endl << endl;    

  } // loop over registers

  // // opcodeTable
  // cout << "movInsnFun* OpcodeTable[] = {" << endl;
  // for (int opi = 0; opi < NUM_OPCODES; opi++) {
  //   const xed_iclass_enum_t opcode = OPCODES[opi];
  //   cout << " " << xed_iclass_enum_t2str(opcode) << "_Srcreg2FunTable," << endl;
  // }
  // cout << " (movInsnFun*) NULL" << endl;
  // cout << "};" << endl << endl;

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
  xed_decoded_inst_t redd;
  xed_decoded_inst_zero(&redd);
  xed_decoded_inst_zero_set_mode(&redd, dstate);
  xed_error = xed_decode(&redd, ibytes, olen);
  if (XED_ERROR_NONE != xed_error) {
    cerr <<  "ERROR decoding kernel write insn: " << xed_error_enum_t2str(xed_error) << endl;
    return false;
  }
  
  char outbuf[256];
  xed_bool_t formatOk = xed_format_context(XED_SYNTAX_ATT, &redd, outbuf, 256, 0/*PC*/, NULL, NULL);
  if (!formatOk) {
    cerr << "ERROR disassembling kernel write insn" << endl;
    return false;
  }

  insnAsm = string(outbuf);

  // clean up generated assembly for GCC's inline assembly requirements

  // hard-coded register names must be prefixed with %%
  boost::replace_all(insnAsm, "%", "%%");

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
