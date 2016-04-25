extern "C" {
#include "xed-interface.h"
#include "xed-examples-util.h"
}
//#include "xed-enc-lang.H"
#include <iostream>
#include <string>
//#include <sstream>

#include <boost/algorithm/string.hpp>

using namespace std;

const char* ASM_NEWLINE = "\\n\\t";

const xed_iclass_enum_t OPCODES[] = { 
  XED_ICLASS_ADD,
  XED_ICLASS_AND,
  XED_ICLASS_MOV,
  XED_ICLASS_MOVDQA,
  XED_ICLASS_OR,
  XED_ICLASS_SETB,
  XED_ICLASS_SETNZ,
  XED_ICLASS_SHL,
  XED_ICLASS_SUB
};
const int NUM_OPCODES = sizeof(OPCODES) / sizeof(OPCODES[0]);

// NB: use RDI for the src value as it's the 1st arg in x86-64 calling conventions
const xed_reg_enum_t REGISTERS[] = {
  XED_REG_DIL, // low 8b
  XED_REG_AH, // high 8b
  XED_REG_DI, // low 16b
  XED_REG_EDI, // low 32b
  XED_REG_RDI, // 64b
  XED_REG_MMX0, // 64b MMX
  XED_REG_XMM0 // 128b SSE
  // XED_REG_YMM0, // 256b AVX NB: no AVX instructions on our target platform
};
const int NUM_REGISTERS = sizeof(REGISTERS) / sizeof(REGISTERS[0]);

bool generateInsn(xed_encoder_instruction_t* xei, xed_state_t* dstate, string& insnAsm);
void generateLUTs();

string makeInsnFunName(xed_iclass_enum_t opcode, xed_reg_enum_t srcReg) {
  string funName = "";
  funName += xed_iclass_enum_t2str(opcode);
  funName += "_";
  funName += xed_reg_enum_t2str(srcReg);
  return funName;
}

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
      // NB: use RSI for the dst addr as it holds the 2nd arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RSI, 8);
      xed_inst1(&xei, dstate, opcode, 0, kwDst);

      const string funName = makeInsnFunName(opcode, XED_REG_FLAGS); 
      cout << "void " << funName << "(uint64_t flags, uint64_t dstAddress) {" << endl;

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << endl;

        // this insnFun should never get called
        cout << " assert(0);" << endl << "}" << endl;

        continue;
      }

      cout << " __asm__(\"push %%rdi" << ASM_NEWLINE << "\"" << endl;
      cout << "         \"popf" << ASM_NEWLINE << "\"" << endl;
      cout << "         \"" << insnAsm << ASM_NEWLINE << "\"" << endl;
      cout << "         : /*no output registers*/" << endl;
      cout << "         : \"S\"(dstAddress), \"D\"(flags) /*input registers*/" << endl;
      cout << "         : /*no clobbered registers*/" << endl;
      cout << "         );" << endl;

      cout << "}" << endl << endl;
      
      continue;
    }

    // STORES FROM A REGISTER

    for (int regi = 0; regi < NUM_REGISTERS; regi++) {
      const xed_reg_enum_t srcReg = REGISTERS[regi];

      const xed_uint32_t srcRegWidthBits = xed_get_register_width_bits64(srcReg);

      // NB: use RSI for the dest addr as it holds the 2nd arg in x86-64 calling conventions
      xed_encoder_operand_t kwDst = xed_mem_b(XED_REG_RSI, srcRegWidthBits);
      string dstAddrReg = "S";
      xed_encoder_operand_t kwSrc = xed_reg(srcReg);

      xed_encoder_instruction_t xei; 

      // two-operand insn
      xed_inst2(&xei, dstate, opcode, srcRegWidthBits, kwDst, kwSrc); 

      const string funName = makeInsnFunName(opcode, srcReg); 
      cout << "void " << funName << "(uint64_t srcValue, uint64_t dstAddress) {" << endl;

      string insnAsm = "";
      if (!generateInsn(&xei, &dstate, insnAsm)) {
        //cerr << " opcode:" << xed_iclass_enum_t2str(opcode) << " srcReg:" << xed_reg_enum_t2str(srcReg) << endl;

        // this insnFun should never get called
        cout << " assert(0);" << endl << "}" << endl;

        continue;
      }

      // gcc doesn't have builtin register constraints for r8-r15, so for 
      // simplicity we always specify our own custom constraints
      // http://stackoverflow.com/questions/15997759/constraining-r10-register-in-gcc-inline-x86-64-assembly
      string srcRegCanonicalName = string(xed_reg_enum_t2str(srcReg));
      if (xed_get_register_width_bits64(srcReg) < 64) { // canonicalize to 64-bit registers (or xmm, ymm)
        srcRegCanonicalName = string(xed_reg_enum_t2str(xed_get_largest_enclosing_register(srcReg)));
      }
      boost::algorithm::to_lower(srcRegCanonicalName);

      cout << "register uint64_t myReg asm (\"" << srcRegCanonicalName << "\") = srcValue;" << endl;

      cout << " __asm__(\"" << insnAsm << ASM_NEWLINE << "\"" << endl;
      cout << "         : /*no output registers*/" << endl;
      cout << "         : \"" << dstAddrReg << "\"(dstAddress), \"r\"(myReg) /*input registers*/" << endl;
      cout << "         : /*no clobbered registers*/" << endl;
      cout << "         );" << endl;

      cout << "}" << endl << endl;
      
    }

    // NB: stores from an immediate just use "store (eax), ebx" and put the immediate into ebx
    // may need to handle various immediate formats, signed vs unsigned, sign extension, etc?

  }
  
  generateLUTs();

}

void generateLUTs() {

  // typedefs
  cout << endl << "typedef void (*insnFun)(uint64_t srcValue, uint64_t dstAddress);" << endl << endl;

  // srcreg2fun tables
  for (int opi = 0; opi < NUM_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = OPCODES[opi];

    cout << "insnFun " << xed_iclass_enum_t2str(opcode) << "_Srcreg2FunTable[] = {" << endl;

    if (isOpcodeSET(opcode)) {
      const string funName = makeInsnFunName(opcode, XED_REG_FLAGS);
      cout << " " << funName << "," << endl;

    } else {
      for (int regi = 0; regi < NUM_REGISTERS; regi++) {
        const xed_reg_enum_t srcReg = REGISTERS[regi];
        const string funName = makeInsnFunName(opcode, srcReg);
        cout << " " << funName << "," << endl;
      }
    }

    cout << " (insnFun) NULL" << endl;
    cout << "};" << endl << endl;
  }

  // opcodeTable
  cout << "insnFun* OpcodeTable[] = {" << endl;
  for (int opi = 0; opi < NUM_OPCODES; opi++) {
    const xed_iclass_enum_t opcode = OPCODES[opi];
    cout << " " << xed_iclass_enum_t2str(opcode) << "_Srcreg2FunTable," << endl;
  }
  cout << " (insnFun*) NULL" << endl;
  cout << "};" << endl << endl;

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
  boost::replace_all(insnAsm, "movdqax ", "movdqa ");

  return true;
}
