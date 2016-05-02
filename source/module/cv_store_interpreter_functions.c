// AUTO-GENERATED FILE - DO NOT EDIT!!

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <udis86.h>

#define CV_LAST_GPR_OPCODE 9
#define CV_LAST_SIMD_OPCODE 34
#define CV_LAST_VALID_OPCODE 34

void SETB_FLAGS(void* dstAddress, uint64_t flags) { 
 __asm__("push %%rsi\n\t"
         "popf\n\t"
         "setbb  (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "S"(flags) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SETNZ_FLAGS(void* dstAddress, uint64_t flags) { 
 __asm__("push %%rsi\n\t"
         "popf\n\t"
         "setnzb  (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "S"(flags) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOV_SIL(void* dstAddress, uint64_t srcValue) {
 __asm__("movb  %%sil, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOV_AH(void* dstAddress, uint64_t srcValue) {
 __asm__("movb  %%ah, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "rax"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOV_SI(void* dstAddress, uint64_t srcValue) {
 __asm__("movw  %%si, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOV_ESI(void* dstAddress, uint64_t srcValue) {
 __asm__("movl  %%esi, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOV_RSI(void* dstAddress, uint64_t srcValue) {
 __asm__("movq  %%rsi, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void ADD_SIL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "addb  %%sil, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void ADD_AH(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "addb  %%ah, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rax"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void ADD_SI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "addw  %%si, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void ADD_ESI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "addl  %%esi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void ADD_RSI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "addq  %%rsi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void AND_SIL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "andb  %%sil, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void AND_AH(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "andb  %%ah, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rax"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void AND_SI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "andw  %%si, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void AND_ESI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "andl  %%esi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void AND_RSI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "andq  %%rsi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void OR_SIL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "orb  %%sil, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void OR_AH(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "orb  %%ah, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rax"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void OR_SI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "orw  %%si, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void OR_ESI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "orl  %%esi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void OR_RSI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "orq  %%rsi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SUB_SIL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "subb  %%sil, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SUB_AH(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "subb  %%ah, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rax"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SUB_SI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "subw  %%si, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SUB_ESI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "subl  %%esi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SUB_RSI(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "subq  %%rsi, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rsi"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SAR_CL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "sarb  %%cl, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rcx"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SHL_CL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "shlb  %%cl, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rcx"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void SHR_CL(void* dstAddress, uint64_t srcValue, uint64_t* flags) {
 __asm__("push %2\n\t"
         "popf\n\t"
         "shrb  %%cl, (%%rdi)\n\t"
         "pushf\n\t"
         "pop %0\n\t"
         : "=r"(*flags) /*output registers*/
         : "D"(dstAddress), "r"(*flags), "rcx"(srcValue) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX0(void* dstAddress) {
 __asm__("movd  %%mm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX1(void* dstAddress) {
 __asm__("movd  %%mm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX2(void* dstAddress) {
 __asm__("movd  %%mm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX3(void* dstAddress) {
 __asm__("movd  %%mm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX4(void* dstAddress) {
 __asm__("movd  %%mm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX5(void* dstAddress) {
 __asm__("movd  %%mm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX6(void* dstAddress) {
 __asm__("movd  %%mm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_MMX7(void* dstAddress) {
 __asm__("movd  %%mm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM0(void* dstAddress) {
 __asm__("movd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM1(void* dstAddress) {
 __asm__("movd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM2(void* dstAddress) {
 __asm__("movd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM3(void* dstAddress) {
 __asm__("movd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM4(void* dstAddress) {
 __asm__("movd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM5(void* dstAddress) {
 __asm__("movd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM6(void* dstAddress) {
 __asm__("movd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM7(void* dstAddress) {
 __asm__("movd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM8(void* dstAddress) {
 __asm__("movd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM9(void* dstAddress) {
 __asm__("movd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM10(void* dstAddress) {
 __asm__("movd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM11(void* dstAddress) {
 __asm__("movd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM12(void* dstAddress) {
 __asm__("movd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM13(void* dstAddress) {
 __asm__("movd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM14(void* dstAddress) {
 __asm__("movd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVD_XMM15(void* dstAddress) {
 __asm__("movd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM0(void* dstAddress) {
 __asm__("movss  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM1(void* dstAddress) {
 __asm__("movss  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM2(void* dstAddress) {
 __asm__("movss  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM3(void* dstAddress) {
 __asm__("movss  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM4(void* dstAddress) {
 __asm__("movss  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM5(void* dstAddress) {
 __asm__("movss  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM6(void* dstAddress) {
 __asm__("movss  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM7(void* dstAddress) {
 __asm__("movss  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM8(void* dstAddress) {
 __asm__("movss  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM9(void* dstAddress) {
 __asm__("movss  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM10(void* dstAddress) {
 __asm__("movss  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM11(void* dstAddress) {
 __asm__("movss  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM12(void* dstAddress) {
 __asm__("movss  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM13(void* dstAddress) {
 __asm__("movss  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM14(void* dstAddress) {
 __asm__("movss  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVSS_XMM15(void* dstAddress) {
 __asm__("movss  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX0(void* dstAddress) {
 __asm__("movq  %%mm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX1(void* dstAddress) {
 __asm__("movq  %%mm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX2(void* dstAddress) {
 __asm__("movq  %%mm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX3(void* dstAddress) {
 __asm__("movq  %%mm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX4(void* dstAddress) {
 __asm__("movq  %%mm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX5(void* dstAddress) {
 __asm__("movq  %%mm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX6(void* dstAddress) {
 __asm__("movq  %%mm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_MMX7(void* dstAddress) {
 __asm__("movq  %%mm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM0(void* dstAddress) {
 __asm__("movq  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM1(void* dstAddress) {
 __asm__("movq  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM2(void* dstAddress) {
 __asm__("movq  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM3(void* dstAddress) {
 __asm__("movq  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM4(void* dstAddress) {
 __asm__("movq  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM5(void* dstAddress) {
 __asm__("movq  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM6(void* dstAddress) {
 __asm__("movq  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM7(void* dstAddress) {
 __asm__("movq  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM8(void* dstAddress) {
 __asm__("movq  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM9(void* dstAddress) {
 __asm__("movq  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM10(void* dstAddress) {
 __asm__("movq  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM11(void* dstAddress) {
 __asm__("movq  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM12(void* dstAddress) {
 __asm__("movq  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM13(void* dstAddress) {
 __asm__("movq  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM14(void* dstAddress) {
 __asm__("movq  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVQ_XMM15(void* dstAddress) {
 __asm__("movq  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM0(void* dstAddress) {
 __asm__("movups  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM1(void* dstAddress) {
 __asm__("movups  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM2(void* dstAddress) {
 __asm__("movups  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM3(void* dstAddress) {
 __asm__("movups  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM4(void* dstAddress) {
 __asm__("movups  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM5(void* dstAddress) {
 __asm__("movups  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM6(void* dstAddress) {
 __asm__("movups  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM7(void* dstAddress) {
 __asm__("movups  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM8(void* dstAddress) {
 __asm__("movups  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM9(void* dstAddress) {
 __asm__("movups  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM10(void* dstAddress) {
 __asm__("movups  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM11(void* dstAddress) {
 __asm__("movups  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM12(void* dstAddress) {
 __asm__("movups  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM13(void* dstAddress) {
 __asm__("movups  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM14(void* dstAddress) {
 __asm__("movups  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPS_XMM15(void* dstAddress) {
 __asm__("movups  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM0(void* dstAddress) {
 __asm__("movupd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM1(void* dstAddress) {
 __asm__("movupd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM2(void* dstAddress) {
 __asm__("movupd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM3(void* dstAddress) {
 __asm__("movupd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM4(void* dstAddress) {
 __asm__("movupd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM5(void* dstAddress) {
 __asm__("movupd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM6(void* dstAddress) {
 __asm__("movupd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM7(void* dstAddress) {
 __asm__("movupd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM8(void* dstAddress) {
 __asm__("movupd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM9(void* dstAddress) {
 __asm__("movupd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM10(void* dstAddress) {
 __asm__("movupd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM11(void* dstAddress) {
 __asm__("movupd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM12(void* dstAddress) {
 __asm__("movupd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM13(void* dstAddress) {
 __asm__("movupd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM14(void* dstAddress) {
 __asm__("movupd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVUPD_XMM15(void* dstAddress) {
 __asm__("movupd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM0(void* dstAddress) {
 __asm__("vmovups  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM1(void* dstAddress) {
 __asm__("vmovups  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM2(void* dstAddress) {
 __asm__("vmovups  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM3(void* dstAddress) {
 __asm__("vmovups  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM4(void* dstAddress) {
 __asm__("vmovups  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM5(void* dstAddress) {
 __asm__("vmovups  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM6(void* dstAddress) {
 __asm__("vmovups  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM7(void* dstAddress) {
 __asm__("vmovups  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM8(void* dstAddress) {
 __asm__("vmovups  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM9(void* dstAddress) {
 __asm__("vmovups  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM10(void* dstAddress) {
 __asm__("vmovups  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM11(void* dstAddress) {
 __asm__("vmovups  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM12(void* dstAddress) {
 __asm__("vmovups  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM13(void* dstAddress) {
 __asm__("vmovups  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM14(void* dstAddress) {
 __asm__("vmovups  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPS_XMM15(void* dstAddress) {
 __asm__("vmovups  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM0(void* dstAddress) {
 __asm__("vmovupd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM1(void* dstAddress) {
 __asm__("vmovupd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM2(void* dstAddress) {
 __asm__("vmovupd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM3(void* dstAddress) {
 __asm__("vmovupd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM4(void* dstAddress) {
 __asm__("vmovupd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM5(void* dstAddress) {
 __asm__("vmovupd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM6(void* dstAddress) {
 __asm__("vmovupd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM7(void* dstAddress) {
 __asm__("vmovupd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM8(void* dstAddress) {
 __asm__("vmovupd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM9(void* dstAddress) {
 __asm__("vmovupd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM10(void* dstAddress) {
 __asm__("vmovupd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM11(void* dstAddress) {
 __asm__("vmovupd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM12(void* dstAddress) {
 __asm__("vmovupd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM13(void* dstAddress) {
 __asm__("vmovupd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM14(void* dstAddress) {
 __asm__("vmovupd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVUPD_XMM15(void* dstAddress) {
 __asm__("vmovupd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM0(void* dstAddress) {
 __asm__("vmovss  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM1(void* dstAddress) {
 __asm__("vmovss  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM2(void* dstAddress) {
 __asm__("vmovss  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM3(void* dstAddress) {
 __asm__("vmovss  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM4(void* dstAddress) {
 __asm__("vmovss  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM5(void* dstAddress) {
 __asm__("vmovss  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM6(void* dstAddress) {
 __asm__("vmovss  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM7(void* dstAddress) {
 __asm__("vmovss  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM8(void* dstAddress) {
 __asm__("vmovss  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM9(void* dstAddress) {
 __asm__("vmovss  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM10(void* dstAddress) {
 __asm__("vmovss  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM11(void* dstAddress) {
 __asm__("vmovss  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM12(void* dstAddress) {
 __asm__("vmovss  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM13(void* dstAddress) {
 __asm__("vmovss  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM14(void* dstAddress) {
 __asm__("vmovss  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSS_XMM15(void* dstAddress) {
 __asm__("vmovss  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM0(void* dstAddress) {
 __asm__("vmovsd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM1(void* dstAddress) {
 __asm__("vmovsd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM2(void* dstAddress) {
 __asm__("vmovsd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM3(void* dstAddress) {
 __asm__("vmovsd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM4(void* dstAddress) {
 __asm__("vmovsd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM5(void* dstAddress) {
 __asm__("vmovsd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM6(void* dstAddress) {
 __asm__("vmovsd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM7(void* dstAddress) {
 __asm__("vmovsd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM8(void* dstAddress) {
 __asm__("vmovsd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM9(void* dstAddress) {
 __asm__("vmovsd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM10(void* dstAddress) {
 __asm__("vmovsd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM11(void* dstAddress) {
 __asm__("vmovsd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM12(void* dstAddress) {
 __asm__("vmovsd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM13(void* dstAddress) {
 __asm__("vmovsd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM14(void* dstAddress) {
 __asm__("vmovsd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVSD_XMM15(void* dstAddress) {
 __asm__("vmovsd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM0(void* dstAddress) {
 __asm__("movlps  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM1(void* dstAddress) {
 __asm__("movlps  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM2(void* dstAddress) {
 __asm__("movlps  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM3(void* dstAddress) {
 __asm__("movlps  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM4(void* dstAddress) {
 __asm__("movlps  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM5(void* dstAddress) {
 __asm__("movlps  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM6(void* dstAddress) {
 __asm__("movlps  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM7(void* dstAddress) {
 __asm__("movlps  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM8(void* dstAddress) {
 __asm__("movlps  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM9(void* dstAddress) {
 __asm__("movlps  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM10(void* dstAddress) {
 __asm__("movlps  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM11(void* dstAddress) {
 __asm__("movlps  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM12(void* dstAddress) {
 __asm__("movlps  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM13(void* dstAddress) {
 __asm__("movlps  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM14(void* dstAddress) {
 __asm__("movlps  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPS_XMM15(void* dstAddress) {
 __asm__("movlps  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM0(void* dstAddress) {
 __asm__("movlpd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM1(void* dstAddress) {
 __asm__("movlpd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM2(void* dstAddress) {
 __asm__("movlpd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM3(void* dstAddress) {
 __asm__("movlpd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM4(void* dstAddress) {
 __asm__("movlpd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM5(void* dstAddress) {
 __asm__("movlpd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM6(void* dstAddress) {
 __asm__("movlpd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM7(void* dstAddress) {
 __asm__("movlpd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM8(void* dstAddress) {
 __asm__("movlpd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM9(void* dstAddress) {
 __asm__("movlpd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM10(void* dstAddress) {
 __asm__("movlpd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM11(void* dstAddress) {
 __asm__("movlpd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM12(void* dstAddress) {
 __asm__("movlpd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM13(void* dstAddress) {
 __asm__("movlpd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM14(void* dstAddress) {
 __asm__("movlpd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVLPD_XMM15(void* dstAddress) {
 __asm__("movlpd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM0(void* dstAddress) {
 __asm__("vmovlps  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM1(void* dstAddress) {
 __asm__("vmovlps  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM2(void* dstAddress) {
 __asm__("vmovlps  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM3(void* dstAddress) {
 __asm__("vmovlps  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM4(void* dstAddress) {
 __asm__("vmovlps  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM5(void* dstAddress) {
 __asm__("vmovlps  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM6(void* dstAddress) {
 __asm__("vmovlps  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM7(void* dstAddress) {
 __asm__("vmovlps  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM8(void* dstAddress) {
 __asm__("vmovlps  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM9(void* dstAddress) {
 __asm__("vmovlps  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM10(void* dstAddress) {
 __asm__("vmovlps  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM11(void* dstAddress) {
 __asm__("vmovlps  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM12(void* dstAddress) {
 __asm__("vmovlps  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM13(void* dstAddress) {
 __asm__("vmovlps  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM14(void* dstAddress) {
 __asm__("vmovlps  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPS_XMM15(void* dstAddress) {
 __asm__("vmovlps  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM0(void* dstAddress) {
 __asm__("vmovlpd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM1(void* dstAddress) {
 __asm__("vmovlpd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM2(void* dstAddress) {
 __asm__("vmovlpd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM3(void* dstAddress) {
 __asm__("vmovlpd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM4(void* dstAddress) {
 __asm__("vmovlpd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM5(void* dstAddress) {
 __asm__("vmovlpd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM6(void* dstAddress) {
 __asm__("vmovlpd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM7(void* dstAddress) {
 __asm__("vmovlpd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM8(void* dstAddress) {
 __asm__("vmovlpd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM9(void* dstAddress) {
 __asm__("vmovlpd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM10(void* dstAddress) {
 __asm__("vmovlpd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM11(void* dstAddress) {
 __asm__("vmovlpd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM12(void* dstAddress) {
 __asm__("vmovlpd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM13(void* dstAddress) {
 __asm__("vmovlpd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM14(void* dstAddress) {
 __asm__("vmovlpd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVLPD_XMM15(void* dstAddress) {
 __asm__("vmovlpd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM0(void* dstAddress) {
 __asm__("movhps  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM1(void* dstAddress) {
 __asm__("movhps  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM2(void* dstAddress) {
 __asm__("movhps  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM3(void* dstAddress) {
 __asm__("movhps  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM4(void* dstAddress) {
 __asm__("movhps  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM5(void* dstAddress) {
 __asm__("movhps  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM6(void* dstAddress) {
 __asm__("movhps  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM7(void* dstAddress) {
 __asm__("movhps  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM8(void* dstAddress) {
 __asm__("movhps  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM9(void* dstAddress) {
 __asm__("movhps  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM10(void* dstAddress) {
 __asm__("movhps  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM11(void* dstAddress) {
 __asm__("movhps  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM12(void* dstAddress) {
 __asm__("movhps  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM13(void* dstAddress) {
 __asm__("movhps  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM14(void* dstAddress) {
 __asm__("movhps  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPS_XMM15(void* dstAddress) {
 __asm__("movhps  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM0(void* dstAddress) {
 __asm__("movhpd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM1(void* dstAddress) {
 __asm__("movhpd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM2(void* dstAddress) {
 __asm__("movhpd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM3(void* dstAddress) {
 __asm__("movhpd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM4(void* dstAddress) {
 __asm__("movhpd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM5(void* dstAddress) {
 __asm__("movhpd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM6(void* dstAddress) {
 __asm__("movhpd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM7(void* dstAddress) {
 __asm__("movhpd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM8(void* dstAddress) {
 __asm__("movhpd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM9(void* dstAddress) {
 __asm__("movhpd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM10(void* dstAddress) {
 __asm__("movhpd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM11(void* dstAddress) {
 __asm__("movhpd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM12(void* dstAddress) {
 __asm__("movhpd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM13(void* dstAddress) {
 __asm__("movhpd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM14(void* dstAddress) {
 __asm__("movhpd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVHPD_XMM15(void* dstAddress) {
 __asm__("movhpd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM0(void* dstAddress) {
 __asm__("vmovhps  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM1(void* dstAddress) {
 __asm__("vmovhps  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM2(void* dstAddress) {
 __asm__("vmovhps  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM3(void* dstAddress) {
 __asm__("vmovhps  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM4(void* dstAddress) {
 __asm__("vmovhps  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM5(void* dstAddress) {
 __asm__("vmovhps  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM6(void* dstAddress) {
 __asm__("vmovhps  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM7(void* dstAddress) {
 __asm__("vmovhps  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM8(void* dstAddress) {
 __asm__("vmovhps  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM9(void* dstAddress) {
 __asm__("vmovhps  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM10(void* dstAddress) {
 __asm__("vmovhps  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM11(void* dstAddress) {
 __asm__("vmovhps  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM12(void* dstAddress) {
 __asm__("vmovhps  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM13(void* dstAddress) {
 __asm__("vmovhps  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM14(void* dstAddress) {
 __asm__("vmovhps  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPS_XMM15(void* dstAddress) {
 __asm__("vmovhps  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM0(void* dstAddress) {
 __asm__("vmovhpd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM1(void* dstAddress) {
 __asm__("vmovhpd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM2(void* dstAddress) {
 __asm__("vmovhpd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM3(void* dstAddress) {
 __asm__("vmovhpd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM4(void* dstAddress) {
 __asm__("vmovhpd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM5(void* dstAddress) {
 __asm__("vmovhpd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM6(void* dstAddress) {
 __asm__("vmovhpd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM7(void* dstAddress) {
 __asm__("vmovhpd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM8(void* dstAddress) {
 __asm__("vmovhpd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM9(void* dstAddress) {
 __asm__("vmovhpd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM10(void* dstAddress) {
 __asm__("vmovhpd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM11(void* dstAddress) {
 __asm__("vmovhpd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM12(void* dstAddress) {
 __asm__("vmovhpd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM13(void* dstAddress) {
 __asm__("vmovhpd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM14(void* dstAddress) {
 __asm__("vmovhpd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVHPD_XMM15(void* dstAddress) {
 __asm__("vmovhpd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM0(void* dstAddress) {
 __asm__("movaps  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM1(void* dstAddress) {
 __asm__("movaps  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM2(void* dstAddress) {
 __asm__("movaps  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM3(void* dstAddress) {
 __asm__("movaps  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM4(void* dstAddress) {
 __asm__("movaps  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM5(void* dstAddress) {
 __asm__("movaps  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM6(void* dstAddress) {
 __asm__("movaps  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM7(void* dstAddress) {
 __asm__("movaps  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM8(void* dstAddress) {
 __asm__("movaps  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM9(void* dstAddress) {
 __asm__("movaps  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM10(void* dstAddress) {
 __asm__("movaps  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM11(void* dstAddress) {
 __asm__("movaps  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM12(void* dstAddress) {
 __asm__("movaps  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM13(void* dstAddress) {
 __asm__("movaps  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM14(void* dstAddress) {
 __asm__("movaps  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPS_XMM15(void* dstAddress) {
 __asm__("movaps  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM0(void* dstAddress) {
 __asm__("movapd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM1(void* dstAddress) {
 __asm__("movapd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM2(void* dstAddress) {
 __asm__("movapd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM3(void* dstAddress) {
 __asm__("movapd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM4(void* dstAddress) {
 __asm__("movapd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM5(void* dstAddress) {
 __asm__("movapd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM6(void* dstAddress) {
 __asm__("movapd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM7(void* dstAddress) {
 __asm__("movapd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM8(void* dstAddress) {
 __asm__("movapd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM9(void* dstAddress) {
 __asm__("movapd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM10(void* dstAddress) {
 __asm__("movapd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM11(void* dstAddress) {
 __asm__("movapd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM12(void* dstAddress) {
 __asm__("movapd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM13(void* dstAddress) {
 __asm__("movapd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM14(void* dstAddress) {
 __asm__("movapd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVAPD_XMM15(void* dstAddress) {
 __asm__("movapd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM0(void* dstAddress) {
 __asm__("vmovaps  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM1(void* dstAddress) {
 __asm__("vmovaps  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM2(void* dstAddress) {
 __asm__("vmovaps  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM3(void* dstAddress) {
 __asm__("vmovaps  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM4(void* dstAddress) {
 __asm__("vmovaps  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM5(void* dstAddress) {
 __asm__("vmovaps  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM6(void* dstAddress) {
 __asm__("vmovaps  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM7(void* dstAddress) {
 __asm__("vmovaps  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM8(void* dstAddress) {
 __asm__("vmovaps  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM9(void* dstAddress) {
 __asm__("vmovaps  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM10(void* dstAddress) {
 __asm__("vmovaps  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM11(void* dstAddress) {
 __asm__("vmovaps  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM12(void* dstAddress) {
 __asm__("vmovaps  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM13(void* dstAddress) {
 __asm__("vmovaps  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM14(void* dstAddress) {
 __asm__("vmovaps  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPS_XMM15(void* dstAddress) {
 __asm__("vmovaps  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM0(void* dstAddress) {
 __asm__("vmovapd  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM1(void* dstAddress) {
 __asm__("vmovapd  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM2(void* dstAddress) {
 __asm__("vmovapd  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM3(void* dstAddress) {
 __asm__("vmovapd  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM4(void* dstAddress) {
 __asm__("vmovapd  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM5(void* dstAddress) {
 __asm__("vmovapd  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM6(void* dstAddress) {
 __asm__("vmovapd  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM7(void* dstAddress) {
 __asm__("vmovapd  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM8(void* dstAddress) {
 __asm__("vmovapd  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM9(void* dstAddress) {
 __asm__("vmovapd  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM10(void* dstAddress) {
 __asm__("vmovapd  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM11(void* dstAddress) {
 __asm__("vmovapd  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM12(void* dstAddress) {
 __asm__("vmovapd  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM13(void* dstAddress) {
 __asm__("vmovapd  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM14(void* dstAddress) {
 __asm__("vmovapd  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVAPD_XMM15(void* dstAddress) {
 __asm__("vmovapd  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM0(void* dstAddress) {
 __asm__("movdqa  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM1(void* dstAddress) {
 __asm__("movdqa  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM2(void* dstAddress) {
 __asm__("movdqa  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM3(void* dstAddress) {
 __asm__("movdqa  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM4(void* dstAddress) {
 __asm__("movdqa  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM5(void* dstAddress) {
 __asm__("movdqa  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM6(void* dstAddress) {
 __asm__("movdqa  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM7(void* dstAddress) {
 __asm__("movdqa  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM8(void* dstAddress) {
 __asm__("movdqa  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM9(void* dstAddress) {
 __asm__("movdqa  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM10(void* dstAddress) {
 __asm__("movdqa  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM11(void* dstAddress) {
 __asm__("movdqa  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM12(void* dstAddress) {
 __asm__("movdqa  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM13(void* dstAddress) {
 __asm__("movdqa  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM14(void* dstAddress) {
 __asm__("movdqa  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQA_XMM15(void* dstAddress) {
 __asm__("movdqa  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM0(void* dstAddress) {
 __asm__("movdqu  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM1(void* dstAddress) {
 __asm__("movdqu  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM2(void* dstAddress) {
 __asm__("movdqu  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM3(void* dstAddress) {
 __asm__("movdqu  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM4(void* dstAddress) {
 __asm__("movdqu  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM5(void* dstAddress) {
 __asm__("movdqu  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM6(void* dstAddress) {
 __asm__("movdqu  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM7(void* dstAddress) {
 __asm__("movdqu  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM8(void* dstAddress) {
 __asm__("movdqu  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM9(void* dstAddress) {
 __asm__("movdqu  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM10(void* dstAddress) {
 __asm__("movdqu  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM11(void* dstAddress) {
 __asm__("movdqu  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM12(void* dstAddress) {
 __asm__("movdqu  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM13(void* dstAddress) {
 __asm__("movdqu  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM14(void* dstAddress) {
 __asm__("movdqu  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void MOVDQU_XMM15(void* dstAddress) {
 __asm__("movdqu  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM0(void* dstAddress) {
 __asm__("vmovdqa  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM1(void* dstAddress) {
 __asm__("vmovdqa  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM2(void* dstAddress) {
 __asm__("vmovdqa  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM3(void* dstAddress) {
 __asm__("vmovdqa  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM4(void* dstAddress) {
 __asm__("vmovdqa  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM5(void* dstAddress) {
 __asm__("vmovdqa  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM6(void* dstAddress) {
 __asm__("vmovdqa  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM7(void* dstAddress) {
 __asm__("vmovdqa  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM8(void* dstAddress) {
 __asm__("vmovdqa  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM9(void* dstAddress) {
 __asm__("vmovdqa  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM10(void* dstAddress) {
 __asm__("vmovdqa  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM11(void* dstAddress) {
 __asm__("vmovdqa  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM12(void* dstAddress) {
 __asm__("vmovdqa  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM13(void* dstAddress) {
 __asm__("vmovdqa  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM14(void* dstAddress) {
 __asm__("vmovdqa  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQA_XMM15(void* dstAddress) {
 __asm__("vmovdqa  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM0(void* dstAddress) {
 __asm__("vmovdqu  %%xmm0, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM1(void* dstAddress) {
 __asm__("vmovdqu  %%xmm1, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM2(void* dstAddress) {
 __asm__("vmovdqu  %%xmm2, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM3(void* dstAddress) {
 __asm__("vmovdqu  %%xmm3, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM4(void* dstAddress) {
 __asm__("vmovdqu  %%xmm4, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM5(void* dstAddress) {
 __asm__("vmovdqu  %%xmm5, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM6(void* dstAddress) {
 __asm__("vmovdqu  %%xmm6, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM7(void* dstAddress) {
 __asm__("vmovdqu  %%xmm7, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM8(void* dstAddress) {
 __asm__("vmovdqu  %%xmm8, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM9(void* dstAddress) {
 __asm__("vmovdqu  %%xmm9, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM10(void* dstAddress) {
 __asm__("vmovdqu  %%xmm10, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM11(void* dstAddress) {
 __asm__("vmovdqu  %%xmm11, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM12(void* dstAddress) {
 __asm__("vmovdqu  %%xmm12, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM13(void* dstAddress) {
 __asm__("vmovdqu  %%xmm13, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM14(void* dstAddress) {
 __asm__("vmovdqu  %%xmm14, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}

void VMOVDQU_XMM15(void* dstAddress) {
 __asm__("vmovdqu  %%xmm15, (%%rdi)\n\t"
         : /*no output registers*/
         : "D"(dstAddress) /*input registers*/
         : /*no clobbered registers*/
         );
}


typedef void (*movInsnFun)(void* dstAddress, uint64_t srcValue);


typedef void (*simdMovInsnFun)(void* dstAddress);


typedef void (*writeFlagsInsnFun)(void* dstAddress, uint64_t srcValue, uint64_t* flags);

movInsnFun NoWriteFlagsOpcode2FunTable_SIL[] = {
 SETB_FLAGS,
 SETNZ_FLAGS,
 MOV_SIL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL
};

writeFlagsInsnFun WriteFlagsOpcode2FunTable_SIL[] = {
 NULL,
 NULL,
 NULL,
 ADD_SIL,
 AND_SIL,
 OR_SIL,
 SUB_SIL,
 SAR_CL,
 SHL_CL,
 SHR_CL,
 NULL
};

movInsnFun NoWriteFlagsOpcode2FunTable_AH[] = {
 SETB_FLAGS,
 SETNZ_FLAGS,
 MOV_AH,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL
};

writeFlagsInsnFun WriteFlagsOpcode2FunTable_AH[] = {
 NULL,
 NULL,
 NULL,
 ADD_AH,
 AND_AH,
 OR_AH,
 SUB_AH,
 NULL,
 NULL,
 NULL,
 NULL
};

movInsnFun NoWriteFlagsOpcode2FunTable_SI[] = {
 SETB_FLAGS,
 SETNZ_FLAGS,
 MOV_SI,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL
};

writeFlagsInsnFun WriteFlagsOpcode2FunTable_SI[] = {
 NULL,
 NULL,
 NULL,
 ADD_SI,
 AND_SI,
 OR_SI,
 SUB_SI,
 NULL,
 NULL,
 NULL,
 NULL
};

movInsnFun NoWriteFlagsOpcode2FunTable_ESI[] = {
 SETB_FLAGS,
 SETNZ_FLAGS,
 MOV_ESI,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL
};

writeFlagsInsnFun WriteFlagsOpcode2FunTable_ESI[] = {
 NULL,
 NULL,
 NULL,
 ADD_ESI,
 AND_ESI,
 OR_ESI,
 SUB_ESI,
 NULL,
 NULL,
 NULL,
 NULL
};

movInsnFun NoWriteFlagsOpcode2FunTable_RSI[] = {
 SETB_FLAGS,
 SETNZ_FLAGS,
 MOV_RSI,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL
};

writeFlagsInsnFun WriteFlagsOpcode2FunTable_RSI[] = {
 NULL,
 NULL,
 NULL,
 ADD_RSI,
 AND_RSI,
 OR_RSI,
 SUB_RSI,
 NULL,
 NULL,
 NULL,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVD[] = {
 MOVD_MMX0,
 MOVD_MMX1,
 MOVD_MMX2,
 MOVD_MMX3,
 MOVD_MMX4,
 MOVD_MMX5,
 MOVD_MMX6,
 MOVD_MMX7,
 MOVD_XMM0,
 MOVD_XMM1,
 MOVD_XMM2,
 MOVD_XMM3,
 MOVD_XMM4,
 MOVD_XMM5,
 MOVD_XMM6,
 MOVD_XMM7,
 MOVD_XMM8,
 MOVD_XMM9,
 MOVD_XMM10,
 MOVD_XMM11,
 MOVD_XMM12,
 MOVD_XMM13,
 MOVD_XMM14,
 MOVD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVSS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVSS_XMM0,
 MOVSS_XMM1,
 MOVSS_XMM2,
 MOVSS_XMM3,
 MOVSS_XMM4,
 MOVSS_XMM5,
 MOVSS_XMM6,
 MOVSS_XMM7,
 MOVSS_XMM8,
 MOVSS_XMM9,
 MOVSS_XMM10,
 MOVSS_XMM11,
 MOVSS_XMM12,
 MOVSS_XMM13,
 MOVSS_XMM14,
 MOVSS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVQ[] = {
 MOVQ_MMX0,
 MOVQ_MMX1,
 MOVQ_MMX2,
 MOVQ_MMX3,
 MOVQ_MMX4,
 MOVQ_MMX5,
 MOVQ_MMX6,
 MOVQ_MMX7,
 MOVQ_XMM0,
 MOVQ_XMM1,
 MOVQ_XMM2,
 MOVQ_XMM3,
 MOVQ_XMM4,
 MOVQ_XMM5,
 MOVQ_XMM6,
 MOVQ_XMM7,
 MOVQ_XMM8,
 MOVQ_XMM9,
 MOVQ_XMM10,
 MOVQ_XMM11,
 MOVQ_XMM12,
 MOVQ_XMM13,
 MOVQ_XMM14,
 MOVQ_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVUPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVUPS_XMM0,
 MOVUPS_XMM1,
 MOVUPS_XMM2,
 MOVUPS_XMM3,
 MOVUPS_XMM4,
 MOVUPS_XMM5,
 MOVUPS_XMM6,
 MOVUPS_XMM7,
 MOVUPS_XMM8,
 MOVUPS_XMM9,
 MOVUPS_XMM10,
 MOVUPS_XMM11,
 MOVUPS_XMM12,
 MOVUPS_XMM13,
 MOVUPS_XMM14,
 MOVUPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVUPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVUPD_XMM0,
 MOVUPD_XMM1,
 MOVUPD_XMM2,
 MOVUPD_XMM3,
 MOVUPD_XMM4,
 MOVUPD_XMM5,
 MOVUPD_XMM6,
 MOVUPD_XMM7,
 MOVUPD_XMM8,
 MOVUPD_XMM9,
 MOVUPD_XMM10,
 MOVUPD_XMM11,
 MOVUPD_XMM12,
 MOVUPD_XMM13,
 MOVUPD_XMM14,
 MOVUPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVUPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVUPS_XMM0,
 VMOVUPS_XMM1,
 VMOVUPS_XMM2,
 VMOVUPS_XMM3,
 VMOVUPS_XMM4,
 VMOVUPS_XMM5,
 VMOVUPS_XMM6,
 VMOVUPS_XMM7,
 VMOVUPS_XMM8,
 VMOVUPS_XMM9,
 VMOVUPS_XMM10,
 VMOVUPS_XMM11,
 VMOVUPS_XMM12,
 VMOVUPS_XMM13,
 VMOVUPS_XMM14,
 VMOVUPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVUPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVUPD_XMM0,
 VMOVUPD_XMM1,
 VMOVUPD_XMM2,
 VMOVUPD_XMM3,
 VMOVUPD_XMM4,
 VMOVUPD_XMM5,
 VMOVUPD_XMM6,
 VMOVUPD_XMM7,
 VMOVUPD_XMM8,
 VMOVUPD_XMM9,
 VMOVUPD_XMM10,
 VMOVUPD_XMM11,
 VMOVUPD_XMM12,
 VMOVUPD_XMM13,
 VMOVUPD_XMM14,
 VMOVUPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVSS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVSS_XMM0,
 VMOVSS_XMM1,
 VMOVSS_XMM2,
 VMOVSS_XMM3,
 VMOVSS_XMM4,
 VMOVSS_XMM5,
 VMOVSS_XMM6,
 VMOVSS_XMM7,
 VMOVSS_XMM8,
 VMOVSS_XMM9,
 VMOVSS_XMM10,
 VMOVSS_XMM11,
 VMOVSS_XMM12,
 VMOVSS_XMM13,
 VMOVSS_XMM14,
 VMOVSS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVSD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVSD_XMM0,
 VMOVSD_XMM1,
 VMOVSD_XMM2,
 VMOVSD_XMM3,
 VMOVSD_XMM4,
 VMOVSD_XMM5,
 VMOVSD_XMM6,
 VMOVSD_XMM7,
 VMOVSD_XMM8,
 VMOVSD_XMM9,
 VMOVSD_XMM10,
 VMOVSD_XMM11,
 VMOVSD_XMM12,
 VMOVSD_XMM13,
 VMOVSD_XMM14,
 VMOVSD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVLPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVLPS_XMM0,
 MOVLPS_XMM1,
 MOVLPS_XMM2,
 MOVLPS_XMM3,
 MOVLPS_XMM4,
 MOVLPS_XMM5,
 MOVLPS_XMM6,
 MOVLPS_XMM7,
 MOVLPS_XMM8,
 MOVLPS_XMM9,
 MOVLPS_XMM10,
 MOVLPS_XMM11,
 MOVLPS_XMM12,
 MOVLPS_XMM13,
 MOVLPS_XMM14,
 MOVLPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVLPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVLPD_XMM0,
 MOVLPD_XMM1,
 MOVLPD_XMM2,
 MOVLPD_XMM3,
 MOVLPD_XMM4,
 MOVLPD_XMM5,
 MOVLPD_XMM6,
 MOVLPD_XMM7,
 MOVLPD_XMM8,
 MOVLPD_XMM9,
 MOVLPD_XMM10,
 MOVLPD_XMM11,
 MOVLPD_XMM12,
 MOVLPD_XMM13,
 MOVLPD_XMM14,
 MOVLPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVLPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVLPS_XMM0,
 VMOVLPS_XMM1,
 VMOVLPS_XMM2,
 VMOVLPS_XMM3,
 VMOVLPS_XMM4,
 VMOVLPS_XMM5,
 VMOVLPS_XMM6,
 VMOVLPS_XMM7,
 VMOVLPS_XMM8,
 VMOVLPS_XMM9,
 VMOVLPS_XMM10,
 VMOVLPS_XMM11,
 VMOVLPS_XMM12,
 VMOVLPS_XMM13,
 VMOVLPS_XMM14,
 VMOVLPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVLPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVLPD_XMM0,
 VMOVLPD_XMM1,
 VMOVLPD_XMM2,
 VMOVLPD_XMM3,
 VMOVLPD_XMM4,
 VMOVLPD_XMM5,
 VMOVLPD_XMM6,
 VMOVLPD_XMM7,
 VMOVLPD_XMM8,
 VMOVLPD_XMM9,
 VMOVLPD_XMM10,
 VMOVLPD_XMM11,
 VMOVLPD_XMM12,
 VMOVLPD_XMM13,
 VMOVLPD_XMM14,
 VMOVLPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVHPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVHPS_XMM0,
 MOVHPS_XMM1,
 MOVHPS_XMM2,
 MOVHPS_XMM3,
 MOVHPS_XMM4,
 MOVHPS_XMM5,
 MOVHPS_XMM6,
 MOVHPS_XMM7,
 MOVHPS_XMM8,
 MOVHPS_XMM9,
 MOVHPS_XMM10,
 MOVHPS_XMM11,
 MOVHPS_XMM12,
 MOVHPS_XMM13,
 MOVHPS_XMM14,
 MOVHPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVHPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVHPD_XMM0,
 MOVHPD_XMM1,
 MOVHPD_XMM2,
 MOVHPD_XMM3,
 MOVHPD_XMM4,
 MOVHPD_XMM5,
 MOVHPD_XMM6,
 MOVHPD_XMM7,
 MOVHPD_XMM8,
 MOVHPD_XMM9,
 MOVHPD_XMM10,
 MOVHPD_XMM11,
 MOVHPD_XMM12,
 MOVHPD_XMM13,
 MOVHPD_XMM14,
 MOVHPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVHPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVHPS_XMM0,
 VMOVHPS_XMM1,
 VMOVHPS_XMM2,
 VMOVHPS_XMM3,
 VMOVHPS_XMM4,
 VMOVHPS_XMM5,
 VMOVHPS_XMM6,
 VMOVHPS_XMM7,
 VMOVHPS_XMM8,
 VMOVHPS_XMM9,
 VMOVHPS_XMM10,
 VMOVHPS_XMM11,
 VMOVHPS_XMM12,
 VMOVHPS_XMM13,
 VMOVHPS_XMM14,
 VMOVHPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVHPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVHPD_XMM0,
 VMOVHPD_XMM1,
 VMOVHPD_XMM2,
 VMOVHPD_XMM3,
 VMOVHPD_XMM4,
 VMOVHPD_XMM5,
 VMOVHPD_XMM6,
 VMOVHPD_XMM7,
 VMOVHPD_XMM8,
 VMOVHPD_XMM9,
 VMOVHPD_XMM10,
 VMOVHPD_XMM11,
 VMOVHPD_XMM12,
 VMOVHPD_XMM13,
 VMOVHPD_XMM14,
 VMOVHPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVAPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVAPS_XMM0,
 MOVAPS_XMM1,
 MOVAPS_XMM2,
 MOVAPS_XMM3,
 MOVAPS_XMM4,
 MOVAPS_XMM5,
 MOVAPS_XMM6,
 MOVAPS_XMM7,
 MOVAPS_XMM8,
 MOVAPS_XMM9,
 MOVAPS_XMM10,
 MOVAPS_XMM11,
 MOVAPS_XMM12,
 MOVAPS_XMM13,
 MOVAPS_XMM14,
 MOVAPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVAPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVAPD_XMM0,
 MOVAPD_XMM1,
 MOVAPD_XMM2,
 MOVAPD_XMM3,
 MOVAPD_XMM4,
 MOVAPD_XMM5,
 MOVAPD_XMM6,
 MOVAPD_XMM7,
 MOVAPD_XMM8,
 MOVAPD_XMM9,
 MOVAPD_XMM10,
 MOVAPD_XMM11,
 MOVAPD_XMM12,
 MOVAPD_XMM13,
 MOVAPD_XMM14,
 MOVAPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVAPS[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVAPS_XMM0,
 VMOVAPS_XMM1,
 VMOVAPS_XMM2,
 VMOVAPS_XMM3,
 VMOVAPS_XMM4,
 VMOVAPS_XMM5,
 VMOVAPS_XMM6,
 VMOVAPS_XMM7,
 VMOVAPS_XMM8,
 VMOVAPS_XMM9,
 VMOVAPS_XMM10,
 VMOVAPS_XMM11,
 VMOVAPS_XMM12,
 VMOVAPS_XMM13,
 VMOVAPS_XMM14,
 VMOVAPS_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVAPD[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVAPD_XMM0,
 VMOVAPD_XMM1,
 VMOVAPD_XMM2,
 VMOVAPD_XMM3,
 VMOVAPD_XMM4,
 VMOVAPD_XMM5,
 VMOVAPD_XMM6,
 VMOVAPD_XMM7,
 VMOVAPD_XMM8,
 VMOVAPD_XMM9,
 VMOVAPD_XMM10,
 VMOVAPD_XMM11,
 VMOVAPD_XMM12,
 VMOVAPD_XMM13,
 VMOVAPD_XMM14,
 VMOVAPD_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVDQA[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVDQA_XMM0,
 MOVDQA_XMM1,
 MOVDQA_XMM2,
 MOVDQA_XMM3,
 MOVDQA_XMM4,
 MOVDQA_XMM5,
 MOVDQA_XMM6,
 MOVDQA_XMM7,
 MOVDQA_XMM8,
 MOVDQA_XMM9,
 MOVDQA_XMM10,
 MOVDQA_XMM11,
 MOVDQA_XMM12,
 MOVDQA_XMM13,
 MOVDQA_XMM14,
 MOVDQA_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_MOVDQU[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 MOVDQU_XMM0,
 MOVDQU_XMM1,
 MOVDQU_XMM2,
 MOVDQU_XMM3,
 MOVDQU_XMM4,
 MOVDQU_XMM5,
 MOVDQU_XMM6,
 MOVDQU_XMM7,
 MOVDQU_XMM8,
 MOVDQU_XMM9,
 MOVDQU_XMM10,
 MOVDQU_XMM11,
 MOVDQU_XMM12,
 MOVDQU_XMM13,
 MOVDQU_XMM14,
 MOVDQU_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVDQA[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVDQA_XMM0,
 VMOVDQA_XMM1,
 VMOVDQA_XMM2,
 VMOVDQA_XMM3,
 VMOVDQA_XMM4,
 VMOVDQA_XMM5,
 VMOVDQA_XMM6,
 VMOVDQA_XMM7,
 VMOVDQA_XMM8,
 VMOVDQA_XMM9,
 VMOVDQA_XMM10,
 VMOVDQA_XMM11,
 VMOVDQA_XMM12,
 VMOVDQA_XMM13,
 VMOVDQA_XMM14,
 VMOVDQA_XMM15,
 NULL
};

simdMovInsnFun SIMDReg2FunTable_VMOVDQU[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 VMOVDQU_XMM0,
 VMOVDQU_XMM1,
 VMOVDQU_XMM2,
 VMOVDQU_XMM3,
 VMOVDQU_XMM4,
 VMOVDQU_XMM5,
 VMOVDQU_XMM6,
 VMOVDQU_XMM7,
 VMOVDQU_XMM8,
 VMOVDQU_XMM9,
 VMOVDQU_XMM10,
 VMOVDQU_XMM11,
 VMOVDQU_XMM12,
 VMOVDQU_XMM13,
 VMOVDQU_XMM14,
 VMOVDQU_XMM15,
 NULL
};

simdMovInsnFun* SIMDOpcode2RegTable[] = {
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 SIMDReg2FunTable_MOVD,
 SIMDReg2FunTable_MOVSS,
 SIMDReg2FunTable_MOVQ,
 SIMDReg2FunTable_MOVUPS,
 SIMDReg2FunTable_MOVUPD,
 SIMDReg2FunTable_VMOVUPS,
 SIMDReg2FunTable_VMOVUPD,
 SIMDReg2FunTable_VMOVSS,
 SIMDReg2FunTable_VMOVSD,
 SIMDReg2FunTable_MOVLPS,
 SIMDReg2FunTable_MOVLPD,
 SIMDReg2FunTable_VMOVLPS,
 SIMDReg2FunTable_VMOVLPD,
 SIMDReg2FunTable_MOVHPS,
 SIMDReg2FunTable_MOVHPD,
 SIMDReg2FunTable_VMOVHPS,
 SIMDReg2FunTable_VMOVHPD,
 SIMDReg2FunTable_MOVAPS,
 SIMDReg2FunTable_MOVAPD,
 SIMDReg2FunTable_VMOVAPS,
 SIMDReg2FunTable_VMOVAPD,
 SIMDReg2FunTable_MOVDQA,
 SIMDReg2FunTable_MOVDQU,
 SIMDReg2FunTable_VMOVDQA,
 SIMDReg2FunTable_VMOVDQU,
 NULL
};

void verifyOpcodesAndRegisters() {
// verify opcodes
 assert(0 == UD_Isetb);
 assert(1 == UD_Isetnz);
 assert(2 == UD_Imov);
 assert(3 == UD_Iadd);
 assert(4 == UD_Iand);
 assert(5 == UD_Ior);
 assert(6 == UD_Isub);
 assert(7 == UD_Isar);
 assert(8 == UD_Ishl);
 assert(9 == UD_Ishr);
 assert(10 == UD_Imovd);
 assert(11 == UD_Imovss);
 assert(12 == UD_Imovq);
 assert(13 == UD_Imovups);
 assert(14 == UD_Imovupd);
 assert(15 == UD_Ivmovups);
 assert(16 == UD_Ivmovupd);
 assert(17 == UD_Ivmovss);
 assert(18 == UD_Ivmovsd);
 assert(19 == UD_Imovlps);
 assert(20 == UD_Imovlpd);
 assert(21 == UD_Ivmovlps);
 assert(22 == UD_Ivmovlpd);
 assert(23 == UD_Imovhps);
 assert(24 == UD_Imovhpd);
 assert(25 == UD_Ivmovhps);
 assert(26 == UD_Ivmovhpd);
 assert(27 == UD_Imovaps);
 assert(28 == UD_Imovapd);
 assert(29 == UD_Ivmovaps);
 assert(30 == UD_Ivmovapd);
 assert(31 == UD_Imovdqa);
 assert(32 == UD_Imovdqu);
 assert(33 == UD_Ivmovdqa);
 assert(34 == UD_Ivmovdqu);
// verify register mapping
 assert(0 == (UD_R_MM0 - UD_R_MM0));
 assert(1 == (UD_R_MM1 - UD_R_MM0));
 assert(2 == (UD_R_MM2 - UD_R_MM0));
 assert(3 == (UD_R_MM3 - UD_R_MM0));
 assert(4 == (UD_R_MM4 - UD_R_MM0));
 assert(5 == (UD_R_MM5 - UD_R_MM0));
 assert(6 == (UD_R_MM6 - UD_R_MM0));
 assert(7 == (UD_R_MM7 - UD_R_MM0));
 assert(8 == (UD_R_XMM0 - UD_R_MM0));
 assert(9 == (UD_R_XMM1 - UD_R_MM0));
 assert(10 == (UD_R_XMM2 - UD_R_MM0));
 assert(11 == (UD_R_XMM3 - UD_R_MM0));
 assert(12 == (UD_R_XMM4 - UD_R_MM0));
 assert(13 == (UD_R_XMM5 - UD_R_MM0));
 assert(14 == (UD_R_XMM6 - UD_R_MM0));
 assert(15 == (UD_R_XMM7 - UD_R_MM0));
 assert(16 == (UD_R_XMM8 - UD_R_MM0));
 assert(17 == (UD_R_XMM9 - UD_R_MM0));
 assert(18 == (UD_R_XMM10 - UD_R_MM0));
 assert(19 == (UD_R_XMM11 - UD_R_MM0));
 assert(20 == (UD_R_XMM12 - UD_R_MM0));
 assert(21 == (UD_R_XMM13 - UD_R_MM0));
 assert(22 == (UD_R_XMM14 - UD_R_MM0));
 assert(23 == (UD_R_XMM15 - UD_R_MM0));
}
struct test_insn { const uint8_t bytes[15]; const ud_mnemonic_code_t expectedOpcode; };
struct test_insn TEST_INSNS[] = {
 { .bytes = { 0x67,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%eax)
 { .bytes = { 0x67,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%ecx)
 { .bytes = { 0x67,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%edx)
 { .bytes = { 0x67,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%ebx)
 { .bytes = { 0x67,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%esp)
 { .bytes = { 0x67,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%ebp)
 { .bytes = { 0x67,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%esi)
 { .bytes = { 0x67,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movl  %eax, (%r15d)
 { .bytes = { 0x67,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%eax)
 { .bytes = { 0x67,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%ecx)
 { .bytes = { 0x67,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%edx)
 { .bytes = { 0x67,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%ebx)
 { .bytes = { 0x67,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%esp)
 { .bytes = { 0x67,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%ebp)
 { .bytes = { 0x67,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%esi)
 { .bytes = { 0x67,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movl  %ecx, (%r15d)
 { .bytes = { 0x67,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%eax)
 { .bytes = { 0x67,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%ecx)
 { .bytes = { 0x67,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%edx)
 { .bytes = { 0x67,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%ebx)
 { .bytes = { 0x67,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%esp)
 { .bytes = { 0x67,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%ebp)
 { .bytes = { 0x67,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%esi)
 { .bytes = { 0x67,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movl  %edx, (%r15d)
 { .bytes = { 0x67,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%eax)
 { .bytes = { 0x67,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%ecx)
 { .bytes = { 0x67,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%edx)
 { .bytes = { 0x67,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%ebx)
 { .bytes = { 0x67,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%esp)
 { .bytes = { 0x67,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%ebp)
 { .bytes = { 0x67,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%esi)
 { .bytes = { 0x67,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movl  %ebx, (%r15d)
 { .bytes = { 0x67,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%eax)
 { .bytes = { 0x67,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%ecx)
 { .bytes = { 0x67,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%edx)
 { .bytes = { 0x67,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%ebx)
 { .bytes = { 0x67,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%esp)
 { .bytes = { 0x67,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%ebp)
 { .bytes = { 0x67,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%esi)
 { .bytes = { 0x67,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movl  %esp, (%r15d)
 { .bytes = { 0x67,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%eax)
 { .bytes = { 0x67,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%ecx)
 { .bytes = { 0x67,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%edx)
 { .bytes = { 0x67,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%ebx)
 { .bytes = { 0x67,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%esp)
 { .bytes = { 0x67,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%ebp)
 { .bytes = { 0x67,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%esi)
 { .bytes = { 0x67,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movl  %ebp, (%r15d)
 { .bytes = { 0x67,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%eax)
 { .bytes = { 0x67,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%ecx)
 { .bytes = { 0x67,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%edx)
 { .bytes = { 0x67,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%ebx)
 { .bytes = { 0x67,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%esp)
 { .bytes = { 0x67,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%ebp)
 { .bytes = { 0x67,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%esi)
 { .bytes = { 0x67,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movl  %esi, (%r15d)
 { .bytes = { 0x67,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%eax)
 { .bytes = { 0x67,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%ecx)
 { .bytes = { 0x67,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%edx)
 { .bytes = { 0x67,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%ebx)
 { .bytes = { 0x67,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%esp)
 { .bytes = { 0x67,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%ebp)
 { .bytes = { 0x67,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%esi)
 { .bytes = { 0x67,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%edi)
 { .bytes = { 0x67,0x41,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r8d)
 { .bytes = { 0x67,0x41,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r9d)
 { .bytes = { 0x67,0x41,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r10d)
 { .bytes = { 0x67,0x41,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r11d)
 { .bytes = { 0x67,0x41,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r12d)
 { .bytes = { 0x67,0x41,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r13d)
 { .bytes = { 0x67,0x41,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r14d)
 { .bytes = { 0x67,0x41,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movl  %edi, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movl  %r8d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movl  %r9d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movl  %r10d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movl  %r11d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movl  %r12d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movl  %r13d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movl  %r14d, (%r15d)
 { .bytes = { 0x67,0x44,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%eax)
 { .bytes = { 0x67,0x44,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%ecx)
 { .bytes = { 0x67,0x44,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%edx)
 { .bytes = { 0x67,0x44,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%ebx)
 { .bytes = { 0x67,0x44,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%esp)
 { .bytes = { 0x67,0x44,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%ebp)
 { .bytes = { 0x67,0x44,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%esi)
 { .bytes = { 0x67,0x44,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%edi)
 { .bytes = { 0x67,0x45,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r8d)
 { .bytes = { 0x67,0x45,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r9d)
 { .bytes = { 0x67,0x45,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r10d)
 { .bytes = { 0x67,0x45,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r11d)
 { .bytes = { 0x67,0x45,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r12d)
 { .bytes = { 0x67,0x45,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r13d)
 { .bytes = { 0x67,0x45,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r14d)
 { .bytes = { 0x67,0x45,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movl  %r15d, (%r15d)
 { .bytes = { 0x48,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rax)
 { .bytes = { 0x48,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rcx)
 { .bytes = { 0x48,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rdx)
 { .bytes = { 0x48,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rbx)
 { .bytes = { 0x48,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rsp)
 { .bytes = { 0x48,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rbp)
 { .bytes = { 0x48,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rsi)
 { .bytes = { 0x48,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%rdi)
 { .bytes = { 0x49,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r8)
 { .bytes = { 0x49,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r9)
 { .bytes = { 0x49,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r10)
 { .bytes = { 0x49,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r11)
 { .bytes = { 0x49,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r12)
 { .bytes = { 0x49,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r13)
 { .bytes = { 0x49,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r14)
 { .bytes = { 0x49,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movq  %rax, (%r15)
 { .bytes = { 0x48,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rax)
 { .bytes = { 0x48,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rcx)
 { .bytes = { 0x48,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rdx)
 { .bytes = { 0x48,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rbx)
 { .bytes = { 0x48,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rsp)
 { .bytes = { 0x48,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rbp)
 { .bytes = { 0x48,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rsi)
 { .bytes = { 0x48,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%rdi)
 { .bytes = { 0x49,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r8)
 { .bytes = { 0x49,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r9)
 { .bytes = { 0x49,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r10)
 { .bytes = { 0x49,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r11)
 { .bytes = { 0x49,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r12)
 { .bytes = { 0x49,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r13)
 { .bytes = { 0x49,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r14)
 { .bytes = { 0x49,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movq  %rcx, (%r15)
 { .bytes = { 0x48,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rax)
 { .bytes = { 0x48,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rcx)
 { .bytes = { 0x48,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rdx)
 { .bytes = { 0x48,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rbx)
 { .bytes = { 0x48,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rsp)
 { .bytes = { 0x48,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rbp)
 { .bytes = { 0x48,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rsi)
 { .bytes = { 0x48,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%rdi)
 { .bytes = { 0x49,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r8)
 { .bytes = { 0x49,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r9)
 { .bytes = { 0x49,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r10)
 { .bytes = { 0x49,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r11)
 { .bytes = { 0x49,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r12)
 { .bytes = { 0x49,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r13)
 { .bytes = { 0x49,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r14)
 { .bytes = { 0x49,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movq  %rdx, (%r15)
 { .bytes = { 0x48,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rax)
 { .bytes = { 0x48,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rcx)
 { .bytes = { 0x48,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rdx)
 { .bytes = { 0x48,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rbx)
 { .bytes = { 0x48,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rsp)
 { .bytes = { 0x48,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rbp)
 { .bytes = { 0x48,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rsi)
 { .bytes = { 0x48,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%rdi)
 { .bytes = { 0x49,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r8)
 { .bytes = { 0x49,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r9)
 { .bytes = { 0x49,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r10)
 { .bytes = { 0x49,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r11)
 { .bytes = { 0x49,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r12)
 { .bytes = { 0x49,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r13)
 { .bytes = { 0x49,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r14)
 { .bytes = { 0x49,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movq  %rbx, (%r15)
 { .bytes = { 0x48,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rax)
 { .bytes = { 0x48,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rcx)
 { .bytes = { 0x48,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rdx)
 { .bytes = { 0x48,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rbx)
 { .bytes = { 0x48,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rsp)
 { .bytes = { 0x48,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rbp)
 { .bytes = { 0x48,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rsi)
 { .bytes = { 0x48,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%rdi)
 { .bytes = { 0x49,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r8)
 { .bytes = { 0x49,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r9)
 { .bytes = { 0x49,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r10)
 { .bytes = { 0x49,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r11)
 { .bytes = { 0x49,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r12)
 { .bytes = { 0x49,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r13)
 { .bytes = { 0x49,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r14)
 { .bytes = { 0x49,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movq  %rsp, (%r15)
 { .bytes = { 0x48,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rax)
 { .bytes = { 0x48,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rcx)
 { .bytes = { 0x48,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rdx)
 { .bytes = { 0x48,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rbx)
 { .bytes = { 0x48,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rsp)
 { .bytes = { 0x48,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rbp)
 { .bytes = { 0x48,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rsi)
 { .bytes = { 0x48,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%rdi)
 { .bytes = { 0x49,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r8)
 { .bytes = { 0x49,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r9)
 { .bytes = { 0x49,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r10)
 { .bytes = { 0x49,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r11)
 { .bytes = { 0x49,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r12)
 { .bytes = { 0x49,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r13)
 { .bytes = { 0x49,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r14)
 { .bytes = { 0x49,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movq  %rbp, (%r15)
 { .bytes = { 0x48,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rax)
 { .bytes = { 0x48,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rcx)
 { .bytes = { 0x48,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rdx)
 { .bytes = { 0x48,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rbx)
 { .bytes = { 0x48,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rsp)
 { .bytes = { 0x48,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rbp)
 { .bytes = { 0x48,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rsi)
 { .bytes = { 0x48,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%rdi)
 { .bytes = { 0x49,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r8)
 { .bytes = { 0x49,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r9)
 { .bytes = { 0x49,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r10)
 { .bytes = { 0x49,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r11)
 { .bytes = { 0x49,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r12)
 { .bytes = { 0x49,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r13)
 { .bytes = { 0x49,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r14)
 { .bytes = { 0x49,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movq  %rsi, (%r15)
 { .bytes = { 0x48,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rax)
 { .bytes = { 0x48,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rcx)
 { .bytes = { 0x48,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rdx)
 { .bytes = { 0x48,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rbx)
 { .bytes = { 0x48,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rsp)
 { .bytes = { 0x48,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rbp)
 { .bytes = { 0x48,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rsi)
 { .bytes = { 0x48,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%rdi)
 { .bytes = { 0x49,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r8)
 { .bytes = { 0x49,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r9)
 { .bytes = { 0x49,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r10)
 { .bytes = { 0x49,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r11)
 { .bytes = { 0x49,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r12)
 { .bytes = { 0x49,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r13)
 { .bytes = { 0x49,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r14)
 { .bytes = { 0x49,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movq  %rdi, (%r15)
 { .bytes = { 0x4c,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rax)
 { .bytes = { 0x4c,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rcx)
 { .bytes = { 0x4c,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rdx)
 { .bytes = { 0x4c,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rbx)
 { .bytes = { 0x4c,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rsp)
 { .bytes = { 0x4c,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rbp)
 { .bytes = { 0x4c,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rsi)
 { .bytes = { 0x4c,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%rdi)
 { .bytes = { 0x4d,0x89,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r8)
 { .bytes = { 0x4d,0x89,0x01, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r9)
 { .bytes = { 0x4d,0x89,0x02, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r10)
 { .bytes = { 0x4d,0x89,0x03, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r11)
 { .bytes = { 0x4d,0x89,0x04,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r12)
 { .bytes = { 0x4d,0x89,0x45,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r13)
 { .bytes = { 0x4d,0x89,0x06, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r14)
 { .bytes = { 0x4d,0x89,0x07, }, .expectedOpcode = UD_Imov }, // movq  %r8, (%r15)
 { .bytes = { 0x4c,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rax)
 { .bytes = { 0x4c,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rcx)
 { .bytes = { 0x4c,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rdx)
 { .bytes = { 0x4c,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rbx)
 { .bytes = { 0x4c,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rsp)
 { .bytes = { 0x4c,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rbp)
 { .bytes = { 0x4c,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rsi)
 { .bytes = { 0x4c,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%rdi)
 { .bytes = { 0x4d,0x89,0x08, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r8)
 { .bytes = { 0x4d,0x89,0x09, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r9)
 { .bytes = { 0x4d,0x89,0x0a, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r10)
 { .bytes = { 0x4d,0x89,0x0b, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r11)
 { .bytes = { 0x4d,0x89,0x0c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r12)
 { .bytes = { 0x4d,0x89,0x4d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r13)
 { .bytes = { 0x4d,0x89,0x0e, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r14)
 { .bytes = { 0x4d,0x89,0x0f, }, .expectedOpcode = UD_Imov }, // movq  %r9, (%r15)
 { .bytes = { 0x4c,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rax)
 { .bytes = { 0x4c,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rcx)
 { .bytes = { 0x4c,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rdx)
 { .bytes = { 0x4c,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rbx)
 { .bytes = { 0x4c,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rsp)
 { .bytes = { 0x4c,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rbp)
 { .bytes = { 0x4c,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rsi)
 { .bytes = { 0x4c,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%rdi)
 { .bytes = { 0x4d,0x89,0x10, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r8)
 { .bytes = { 0x4d,0x89,0x11, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r9)
 { .bytes = { 0x4d,0x89,0x12, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r10)
 { .bytes = { 0x4d,0x89,0x13, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r11)
 { .bytes = { 0x4d,0x89,0x14,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r12)
 { .bytes = { 0x4d,0x89,0x55,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r13)
 { .bytes = { 0x4d,0x89,0x16, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r14)
 { .bytes = { 0x4d,0x89,0x17, }, .expectedOpcode = UD_Imov }, // movq  %r10, (%r15)
 { .bytes = { 0x4c,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rax)
 { .bytes = { 0x4c,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rcx)
 { .bytes = { 0x4c,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rdx)
 { .bytes = { 0x4c,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rbx)
 { .bytes = { 0x4c,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rsp)
 { .bytes = { 0x4c,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rbp)
 { .bytes = { 0x4c,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rsi)
 { .bytes = { 0x4c,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%rdi)
 { .bytes = { 0x4d,0x89,0x18, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r8)
 { .bytes = { 0x4d,0x89,0x19, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r9)
 { .bytes = { 0x4d,0x89,0x1a, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r10)
 { .bytes = { 0x4d,0x89,0x1b, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r11)
 { .bytes = { 0x4d,0x89,0x1c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r12)
 { .bytes = { 0x4d,0x89,0x5d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r13)
 { .bytes = { 0x4d,0x89,0x1e, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r14)
 { .bytes = { 0x4d,0x89,0x1f, }, .expectedOpcode = UD_Imov }, // movq  %r11, (%r15)
 { .bytes = { 0x4c,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rax)
 { .bytes = { 0x4c,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rcx)
 { .bytes = { 0x4c,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rdx)
 { .bytes = { 0x4c,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rbx)
 { .bytes = { 0x4c,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rsp)
 { .bytes = { 0x4c,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rbp)
 { .bytes = { 0x4c,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rsi)
 { .bytes = { 0x4c,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%rdi)
 { .bytes = { 0x4d,0x89,0x20, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r8)
 { .bytes = { 0x4d,0x89,0x21, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r9)
 { .bytes = { 0x4d,0x89,0x22, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r10)
 { .bytes = { 0x4d,0x89,0x23, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r11)
 { .bytes = { 0x4d,0x89,0x24,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r12)
 { .bytes = { 0x4d,0x89,0x65,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r13)
 { .bytes = { 0x4d,0x89,0x26, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r14)
 { .bytes = { 0x4d,0x89,0x27, }, .expectedOpcode = UD_Imov }, // movq  %r12, (%r15)
 { .bytes = { 0x4c,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rax)
 { .bytes = { 0x4c,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rcx)
 { .bytes = { 0x4c,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rdx)
 { .bytes = { 0x4c,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rbx)
 { .bytes = { 0x4c,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rsp)
 { .bytes = { 0x4c,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rbp)
 { .bytes = { 0x4c,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rsi)
 { .bytes = { 0x4c,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%rdi)
 { .bytes = { 0x4d,0x89,0x28, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r8)
 { .bytes = { 0x4d,0x89,0x29, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r9)
 { .bytes = { 0x4d,0x89,0x2a, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r10)
 { .bytes = { 0x4d,0x89,0x2b, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r11)
 { .bytes = { 0x4d,0x89,0x2c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r12)
 { .bytes = { 0x4d,0x89,0x6d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r13)
 { .bytes = { 0x4d,0x89,0x2e, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r14)
 { .bytes = { 0x4d,0x89,0x2f, }, .expectedOpcode = UD_Imov }, // movq  %r13, (%r15)
 { .bytes = { 0x4c,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rax)
 { .bytes = { 0x4c,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rcx)
 { .bytes = { 0x4c,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rdx)
 { .bytes = { 0x4c,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rbx)
 { .bytes = { 0x4c,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rsp)
 { .bytes = { 0x4c,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rbp)
 { .bytes = { 0x4c,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rsi)
 { .bytes = { 0x4c,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%rdi)
 { .bytes = { 0x4d,0x89,0x30, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r8)
 { .bytes = { 0x4d,0x89,0x31, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r9)
 { .bytes = { 0x4d,0x89,0x32, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r10)
 { .bytes = { 0x4d,0x89,0x33, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r11)
 { .bytes = { 0x4d,0x89,0x34,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r12)
 { .bytes = { 0x4d,0x89,0x75,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r13)
 { .bytes = { 0x4d,0x89,0x36, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r14)
 { .bytes = { 0x4d,0x89,0x37, }, .expectedOpcode = UD_Imov }, // movq  %r14, (%r15)
 { .bytes = { 0x4c,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rax)
 { .bytes = { 0x4c,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rcx)
 { .bytes = { 0x4c,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rdx)
 { .bytes = { 0x4c,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rbx)
 { .bytes = { 0x4c,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rsp)
 { .bytes = { 0x4c,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rbp)
 { .bytes = { 0x4c,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rsi)
 { .bytes = { 0x4c,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%rdi)
 { .bytes = { 0x4d,0x89,0x38, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r8)
 { .bytes = { 0x4d,0x89,0x39, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r9)
 { .bytes = { 0x4d,0x89,0x3a, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r10)
 { .bytes = { 0x4d,0x89,0x3b, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r11)
 { .bytes = { 0x4d,0x89,0x3c,0x24, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r12)
 { .bytes = { 0x4d,0x89,0x7d,0x00, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r13)
 { .bytes = { 0x4d,0x89,0x3e, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r14)
 { .bytes = { 0x4d,0x89,0x3f, }, .expectedOpcode = UD_Imov }, // movq  %r15, (%r15)
 { .bytes = { 0x67,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%eax)
 { .bytes = { 0x67,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%ecx)
 { .bytes = { 0x67,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%edx)
 { .bytes = { 0x67,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%ebx)
 { .bytes = { 0x67,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%esp)
 { .bytes = { 0x67,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%ebp)
 { .bytes = { 0x67,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%esi)
 { .bytes = { 0x67,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addl  %eax, (%r15d)
 { .bytes = { 0x67,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%eax)
 { .bytes = { 0x67,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%ecx)
 { .bytes = { 0x67,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%edx)
 { .bytes = { 0x67,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%ebx)
 { .bytes = { 0x67,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%esp)
 { .bytes = { 0x67,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%ebp)
 { .bytes = { 0x67,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%esi)
 { .bytes = { 0x67,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addl  %ecx, (%r15d)
 { .bytes = { 0x67,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%eax)
 { .bytes = { 0x67,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%ecx)
 { .bytes = { 0x67,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%edx)
 { .bytes = { 0x67,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%ebx)
 { .bytes = { 0x67,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%esp)
 { .bytes = { 0x67,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%ebp)
 { .bytes = { 0x67,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%esi)
 { .bytes = { 0x67,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addl  %edx, (%r15d)
 { .bytes = { 0x67,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%eax)
 { .bytes = { 0x67,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%ecx)
 { .bytes = { 0x67,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%edx)
 { .bytes = { 0x67,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%ebx)
 { .bytes = { 0x67,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%esp)
 { .bytes = { 0x67,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%ebp)
 { .bytes = { 0x67,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%esi)
 { .bytes = { 0x67,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addl  %ebx, (%r15d)
 { .bytes = { 0x67,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%eax)
 { .bytes = { 0x67,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%ecx)
 { .bytes = { 0x67,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%edx)
 { .bytes = { 0x67,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%ebx)
 { .bytes = { 0x67,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%esp)
 { .bytes = { 0x67,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%ebp)
 { .bytes = { 0x67,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%esi)
 { .bytes = { 0x67,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addl  %esp, (%r15d)
 { .bytes = { 0x67,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%eax)
 { .bytes = { 0x67,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%ecx)
 { .bytes = { 0x67,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%edx)
 { .bytes = { 0x67,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%ebx)
 { .bytes = { 0x67,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%esp)
 { .bytes = { 0x67,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%ebp)
 { .bytes = { 0x67,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%esi)
 { .bytes = { 0x67,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addl  %ebp, (%r15d)
 { .bytes = { 0x67,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%eax)
 { .bytes = { 0x67,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%ecx)
 { .bytes = { 0x67,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%edx)
 { .bytes = { 0x67,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%ebx)
 { .bytes = { 0x67,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%esp)
 { .bytes = { 0x67,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%ebp)
 { .bytes = { 0x67,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%esi)
 { .bytes = { 0x67,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addl  %esi, (%r15d)
 { .bytes = { 0x67,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%eax)
 { .bytes = { 0x67,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%ecx)
 { .bytes = { 0x67,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%edx)
 { .bytes = { 0x67,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%ebx)
 { .bytes = { 0x67,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%esp)
 { .bytes = { 0x67,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%ebp)
 { .bytes = { 0x67,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%esi)
 { .bytes = { 0x67,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%edi)
 { .bytes = { 0x67,0x41,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r8d)
 { .bytes = { 0x67,0x41,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r9d)
 { .bytes = { 0x67,0x41,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r10d)
 { .bytes = { 0x67,0x41,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r11d)
 { .bytes = { 0x67,0x41,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r12d)
 { .bytes = { 0x67,0x41,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r13d)
 { .bytes = { 0x67,0x41,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r14d)
 { .bytes = { 0x67,0x41,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addl  %edi, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addl  %r8d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addl  %r9d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addl  %r10d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addl  %r11d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addl  %r12d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addl  %r13d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addl  %r14d, (%r15d)
 { .bytes = { 0x67,0x44,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%eax)
 { .bytes = { 0x67,0x44,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%ecx)
 { .bytes = { 0x67,0x44,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%edx)
 { .bytes = { 0x67,0x44,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%ebx)
 { .bytes = { 0x67,0x44,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%esp)
 { .bytes = { 0x67,0x44,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%ebp)
 { .bytes = { 0x67,0x44,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%esi)
 { .bytes = { 0x67,0x44,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%edi)
 { .bytes = { 0x67,0x45,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r8d)
 { .bytes = { 0x67,0x45,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r9d)
 { .bytes = { 0x67,0x45,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r10d)
 { .bytes = { 0x67,0x45,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r11d)
 { .bytes = { 0x67,0x45,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r12d)
 { .bytes = { 0x67,0x45,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r13d)
 { .bytes = { 0x67,0x45,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r14d)
 { .bytes = { 0x67,0x45,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addl  %r15d, (%r15d)
 { .bytes = { 0x48,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rax)
 { .bytes = { 0x48,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rcx)
 { .bytes = { 0x48,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rdx)
 { .bytes = { 0x48,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rbx)
 { .bytes = { 0x48,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rsp)
 { .bytes = { 0x48,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rbp)
 { .bytes = { 0x48,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rsi)
 { .bytes = { 0x48,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%rdi)
 { .bytes = { 0x49,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r8)
 { .bytes = { 0x49,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r9)
 { .bytes = { 0x49,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r10)
 { .bytes = { 0x49,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r11)
 { .bytes = { 0x49,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r12)
 { .bytes = { 0x49,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r13)
 { .bytes = { 0x49,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r14)
 { .bytes = { 0x49,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addq  %rax, (%r15)
 { .bytes = { 0x48,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rax)
 { .bytes = { 0x48,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rcx)
 { .bytes = { 0x48,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rdx)
 { .bytes = { 0x48,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rbx)
 { .bytes = { 0x48,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rsp)
 { .bytes = { 0x48,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rbp)
 { .bytes = { 0x48,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rsi)
 { .bytes = { 0x48,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%rdi)
 { .bytes = { 0x49,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r8)
 { .bytes = { 0x49,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r9)
 { .bytes = { 0x49,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r10)
 { .bytes = { 0x49,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r11)
 { .bytes = { 0x49,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r12)
 { .bytes = { 0x49,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r13)
 { .bytes = { 0x49,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r14)
 { .bytes = { 0x49,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addq  %rcx, (%r15)
 { .bytes = { 0x48,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rax)
 { .bytes = { 0x48,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rcx)
 { .bytes = { 0x48,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rdx)
 { .bytes = { 0x48,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rbx)
 { .bytes = { 0x48,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rsp)
 { .bytes = { 0x48,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rbp)
 { .bytes = { 0x48,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rsi)
 { .bytes = { 0x48,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%rdi)
 { .bytes = { 0x49,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r8)
 { .bytes = { 0x49,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r9)
 { .bytes = { 0x49,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r10)
 { .bytes = { 0x49,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r11)
 { .bytes = { 0x49,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r12)
 { .bytes = { 0x49,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r13)
 { .bytes = { 0x49,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r14)
 { .bytes = { 0x49,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addq  %rdx, (%r15)
 { .bytes = { 0x48,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rax)
 { .bytes = { 0x48,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rcx)
 { .bytes = { 0x48,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rdx)
 { .bytes = { 0x48,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rbx)
 { .bytes = { 0x48,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rsp)
 { .bytes = { 0x48,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rbp)
 { .bytes = { 0x48,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rsi)
 { .bytes = { 0x48,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%rdi)
 { .bytes = { 0x49,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r8)
 { .bytes = { 0x49,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r9)
 { .bytes = { 0x49,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r10)
 { .bytes = { 0x49,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r11)
 { .bytes = { 0x49,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r12)
 { .bytes = { 0x49,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r13)
 { .bytes = { 0x49,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r14)
 { .bytes = { 0x49,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addq  %rbx, (%r15)
 { .bytes = { 0x48,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rax)
 { .bytes = { 0x48,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rcx)
 { .bytes = { 0x48,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rdx)
 { .bytes = { 0x48,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rbx)
 { .bytes = { 0x48,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rsp)
 { .bytes = { 0x48,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rbp)
 { .bytes = { 0x48,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rsi)
 { .bytes = { 0x48,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%rdi)
 { .bytes = { 0x49,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r8)
 { .bytes = { 0x49,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r9)
 { .bytes = { 0x49,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r10)
 { .bytes = { 0x49,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r11)
 { .bytes = { 0x49,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r12)
 { .bytes = { 0x49,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r13)
 { .bytes = { 0x49,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r14)
 { .bytes = { 0x49,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addq  %rsp, (%r15)
 { .bytes = { 0x48,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rax)
 { .bytes = { 0x48,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rcx)
 { .bytes = { 0x48,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rdx)
 { .bytes = { 0x48,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rbx)
 { .bytes = { 0x48,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rsp)
 { .bytes = { 0x48,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rbp)
 { .bytes = { 0x48,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rsi)
 { .bytes = { 0x48,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%rdi)
 { .bytes = { 0x49,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r8)
 { .bytes = { 0x49,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r9)
 { .bytes = { 0x49,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r10)
 { .bytes = { 0x49,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r11)
 { .bytes = { 0x49,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r12)
 { .bytes = { 0x49,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r13)
 { .bytes = { 0x49,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r14)
 { .bytes = { 0x49,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addq  %rbp, (%r15)
 { .bytes = { 0x48,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rax)
 { .bytes = { 0x48,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rcx)
 { .bytes = { 0x48,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rdx)
 { .bytes = { 0x48,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rbx)
 { .bytes = { 0x48,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rsp)
 { .bytes = { 0x48,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rbp)
 { .bytes = { 0x48,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rsi)
 { .bytes = { 0x48,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%rdi)
 { .bytes = { 0x49,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r8)
 { .bytes = { 0x49,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r9)
 { .bytes = { 0x49,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r10)
 { .bytes = { 0x49,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r11)
 { .bytes = { 0x49,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r12)
 { .bytes = { 0x49,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r13)
 { .bytes = { 0x49,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r14)
 { .bytes = { 0x49,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addq  %rsi, (%r15)
 { .bytes = { 0x48,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rax)
 { .bytes = { 0x48,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rcx)
 { .bytes = { 0x48,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rdx)
 { .bytes = { 0x48,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rbx)
 { .bytes = { 0x48,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rsp)
 { .bytes = { 0x48,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rbp)
 { .bytes = { 0x48,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rsi)
 { .bytes = { 0x48,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%rdi)
 { .bytes = { 0x49,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r8)
 { .bytes = { 0x49,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r9)
 { .bytes = { 0x49,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r10)
 { .bytes = { 0x49,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r11)
 { .bytes = { 0x49,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r12)
 { .bytes = { 0x49,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r13)
 { .bytes = { 0x49,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r14)
 { .bytes = { 0x49,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addq  %rdi, (%r15)
 { .bytes = { 0x4c,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rax)
 { .bytes = { 0x4c,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rcx)
 { .bytes = { 0x4c,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rdx)
 { .bytes = { 0x4c,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rbx)
 { .bytes = { 0x4c,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rsp)
 { .bytes = { 0x4c,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rbp)
 { .bytes = { 0x4c,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rsi)
 { .bytes = { 0x4c,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%rdi)
 { .bytes = { 0x4d,0x01,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r8)
 { .bytes = { 0x4d,0x01,0x01, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r9)
 { .bytes = { 0x4d,0x01,0x02, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r10)
 { .bytes = { 0x4d,0x01,0x03, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r11)
 { .bytes = { 0x4d,0x01,0x04,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r12)
 { .bytes = { 0x4d,0x01,0x45,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r13)
 { .bytes = { 0x4d,0x01,0x06, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r14)
 { .bytes = { 0x4d,0x01,0x07, }, .expectedOpcode = UD_Iadd }, // addq  %r8, (%r15)
 { .bytes = { 0x4c,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rax)
 { .bytes = { 0x4c,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rcx)
 { .bytes = { 0x4c,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rdx)
 { .bytes = { 0x4c,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rbx)
 { .bytes = { 0x4c,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rsp)
 { .bytes = { 0x4c,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rbp)
 { .bytes = { 0x4c,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rsi)
 { .bytes = { 0x4c,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%rdi)
 { .bytes = { 0x4d,0x01,0x08, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r8)
 { .bytes = { 0x4d,0x01,0x09, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r9)
 { .bytes = { 0x4d,0x01,0x0a, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r10)
 { .bytes = { 0x4d,0x01,0x0b, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r11)
 { .bytes = { 0x4d,0x01,0x0c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r12)
 { .bytes = { 0x4d,0x01,0x4d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r13)
 { .bytes = { 0x4d,0x01,0x0e, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r14)
 { .bytes = { 0x4d,0x01,0x0f, }, .expectedOpcode = UD_Iadd }, // addq  %r9, (%r15)
 { .bytes = { 0x4c,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rax)
 { .bytes = { 0x4c,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rcx)
 { .bytes = { 0x4c,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rdx)
 { .bytes = { 0x4c,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rbx)
 { .bytes = { 0x4c,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rsp)
 { .bytes = { 0x4c,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rbp)
 { .bytes = { 0x4c,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rsi)
 { .bytes = { 0x4c,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%rdi)
 { .bytes = { 0x4d,0x01,0x10, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r8)
 { .bytes = { 0x4d,0x01,0x11, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r9)
 { .bytes = { 0x4d,0x01,0x12, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r10)
 { .bytes = { 0x4d,0x01,0x13, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r11)
 { .bytes = { 0x4d,0x01,0x14,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r12)
 { .bytes = { 0x4d,0x01,0x55,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r13)
 { .bytes = { 0x4d,0x01,0x16, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r14)
 { .bytes = { 0x4d,0x01,0x17, }, .expectedOpcode = UD_Iadd }, // addq  %r10, (%r15)
 { .bytes = { 0x4c,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rax)
 { .bytes = { 0x4c,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rcx)
 { .bytes = { 0x4c,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rdx)
 { .bytes = { 0x4c,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rbx)
 { .bytes = { 0x4c,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rsp)
 { .bytes = { 0x4c,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rbp)
 { .bytes = { 0x4c,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rsi)
 { .bytes = { 0x4c,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%rdi)
 { .bytes = { 0x4d,0x01,0x18, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r8)
 { .bytes = { 0x4d,0x01,0x19, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r9)
 { .bytes = { 0x4d,0x01,0x1a, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r10)
 { .bytes = { 0x4d,0x01,0x1b, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r11)
 { .bytes = { 0x4d,0x01,0x1c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r12)
 { .bytes = { 0x4d,0x01,0x5d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r13)
 { .bytes = { 0x4d,0x01,0x1e, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r14)
 { .bytes = { 0x4d,0x01,0x1f, }, .expectedOpcode = UD_Iadd }, // addq  %r11, (%r15)
 { .bytes = { 0x4c,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rax)
 { .bytes = { 0x4c,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rcx)
 { .bytes = { 0x4c,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rdx)
 { .bytes = { 0x4c,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rbx)
 { .bytes = { 0x4c,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rsp)
 { .bytes = { 0x4c,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rbp)
 { .bytes = { 0x4c,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rsi)
 { .bytes = { 0x4c,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%rdi)
 { .bytes = { 0x4d,0x01,0x20, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r8)
 { .bytes = { 0x4d,0x01,0x21, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r9)
 { .bytes = { 0x4d,0x01,0x22, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r10)
 { .bytes = { 0x4d,0x01,0x23, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r11)
 { .bytes = { 0x4d,0x01,0x24,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r12)
 { .bytes = { 0x4d,0x01,0x65,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r13)
 { .bytes = { 0x4d,0x01,0x26, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r14)
 { .bytes = { 0x4d,0x01,0x27, }, .expectedOpcode = UD_Iadd }, // addq  %r12, (%r15)
 { .bytes = { 0x4c,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rax)
 { .bytes = { 0x4c,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rcx)
 { .bytes = { 0x4c,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rdx)
 { .bytes = { 0x4c,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rbx)
 { .bytes = { 0x4c,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rsp)
 { .bytes = { 0x4c,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rbp)
 { .bytes = { 0x4c,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rsi)
 { .bytes = { 0x4c,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%rdi)
 { .bytes = { 0x4d,0x01,0x28, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r8)
 { .bytes = { 0x4d,0x01,0x29, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r9)
 { .bytes = { 0x4d,0x01,0x2a, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r10)
 { .bytes = { 0x4d,0x01,0x2b, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r11)
 { .bytes = { 0x4d,0x01,0x2c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r12)
 { .bytes = { 0x4d,0x01,0x6d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r13)
 { .bytes = { 0x4d,0x01,0x2e, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r14)
 { .bytes = { 0x4d,0x01,0x2f, }, .expectedOpcode = UD_Iadd }, // addq  %r13, (%r15)
 { .bytes = { 0x4c,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rax)
 { .bytes = { 0x4c,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rcx)
 { .bytes = { 0x4c,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rdx)
 { .bytes = { 0x4c,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rbx)
 { .bytes = { 0x4c,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rsp)
 { .bytes = { 0x4c,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rbp)
 { .bytes = { 0x4c,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rsi)
 { .bytes = { 0x4c,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%rdi)
 { .bytes = { 0x4d,0x01,0x30, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r8)
 { .bytes = { 0x4d,0x01,0x31, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r9)
 { .bytes = { 0x4d,0x01,0x32, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r10)
 { .bytes = { 0x4d,0x01,0x33, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r11)
 { .bytes = { 0x4d,0x01,0x34,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r12)
 { .bytes = { 0x4d,0x01,0x75,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r13)
 { .bytes = { 0x4d,0x01,0x36, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r14)
 { .bytes = { 0x4d,0x01,0x37, }, .expectedOpcode = UD_Iadd }, // addq  %r14, (%r15)
 { .bytes = { 0x4c,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rax)
 { .bytes = { 0x4c,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rcx)
 { .bytes = { 0x4c,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rdx)
 { .bytes = { 0x4c,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rbx)
 { .bytes = { 0x4c,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rsp)
 { .bytes = { 0x4c,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rbp)
 { .bytes = { 0x4c,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rsi)
 { .bytes = { 0x4c,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%rdi)
 { .bytes = { 0x4d,0x01,0x38, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r8)
 { .bytes = { 0x4d,0x01,0x39, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r9)
 { .bytes = { 0x4d,0x01,0x3a, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r10)
 { .bytes = { 0x4d,0x01,0x3b, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r11)
 { .bytes = { 0x4d,0x01,0x3c,0x24, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r12)
 { .bytes = { 0x4d,0x01,0x7d,0x00, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r13)
 { .bytes = { 0x4d,0x01,0x3e, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r14)
 { .bytes = { 0x4d,0x01,0x3f, }, .expectedOpcode = UD_Iadd }, // addq  %r15, (%r15)
 { .bytes = { 0x67,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%eax)
 { .bytes = { 0x67,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%ecx)
 { .bytes = { 0x67,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%edx)
 { .bytes = { 0x67,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%ebx)
 { .bytes = { 0x67,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%esp)
 { .bytes = { 0x67,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%ebp)
 { .bytes = { 0x67,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%esi)
 { .bytes = { 0x67,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andl  %eax, (%r15d)
 { .bytes = { 0x67,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%eax)
 { .bytes = { 0x67,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%ecx)
 { .bytes = { 0x67,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%edx)
 { .bytes = { 0x67,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%ebx)
 { .bytes = { 0x67,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%esp)
 { .bytes = { 0x67,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%ebp)
 { .bytes = { 0x67,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%esi)
 { .bytes = { 0x67,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andl  %ecx, (%r15d)
 { .bytes = { 0x67,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%eax)
 { .bytes = { 0x67,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%ecx)
 { .bytes = { 0x67,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%edx)
 { .bytes = { 0x67,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%ebx)
 { .bytes = { 0x67,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%esp)
 { .bytes = { 0x67,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%ebp)
 { .bytes = { 0x67,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%esi)
 { .bytes = { 0x67,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andl  %edx, (%r15d)
 { .bytes = { 0x67,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%eax)
 { .bytes = { 0x67,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%ecx)
 { .bytes = { 0x67,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%edx)
 { .bytes = { 0x67,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%ebx)
 { .bytes = { 0x67,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%esp)
 { .bytes = { 0x67,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%ebp)
 { .bytes = { 0x67,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%esi)
 { .bytes = { 0x67,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andl  %ebx, (%r15d)
 { .bytes = { 0x67,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%eax)
 { .bytes = { 0x67,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%ecx)
 { .bytes = { 0x67,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%edx)
 { .bytes = { 0x67,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%ebx)
 { .bytes = { 0x67,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%esp)
 { .bytes = { 0x67,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%ebp)
 { .bytes = { 0x67,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%esi)
 { .bytes = { 0x67,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andl  %esp, (%r15d)
 { .bytes = { 0x67,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%eax)
 { .bytes = { 0x67,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%ecx)
 { .bytes = { 0x67,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%edx)
 { .bytes = { 0x67,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%ebx)
 { .bytes = { 0x67,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%esp)
 { .bytes = { 0x67,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%ebp)
 { .bytes = { 0x67,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%esi)
 { .bytes = { 0x67,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andl  %ebp, (%r15d)
 { .bytes = { 0x67,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%eax)
 { .bytes = { 0x67,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%ecx)
 { .bytes = { 0x67,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%edx)
 { .bytes = { 0x67,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%ebx)
 { .bytes = { 0x67,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%esp)
 { .bytes = { 0x67,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%ebp)
 { .bytes = { 0x67,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%esi)
 { .bytes = { 0x67,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andl  %esi, (%r15d)
 { .bytes = { 0x67,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%eax)
 { .bytes = { 0x67,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%ecx)
 { .bytes = { 0x67,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%edx)
 { .bytes = { 0x67,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%ebx)
 { .bytes = { 0x67,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%esp)
 { .bytes = { 0x67,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%ebp)
 { .bytes = { 0x67,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%esi)
 { .bytes = { 0x67,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%edi)
 { .bytes = { 0x67,0x41,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r8d)
 { .bytes = { 0x67,0x41,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r9d)
 { .bytes = { 0x67,0x41,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r10d)
 { .bytes = { 0x67,0x41,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r11d)
 { .bytes = { 0x67,0x41,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r12d)
 { .bytes = { 0x67,0x41,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r13d)
 { .bytes = { 0x67,0x41,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r14d)
 { .bytes = { 0x67,0x41,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andl  %edi, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andl  %r8d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andl  %r9d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andl  %r10d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andl  %r11d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andl  %r12d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andl  %r13d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andl  %r14d, (%r15d)
 { .bytes = { 0x67,0x44,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%eax)
 { .bytes = { 0x67,0x44,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%ecx)
 { .bytes = { 0x67,0x44,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%edx)
 { .bytes = { 0x67,0x44,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%ebx)
 { .bytes = { 0x67,0x44,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%esp)
 { .bytes = { 0x67,0x44,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%ebp)
 { .bytes = { 0x67,0x44,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%esi)
 { .bytes = { 0x67,0x44,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%edi)
 { .bytes = { 0x67,0x45,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r8d)
 { .bytes = { 0x67,0x45,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r9d)
 { .bytes = { 0x67,0x45,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r10d)
 { .bytes = { 0x67,0x45,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r11d)
 { .bytes = { 0x67,0x45,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r12d)
 { .bytes = { 0x67,0x45,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r13d)
 { .bytes = { 0x67,0x45,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r14d)
 { .bytes = { 0x67,0x45,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andl  %r15d, (%r15d)
 { .bytes = { 0x48,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rax)
 { .bytes = { 0x48,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rcx)
 { .bytes = { 0x48,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rdx)
 { .bytes = { 0x48,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rbx)
 { .bytes = { 0x48,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rsp)
 { .bytes = { 0x48,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rbp)
 { .bytes = { 0x48,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rsi)
 { .bytes = { 0x48,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%rdi)
 { .bytes = { 0x49,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r8)
 { .bytes = { 0x49,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r9)
 { .bytes = { 0x49,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r10)
 { .bytes = { 0x49,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r11)
 { .bytes = { 0x49,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r12)
 { .bytes = { 0x49,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r13)
 { .bytes = { 0x49,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r14)
 { .bytes = { 0x49,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andq  %rax, (%r15)
 { .bytes = { 0x48,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rax)
 { .bytes = { 0x48,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rcx)
 { .bytes = { 0x48,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rdx)
 { .bytes = { 0x48,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rbx)
 { .bytes = { 0x48,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rsp)
 { .bytes = { 0x48,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rbp)
 { .bytes = { 0x48,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rsi)
 { .bytes = { 0x48,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%rdi)
 { .bytes = { 0x49,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r8)
 { .bytes = { 0x49,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r9)
 { .bytes = { 0x49,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r10)
 { .bytes = { 0x49,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r11)
 { .bytes = { 0x49,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r12)
 { .bytes = { 0x49,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r13)
 { .bytes = { 0x49,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r14)
 { .bytes = { 0x49,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andq  %rcx, (%r15)
 { .bytes = { 0x48,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rax)
 { .bytes = { 0x48,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rcx)
 { .bytes = { 0x48,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rdx)
 { .bytes = { 0x48,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rbx)
 { .bytes = { 0x48,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rsp)
 { .bytes = { 0x48,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rbp)
 { .bytes = { 0x48,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rsi)
 { .bytes = { 0x48,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%rdi)
 { .bytes = { 0x49,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r8)
 { .bytes = { 0x49,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r9)
 { .bytes = { 0x49,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r10)
 { .bytes = { 0x49,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r11)
 { .bytes = { 0x49,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r12)
 { .bytes = { 0x49,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r13)
 { .bytes = { 0x49,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r14)
 { .bytes = { 0x49,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andq  %rdx, (%r15)
 { .bytes = { 0x48,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rax)
 { .bytes = { 0x48,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rcx)
 { .bytes = { 0x48,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rdx)
 { .bytes = { 0x48,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rbx)
 { .bytes = { 0x48,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rsp)
 { .bytes = { 0x48,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rbp)
 { .bytes = { 0x48,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rsi)
 { .bytes = { 0x48,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%rdi)
 { .bytes = { 0x49,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r8)
 { .bytes = { 0x49,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r9)
 { .bytes = { 0x49,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r10)
 { .bytes = { 0x49,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r11)
 { .bytes = { 0x49,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r12)
 { .bytes = { 0x49,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r13)
 { .bytes = { 0x49,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r14)
 { .bytes = { 0x49,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andq  %rbx, (%r15)
 { .bytes = { 0x48,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rax)
 { .bytes = { 0x48,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rcx)
 { .bytes = { 0x48,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rdx)
 { .bytes = { 0x48,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rbx)
 { .bytes = { 0x48,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rsp)
 { .bytes = { 0x48,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rbp)
 { .bytes = { 0x48,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rsi)
 { .bytes = { 0x48,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%rdi)
 { .bytes = { 0x49,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r8)
 { .bytes = { 0x49,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r9)
 { .bytes = { 0x49,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r10)
 { .bytes = { 0x49,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r11)
 { .bytes = { 0x49,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r12)
 { .bytes = { 0x49,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r13)
 { .bytes = { 0x49,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r14)
 { .bytes = { 0x49,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andq  %rsp, (%r15)
 { .bytes = { 0x48,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rax)
 { .bytes = { 0x48,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rcx)
 { .bytes = { 0x48,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rdx)
 { .bytes = { 0x48,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rbx)
 { .bytes = { 0x48,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rsp)
 { .bytes = { 0x48,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rbp)
 { .bytes = { 0x48,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rsi)
 { .bytes = { 0x48,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%rdi)
 { .bytes = { 0x49,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r8)
 { .bytes = { 0x49,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r9)
 { .bytes = { 0x49,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r10)
 { .bytes = { 0x49,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r11)
 { .bytes = { 0x49,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r12)
 { .bytes = { 0x49,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r13)
 { .bytes = { 0x49,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r14)
 { .bytes = { 0x49,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andq  %rbp, (%r15)
 { .bytes = { 0x48,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rax)
 { .bytes = { 0x48,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rcx)
 { .bytes = { 0x48,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rdx)
 { .bytes = { 0x48,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rbx)
 { .bytes = { 0x48,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rsp)
 { .bytes = { 0x48,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rbp)
 { .bytes = { 0x48,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rsi)
 { .bytes = { 0x48,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%rdi)
 { .bytes = { 0x49,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r8)
 { .bytes = { 0x49,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r9)
 { .bytes = { 0x49,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r10)
 { .bytes = { 0x49,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r11)
 { .bytes = { 0x49,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r12)
 { .bytes = { 0x49,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r13)
 { .bytes = { 0x49,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r14)
 { .bytes = { 0x49,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andq  %rsi, (%r15)
 { .bytes = { 0x48,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rax)
 { .bytes = { 0x48,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rcx)
 { .bytes = { 0x48,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rdx)
 { .bytes = { 0x48,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rbx)
 { .bytes = { 0x48,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rsp)
 { .bytes = { 0x48,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rbp)
 { .bytes = { 0x48,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rsi)
 { .bytes = { 0x48,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%rdi)
 { .bytes = { 0x49,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r8)
 { .bytes = { 0x49,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r9)
 { .bytes = { 0x49,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r10)
 { .bytes = { 0x49,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r11)
 { .bytes = { 0x49,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r12)
 { .bytes = { 0x49,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r13)
 { .bytes = { 0x49,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r14)
 { .bytes = { 0x49,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andq  %rdi, (%r15)
 { .bytes = { 0x4c,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rax)
 { .bytes = { 0x4c,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rcx)
 { .bytes = { 0x4c,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rdx)
 { .bytes = { 0x4c,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rbx)
 { .bytes = { 0x4c,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rsp)
 { .bytes = { 0x4c,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rbp)
 { .bytes = { 0x4c,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rsi)
 { .bytes = { 0x4c,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%rdi)
 { .bytes = { 0x4d,0x21,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r8)
 { .bytes = { 0x4d,0x21,0x01, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r9)
 { .bytes = { 0x4d,0x21,0x02, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r10)
 { .bytes = { 0x4d,0x21,0x03, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r11)
 { .bytes = { 0x4d,0x21,0x04,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r12)
 { .bytes = { 0x4d,0x21,0x45,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r13)
 { .bytes = { 0x4d,0x21,0x06, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r14)
 { .bytes = { 0x4d,0x21,0x07, }, .expectedOpcode = UD_Iand }, // andq  %r8, (%r15)
 { .bytes = { 0x4c,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rax)
 { .bytes = { 0x4c,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rcx)
 { .bytes = { 0x4c,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rdx)
 { .bytes = { 0x4c,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rbx)
 { .bytes = { 0x4c,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rsp)
 { .bytes = { 0x4c,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rbp)
 { .bytes = { 0x4c,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rsi)
 { .bytes = { 0x4c,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%rdi)
 { .bytes = { 0x4d,0x21,0x08, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r8)
 { .bytes = { 0x4d,0x21,0x09, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r9)
 { .bytes = { 0x4d,0x21,0x0a, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r10)
 { .bytes = { 0x4d,0x21,0x0b, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r11)
 { .bytes = { 0x4d,0x21,0x0c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r12)
 { .bytes = { 0x4d,0x21,0x4d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r13)
 { .bytes = { 0x4d,0x21,0x0e, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r14)
 { .bytes = { 0x4d,0x21,0x0f, }, .expectedOpcode = UD_Iand }, // andq  %r9, (%r15)
 { .bytes = { 0x4c,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rax)
 { .bytes = { 0x4c,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rcx)
 { .bytes = { 0x4c,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rdx)
 { .bytes = { 0x4c,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rbx)
 { .bytes = { 0x4c,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rsp)
 { .bytes = { 0x4c,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rbp)
 { .bytes = { 0x4c,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rsi)
 { .bytes = { 0x4c,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%rdi)
 { .bytes = { 0x4d,0x21,0x10, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r8)
 { .bytes = { 0x4d,0x21,0x11, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r9)
 { .bytes = { 0x4d,0x21,0x12, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r10)
 { .bytes = { 0x4d,0x21,0x13, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r11)
 { .bytes = { 0x4d,0x21,0x14,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r12)
 { .bytes = { 0x4d,0x21,0x55,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r13)
 { .bytes = { 0x4d,0x21,0x16, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r14)
 { .bytes = { 0x4d,0x21,0x17, }, .expectedOpcode = UD_Iand }, // andq  %r10, (%r15)
 { .bytes = { 0x4c,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rax)
 { .bytes = { 0x4c,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rcx)
 { .bytes = { 0x4c,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rdx)
 { .bytes = { 0x4c,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rbx)
 { .bytes = { 0x4c,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rsp)
 { .bytes = { 0x4c,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rbp)
 { .bytes = { 0x4c,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rsi)
 { .bytes = { 0x4c,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%rdi)
 { .bytes = { 0x4d,0x21,0x18, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r8)
 { .bytes = { 0x4d,0x21,0x19, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r9)
 { .bytes = { 0x4d,0x21,0x1a, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r10)
 { .bytes = { 0x4d,0x21,0x1b, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r11)
 { .bytes = { 0x4d,0x21,0x1c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r12)
 { .bytes = { 0x4d,0x21,0x5d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r13)
 { .bytes = { 0x4d,0x21,0x1e, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r14)
 { .bytes = { 0x4d,0x21,0x1f, }, .expectedOpcode = UD_Iand }, // andq  %r11, (%r15)
 { .bytes = { 0x4c,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rax)
 { .bytes = { 0x4c,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rcx)
 { .bytes = { 0x4c,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rdx)
 { .bytes = { 0x4c,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rbx)
 { .bytes = { 0x4c,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rsp)
 { .bytes = { 0x4c,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rbp)
 { .bytes = { 0x4c,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rsi)
 { .bytes = { 0x4c,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%rdi)
 { .bytes = { 0x4d,0x21,0x20, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r8)
 { .bytes = { 0x4d,0x21,0x21, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r9)
 { .bytes = { 0x4d,0x21,0x22, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r10)
 { .bytes = { 0x4d,0x21,0x23, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r11)
 { .bytes = { 0x4d,0x21,0x24,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r12)
 { .bytes = { 0x4d,0x21,0x65,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r13)
 { .bytes = { 0x4d,0x21,0x26, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r14)
 { .bytes = { 0x4d,0x21,0x27, }, .expectedOpcode = UD_Iand }, // andq  %r12, (%r15)
 { .bytes = { 0x4c,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rax)
 { .bytes = { 0x4c,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rcx)
 { .bytes = { 0x4c,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rdx)
 { .bytes = { 0x4c,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rbx)
 { .bytes = { 0x4c,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rsp)
 { .bytes = { 0x4c,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rbp)
 { .bytes = { 0x4c,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rsi)
 { .bytes = { 0x4c,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%rdi)
 { .bytes = { 0x4d,0x21,0x28, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r8)
 { .bytes = { 0x4d,0x21,0x29, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r9)
 { .bytes = { 0x4d,0x21,0x2a, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r10)
 { .bytes = { 0x4d,0x21,0x2b, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r11)
 { .bytes = { 0x4d,0x21,0x2c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r12)
 { .bytes = { 0x4d,0x21,0x6d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r13)
 { .bytes = { 0x4d,0x21,0x2e, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r14)
 { .bytes = { 0x4d,0x21,0x2f, }, .expectedOpcode = UD_Iand }, // andq  %r13, (%r15)
 { .bytes = { 0x4c,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rax)
 { .bytes = { 0x4c,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rcx)
 { .bytes = { 0x4c,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rdx)
 { .bytes = { 0x4c,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rbx)
 { .bytes = { 0x4c,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rsp)
 { .bytes = { 0x4c,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rbp)
 { .bytes = { 0x4c,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rsi)
 { .bytes = { 0x4c,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%rdi)
 { .bytes = { 0x4d,0x21,0x30, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r8)
 { .bytes = { 0x4d,0x21,0x31, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r9)
 { .bytes = { 0x4d,0x21,0x32, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r10)
 { .bytes = { 0x4d,0x21,0x33, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r11)
 { .bytes = { 0x4d,0x21,0x34,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r12)
 { .bytes = { 0x4d,0x21,0x75,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r13)
 { .bytes = { 0x4d,0x21,0x36, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r14)
 { .bytes = { 0x4d,0x21,0x37, }, .expectedOpcode = UD_Iand }, // andq  %r14, (%r15)
 { .bytes = { 0x4c,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rax)
 { .bytes = { 0x4c,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rcx)
 { .bytes = { 0x4c,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rdx)
 { .bytes = { 0x4c,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rbx)
 { .bytes = { 0x4c,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rsp)
 { .bytes = { 0x4c,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rbp)
 { .bytes = { 0x4c,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rsi)
 { .bytes = { 0x4c,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%rdi)
 { .bytes = { 0x4d,0x21,0x38, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r8)
 { .bytes = { 0x4d,0x21,0x39, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r9)
 { .bytes = { 0x4d,0x21,0x3a, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r10)
 { .bytes = { 0x4d,0x21,0x3b, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r11)
 { .bytes = { 0x4d,0x21,0x3c,0x24, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r12)
 { .bytes = { 0x4d,0x21,0x7d,0x00, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r13)
 { .bytes = { 0x4d,0x21,0x3e, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r14)
 { .bytes = { 0x4d,0x21,0x3f, }, .expectedOpcode = UD_Iand }, // andq  %r15, (%r15)
 { .bytes = { 0x67,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%eax)
 { .bytes = { 0x67,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%ecx)
 { .bytes = { 0x67,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%edx)
 { .bytes = { 0x67,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%ebx)
 { .bytes = { 0x67,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%esp)
 { .bytes = { 0x67,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%ebp)
 { .bytes = { 0x67,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%esi)
 { .bytes = { 0x67,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orl  %eax, (%r15d)
 { .bytes = { 0x67,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%eax)
 { .bytes = { 0x67,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%ecx)
 { .bytes = { 0x67,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%edx)
 { .bytes = { 0x67,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%ebx)
 { .bytes = { 0x67,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%esp)
 { .bytes = { 0x67,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%ebp)
 { .bytes = { 0x67,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%esi)
 { .bytes = { 0x67,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orl  %ecx, (%r15d)
 { .bytes = { 0x67,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%eax)
 { .bytes = { 0x67,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%ecx)
 { .bytes = { 0x67,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%edx)
 { .bytes = { 0x67,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%ebx)
 { .bytes = { 0x67,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%esp)
 { .bytes = { 0x67,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%ebp)
 { .bytes = { 0x67,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%esi)
 { .bytes = { 0x67,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orl  %edx, (%r15d)
 { .bytes = { 0x67,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%eax)
 { .bytes = { 0x67,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%ecx)
 { .bytes = { 0x67,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%edx)
 { .bytes = { 0x67,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%ebx)
 { .bytes = { 0x67,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%esp)
 { .bytes = { 0x67,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%ebp)
 { .bytes = { 0x67,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%esi)
 { .bytes = { 0x67,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orl  %ebx, (%r15d)
 { .bytes = { 0x67,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%eax)
 { .bytes = { 0x67,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%ecx)
 { .bytes = { 0x67,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%edx)
 { .bytes = { 0x67,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%ebx)
 { .bytes = { 0x67,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%esp)
 { .bytes = { 0x67,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%ebp)
 { .bytes = { 0x67,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%esi)
 { .bytes = { 0x67,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orl  %esp, (%r15d)
 { .bytes = { 0x67,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%eax)
 { .bytes = { 0x67,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%ecx)
 { .bytes = { 0x67,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%edx)
 { .bytes = { 0x67,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%ebx)
 { .bytes = { 0x67,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%esp)
 { .bytes = { 0x67,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%ebp)
 { .bytes = { 0x67,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%esi)
 { .bytes = { 0x67,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orl  %ebp, (%r15d)
 { .bytes = { 0x67,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%eax)
 { .bytes = { 0x67,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%ecx)
 { .bytes = { 0x67,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%edx)
 { .bytes = { 0x67,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%ebx)
 { .bytes = { 0x67,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%esp)
 { .bytes = { 0x67,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%ebp)
 { .bytes = { 0x67,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%esi)
 { .bytes = { 0x67,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orl  %esi, (%r15d)
 { .bytes = { 0x67,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%eax)
 { .bytes = { 0x67,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%ecx)
 { .bytes = { 0x67,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%edx)
 { .bytes = { 0x67,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%ebx)
 { .bytes = { 0x67,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%esp)
 { .bytes = { 0x67,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%ebp)
 { .bytes = { 0x67,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%esi)
 { .bytes = { 0x67,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%edi)
 { .bytes = { 0x67,0x41,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r8d)
 { .bytes = { 0x67,0x41,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r9d)
 { .bytes = { 0x67,0x41,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r10d)
 { .bytes = { 0x67,0x41,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r11d)
 { .bytes = { 0x67,0x41,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r12d)
 { .bytes = { 0x67,0x41,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r13d)
 { .bytes = { 0x67,0x41,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r14d)
 { .bytes = { 0x67,0x41,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orl  %edi, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orl  %r8d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orl  %r9d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orl  %r10d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orl  %r11d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orl  %r12d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orl  %r13d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orl  %r14d, (%r15d)
 { .bytes = { 0x67,0x44,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%eax)
 { .bytes = { 0x67,0x44,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%ecx)
 { .bytes = { 0x67,0x44,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%edx)
 { .bytes = { 0x67,0x44,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%ebx)
 { .bytes = { 0x67,0x44,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%esp)
 { .bytes = { 0x67,0x44,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%ebp)
 { .bytes = { 0x67,0x44,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%esi)
 { .bytes = { 0x67,0x44,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%edi)
 { .bytes = { 0x67,0x45,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r8d)
 { .bytes = { 0x67,0x45,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r9d)
 { .bytes = { 0x67,0x45,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r10d)
 { .bytes = { 0x67,0x45,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r11d)
 { .bytes = { 0x67,0x45,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r12d)
 { .bytes = { 0x67,0x45,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r13d)
 { .bytes = { 0x67,0x45,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r14d)
 { .bytes = { 0x67,0x45,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orl  %r15d, (%r15d)
 { .bytes = { 0x48,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rax)
 { .bytes = { 0x48,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rcx)
 { .bytes = { 0x48,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rdx)
 { .bytes = { 0x48,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rbx)
 { .bytes = { 0x48,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rsp)
 { .bytes = { 0x48,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rbp)
 { .bytes = { 0x48,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rsi)
 { .bytes = { 0x48,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%rdi)
 { .bytes = { 0x49,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r8)
 { .bytes = { 0x49,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r9)
 { .bytes = { 0x49,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r10)
 { .bytes = { 0x49,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r11)
 { .bytes = { 0x49,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r12)
 { .bytes = { 0x49,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r13)
 { .bytes = { 0x49,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r14)
 { .bytes = { 0x49,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orq  %rax, (%r15)
 { .bytes = { 0x48,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rax)
 { .bytes = { 0x48,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rcx)
 { .bytes = { 0x48,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rdx)
 { .bytes = { 0x48,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rbx)
 { .bytes = { 0x48,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rsp)
 { .bytes = { 0x48,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rbp)
 { .bytes = { 0x48,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rsi)
 { .bytes = { 0x48,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%rdi)
 { .bytes = { 0x49,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r8)
 { .bytes = { 0x49,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r9)
 { .bytes = { 0x49,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r10)
 { .bytes = { 0x49,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r11)
 { .bytes = { 0x49,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r12)
 { .bytes = { 0x49,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r13)
 { .bytes = { 0x49,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r14)
 { .bytes = { 0x49,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orq  %rcx, (%r15)
 { .bytes = { 0x48,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rax)
 { .bytes = { 0x48,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rcx)
 { .bytes = { 0x48,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rdx)
 { .bytes = { 0x48,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rbx)
 { .bytes = { 0x48,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rsp)
 { .bytes = { 0x48,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rbp)
 { .bytes = { 0x48,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rsi)
 { .bytes = { 0x48,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%rdi)
 { .bytes = { 0x49,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r8)
 { .bytes = { 0x49,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r9)
 { .bytes = { 0x49,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r10)
 { .bytes = { 0x49,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r11)
 { .bytes = { 0x49,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r12)
 { .bytes = { 0x49,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r13)
 { .bytes = { 0x49,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r14)
 { .bytes = { 0x49,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orq  %rdx, (%r15)
 { .bytes = { 0x48,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rax)
 { .bytes = { 0x48,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rcx)
 { .bytes = { 0x48,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rdx)
 { .bytes = { 0x48,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rbx)
 { .bytes = { 0x48,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rsp)
 { .bytes = { 0x48,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rbp)
 { .bytes = { 0x48,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rsi)
 { .bytes = { 0x48,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%rdi)
 { .bytes = { 0x49,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r8)
 { .bytes = { 0x49,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r9)
 { .bytes = { 0x49,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r10)
 { .bytes = { 0x49,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r11)
 { .bytes = { 0x49,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r12)
 { .bytes = { 0x49,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r13)
 { .bytes = { 0x49,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r14)
 { .bytes = { 0x49,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orq  %rbx, (%r15)
 { .bytes = { 0x48,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rax)
 { .bytes = { 0x48,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rcx)
 { .bytes = { 0x48,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rdx)
 { .bytes = { 0x48,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rbx)
 { .bytes = { 0x48,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rsp)
 { .bytes = { 0x48,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rbp)
 { .bytes = { 0x48,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rsi)
 { .bytes = { 0x48,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%rdi)
 { .bytes = { 0x49,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r8)
 { .bytes = { 0x49,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r9)
 { .bytes = { 0x49,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r10)
 { .bytes = { 0x49,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r11)
 { .bytes = { 0x49,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r12)
 { .bytes = { 0x49,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r13)
 { .bytes = { 0x49,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r14)
 { .bytes = { 0x49,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orq  %rsp, (%r15)
 { .bytes = { 0x48,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rax)
 { .bytes = { 0x48,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rcx)
 { .bytes = { 0x48,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rdx)
 { .bytes = { 0x48,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rbx)
 { .bytes = { 0x48,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rsp)
 { .bytes = { 0x48,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rbp)
 { .bytes = { 0x48,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rsi)
 { .bytes = { 0x48,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%rdi)
 { .bytes = { 0x49,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r8)
 { .bytes = { 0x49,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r9)
 { .bytes = { 0x49,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r10)
 { .bytes = { 0x49,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r11)
 { .bytes = { 0x49,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r12)
 { .bytes = { 0x49,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r13)
 { .bytes = { 0x49,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r14)
 { .bytes = { 0x49,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orq  %rbp, (%r15)
 { .bytes = { 0x48,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rax)
 { .bytes = { 0x48,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rcx)
 { .bytes = { 0x48,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rdx)
 { .bytes = { 0x48,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rbx)
 { .bytes = { 0x48,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rsp)
 { .bytes = { 0x48,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rbp)
 { .bytes = { 0x48,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rsi)
 { .bytes = { 0x48,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%rdi)
 { .bytes = { 0x49,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r8)
 { .bytes = { 0x49,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r9)
 { .bytes = { 0x49,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r10)
 { .bytes = { 0x49,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r11)
 { .bytes = { 0x49,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r12)
 { .bytes = { 0x49,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r13)
 { .bytes = { 0x49,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r14)
 { .bytes = { 0x49,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orq  %rsi, (%r15)
 { .bytes = { 0x48,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rax)
 { .bytes = { 0x48,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rcx)
 { .bytes = { 0x48,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rdx)
 { .bytes = { 0x48,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rbx)
 { .bytes = { 0x48,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rsp)
 { .bytes = { 0x48,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rbp)
 { .bytes = { 0x48,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rsi)
 { .bytes = { 0x48,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%rdi)
 { .bytes = { 0x49,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r8)
 { .bytes = { 0x49,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r9)
 { .bytes = { 0x49,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r10)
 { .bytes = { 0x49,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r11)
 { .bytes = { 0x49,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r12)
 { .bytes = { 0x49,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r13)
 { .bytes = { 0x49,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r14)
 { .bytes = { 0x49,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orq  %rdi, (%r15)
 { .bytes = { 0x4c,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rax)
 { .bytes = { 0x4c,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rcx)
 { .bytes = { 0x4c,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rdx)
 { .bytes = { 0x4c,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rbx)
 { .bytes = { 0x4c,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rsp)
 { .bytes = { 0x4c,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rbp)
 { .bytes = { 0x4c,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rsi)
 { .bytes = { 0x4c,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%rdi)
 { .bytes = { 0x4d,0x09,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r8)
 { .bytes = { 0x4d,0x09,0x01, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r9)
 { .bytes = { 0x4d,0x09,0x02, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r10)
 { .bytes = { 0x4d,0x09,0x03, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r11)
 { .bytes = { 0x4d,0x09,0x04,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r12)
 { .bytes = { 0x4d,0x09,0x45,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r13)
 { .bytes = { 0x4d,0x09,0x06, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r14)
 { .bytes = { 0x4d,0x09,0x07, }, .expectedOpcode = UD_Ior }, // orq  %r8, (%r15)
 { .bytes = { 0x4c,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rax)
 { .bytes = { 0x4c,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rcx)
 { .bytes = { 0x4c,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rdx)
 { .bytes = { 0x4c,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rbx)
 { .bytes = { 0x4c,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rsp)
 { .bytes = { 0x4c,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rbp)
 { .bytes = { 0x4c,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rsi)
 { .bytes = { 0x4c,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%rdi)
 { .bytes = { 0x4d,0x09,0x08, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r8)
 { .bytes = { 0x4d,0x09,0x09, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r9)
 { .bytes = { 0x4d,0x09,0x0a, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r10)
 { .bytes = { 0x4d,0x09,0x0b, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r11)
 { .bytes = { 0x4d,0x09,0x0c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r12)
 { .bytes = { 0x4d,0x09,0x4d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r13)
 { .bytes = { 0x4d,0x09,0x0e, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r14)
 { .bytes = { 0x4d,0x09,0x0f, }, .expectedOpcode = UD_Ior }, // orq  %r9, (%r15)
 { .bytes = { 0x4c,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rax)
 { .bytes = { 0x4c,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rcx)
 { .bytes = { 0x4c,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rdx)
 { .bytes = { 0x4c,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rbx)
 { .bytes = { 0x4c,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rsp)
 { .bytes = { 0x4c,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rbp)
 { .bytes = { 0x4c,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rsi)
 { .bytes = { 0x4c,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%rdi)
 { .bytes = { 0x4d,0x09,0x10, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r8)
 { .bytes = { 0x4d,0x09,0x11, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r9)
 { .bytes = { 0x4d,0x09,0x12, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r10)
 { .bytes = { 0x4d,0x09,0x13, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r11)
 { .bytes = { 0x4d,0x09,0x14,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r12)
 { .bytes = { 0x4d,0x09,0x55,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r13)
 { .bytes = { 0x4d,0x09,0x16, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r14)
 { .bytes = { 0x4d,0x09,0x17, }, .expectedOpcode = UD_Ior }, // orq  %r10, (%r15)
 { .bytes = { 0x4c,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rax)
 { .bytes = { 0x4c,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rcx)
 { .bytes = { 0x4c,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rdx)
 { .bytes = { 0x4c,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rbx)
 { .bytes = { 0x4c,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rsp)
 { .bytes = { 0x4c,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rbp)
 { .bytes = { 0x4c,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rsi)
 { .bytes = { 0x4c,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%rdi)
 { .bytes = { 0x4d,0x09,0x18, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r8)
 { .bytes = { 0x4d,0x09,0x19, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r9)
 { .bytes = { 0x4d,0x09,0x1a, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r10)
 { .bytes = { 0x4d,0x09,0x1b, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r11)
 { .bytes = { 0x4d,0x09,0x1c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r12)
 { .bytes = { 0x4d,0x09,0x5d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r13)
 { .bytes = { 0x4d,0x09,0x1e, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r14)
 { .bytes = { 0x4d,0x09,0x1f, }, .expectedOpcode = UD_Ior }, // orq  %r11, (%r15)
 { .bytes = { 0x4c,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rax)
 { .bytes = { 0x4c,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rcx)
 { .bytes = { 0x4c,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rdx)
 { .bytes = { 0x4c,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rbx)
 { .bytes = { 0x4c,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rsp)
 { .bytes = { 0x4c,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rbp)
 { .bytes = { 0x4c,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rsi)
 { .bytes = { 0x4c,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%rdi)
 { .bytes = { 0x4d,0x09,0x20, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r8)
 { .bytes = { 0x4d,0x09,0x21, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r9)
 { .bytes = { 0x4d,0x09,0x22, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r10)
 { .bytes = { 0x4d,0x09,0x23, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r11)
 { .bytes = { 0x4d,0x09,0x24,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r12)
 { .bytes = { 0x4d,0x09,0x65,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r13)
 { .bytes = { 0x4d,0x09,0x26, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r14)
 { .bytes = { 0x4d,0x09,0x27, }, .expectedOpcode = UD_Ior }, // orq  %r12, (%r15)
 { .bytes = { 0x4c,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rax)
 { .bytes = { 0x4c,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rcx)
 { .bytes = { 0x4c,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rdx)
 { .bytes = { 0x4c,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rbx)
 { .bytes = { 0x4c,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rsp)
 { .bytes = { 0x4c,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rbp)
 { .bytes = { 0x4c,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rsi)
 { .bytes = { 0x4c,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%rdi)
 { .bytes = { 0x4d,0x09,0x28, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r8)
 { .bytes = { 0x4d,0x09,0x29, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r9)
 { .bytes = { 0x4d,0x09,0x2a, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r10)
 { .bytes = { 0x4d,0x09,0x2b, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r11)
 { .bytes = { 0x4d,0x09,0x2c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r12)
 { .bytes = { 0x4d,0x09,0x6d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r13)
 { .bytes = { 0x4d,0x09,0x2e, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r14)
 { .bytes = { 0x4d,0x09,0x2f, }, .expectedOpcode = UD_Ior }, // orq  %r13, (%r15)
 { .bytes = { 0x4c,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rax)
 { .bytes = { 0x4c,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rcx)
 { .bytes = { 0x4c,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rdx)
 { .bytes = { 0x4c,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rbx)
 { .bytes = { 0x4c,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rsp)
 { .bytes = { 0x4c,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rbp)
 { .bytes = { 0x4c,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rsi)
 { .bytes = { 0x4c,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%rdi)
 { .bytes = { 0x4d,0x09,0x30, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r8)
 { .bytes = { 0x4d,0x09,0x31, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r9)
 { .bytes = { 0x4d,0x09,0x32, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r10)
 { .bytes = { 0x4d,0x09,0x33, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r11)
 { .bytes = { 0x4d,0x09,0x34,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r12)
 { .bytes = { 0x4d,0x09,0x75,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r13)
 { .bytes = { 0x4d,0x09,0x36, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r14)
 { .bytes = { 0x4d,0x09,0x37, }, .expectedOpcode = UD_Ior }, // orq  %r14, (%r15)
 { .bytes = { 0x4c,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rax)
 { .bytes = { 0x4c,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rcx)
 { .bytes = { 0x4c,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rdx)
 { .bytes = { 0x4c,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rbx)
 { .bytes = { 0x4c,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rsp)
 { .bytes = { 0x4c,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rbp)
 { .bytes = { 0x4c,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rsi)
 { .bytes = { 0x4c,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%rdi)
 { .bytes = { 0x4d,0x09,0x38, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r8)
 { .bytes = { 0x4d,0x09,0x39, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r9)
 { .bytes = { 0x4d,0x09,0x3a, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r10)
 { .bytes = { 0x4d,0x09,0x3b, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r11)
 { .bytes = { 0x4d,0x09,0x3c,0x24, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r12)
 { .bytes = { 0x4d,0x09,0x7d,0x00, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r13)
 { .bytes = { 0x4d,0x09,0x3e, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r14)
 { .bytes = { 0x4d,0x09,0x3f, }, .expectedOpcode = UD_Ior }, // orq  %r15, (%r15)
 { .bytes = { 0x67,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%eax)
 { .bytes = { 0x67,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%ecx)
 { .bytes = { 0x67,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%edx)
 { .bytes = { 0x67,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%ebx)
 { .bytes = { 0x67,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%esp)
 { .bytes = { 0x67,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%ebp)
 { .bytes = { 0x67,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%esi)
 { .bytes = { 0x67,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subl  %eax, (%r15d)
 { .bytes = { 0x67,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%eax)
 { .bytes = { 0x67,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%ecx)
 { .bytes = { 0x67,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%edx)
 { .bytes = { 0x67,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%ebx)
 { .bytes = { 0x67,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%esp)
 { .bytes = { 0x67,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%ebp)
 { .bytes = { 0x67,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%esi)
 { .bytes = { 0x67,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subl  %ecx, (%r15d)
 { .bytes = { 0x67,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%eax)
 { .bytes = { 0x67,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%ecx)
 { .bytes = { 0x67,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%edx)
 { .bytes = { 0x67,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%ebx)
 { .bytes = { 0x67,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%esp)
 { .bytes = { 0x67,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%ebp)
 { .bytes = { 0x67,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%esi)
 { .bytes = { 0x67,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subl  %edx, (%r15d)
 { .bytes = { 0x67,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%eax)
 { .bytes = { 0x67,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%ecx)
 { .bytes = { 0x67,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%edx)
 { .bytes = { 0x67,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%ebx)
 { .bytes = { 0x67,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%esp)
 { .bytes = { 0x67,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%ebp)
 { .bytes = { 0x67,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%esi)
 { .bytes = { 0x67,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subl  %ebx, (%r15d)
 { .bytes = { 0x67,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%eax)
 { .bytes = { 0x67,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%ecx)
 { .bytes = { 0x67,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%edx)
 { .bytes = { 0x67,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%ebx)
 { .bytes = { 0x67,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%esp)
 { .bytes = { 0x67,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%ebp)
 { .bytes = { 0x67,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%esi)
 { .bytes = { 0x67,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subl  %esp, (%r15d)
 { .bytes = { 0x67,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%eax)
 { .bytes = { 0x67,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%ecx)
 { .bytes = { 0x67,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%edx)
 { .bytes = { 0x67,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%ebx)
 { .bytes = { 0x67,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%esp)
 { .bytes = { 0x67,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%ebp)
 { .bytes = { 0x67,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%esi)
 { .bytes = { 0x67,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subl  %ebp, (%r15d)
 { .bytes = { 0x67,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%eax)
 { .bytes = { 0x67,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%ecx)
 { .bytes = { 0x67,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%edx)
 { .bytes = { 0x67,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%ebx)
 { .bytes = { 0x67,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%esp)
 { .bytes = { 0x67,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%ebp)
 { .bytes = { 0x67,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%esi)
 { .bytes = { 0x67,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subl  %esi, (%r15d)
 { .bytes = { 0x67,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%eax)
 { .bytes = { 0x67,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%ecx)
 { .bytes = { 0x67,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%edx)
 { .bytes = { 0x67,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%ebx)
 { .bytes = { 0x67,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%esp)
 { .bytes = { 0x67,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%ebp)
 { .bytes = { 0x67,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%esi)
 { .bytes = { 0x67,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%edi)
 { .bytes = { 0x67,0x41,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r8d)
 { .bytes = { 0x67,0x41,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r9d)
 { .bytes = { 0x67,0x41,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r10d)
 { .bytes = { 0x67,0x41,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r11d)
 { .bytes = { 0x67,0x41,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r12d)
 { .bytes = { 0x67,0x41,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r13d)
 { .bytes = { 0x67,0x41,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r14d)
 { .bytes = { 0x67,0x41,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subl  %edi, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subl  %r8d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subl  %r9d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subl  %r10d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subl  %r11d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subl  %r12d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subl  %r13d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subl  %r14d, (%r15d)
 { .bytes = { 0x67,0x44,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%eax)
 { .bytes = { 0x67,0x44,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%ecx)
 { .bytes = { 0x67,0x44,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%edx)
 { .bytes = { 0x67,0x44,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%ebx)
 { .bytes = { 0x67,0x44,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%esp)
 { .bytes = { 0x67,0x44,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%ebp)
 { .bytes = { 0x67,0x44,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%esi)
 { .bytes = { 0x67,0x44,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%edi)
 { .bytes = { 0x67,0x45,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r8d)
 { .bytes = { 0x67,0x45,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r9d)
 { .bytes = { 0x67,0x45,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r10d)
 { .bytes = { 0x67,0x45,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r11d)
 { .bytes = { 0x67,0x45,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r12d)
 { .bytes = { 0x67,0x45,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r13d)
 { .bytes = { 0x67,0x45,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r14d)
 { .bytes = { 0x67,0x45,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subl  %r15d, (%r15d)
 { .bytes = { 0x48,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rax)
 { .bytes = { 0x48,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rcx)
 { .bytes = { 0x48,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rdx)
 { .bytes = { 0x48,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rbx)
 { .bytes = { 0x48,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rsp)
 { .bytes = { 0x48,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rbp)
 { .bytes = { 0x48,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rsi)
 { .bytes = { 0x48,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%rdi)
 { .bytes = { 0x49,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r8)
 { .bytes = { 0x49,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r9)
 { .bytes = { 0x49,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r10)
 { .bytes = { 0x49,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r11)
 { .bytes = { 0x49,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r12)
 { .bytes = { 0x49,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r13)
 { .bytes = { 0x49,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r14)
 { .bytes = { 0x49,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subq  %rax, (%r15)
 { .bytes = { 0x48,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rax)
 { .bytes = { 0x48,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rcx)
 { .bytes = { 0x48,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rdx)
 { .bytes = { 0x48,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rbx)
 { .bytes = { 0x48,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rsp)
 { .bytes = { 0x48,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rbp)
 { .bytes = { 0x48,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rsi)
 { .bytes = { 0x48,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%rdi)
 { .bytes = { 0x49,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r8)
 { .bytes = { 0x49,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r9)
 { .bytes = { 0x49,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r10)
 { .bytes = { 0x49,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r11)
 { .bytes = { 0x49,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r12)
 { .bytes = { 0x49,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r13)
 { .bytes = { 0x49,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r14)
 { .bytes = { 0x49,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subq  %rcx, (%r15)
 { .bytes = { 0x48,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rax)
 { .bytes = { 0x48,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rcx)
 { .bytes = { 0x48,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rdx)
 { .bytes = { 0x48,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rbx)
 { .bytes = { 0x48,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rsp)
 { .bytes = { 0x48,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rbp)
 { .bytes = { 0x48,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rsi)
 { .bytes = { 0x48,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%rdi)
 { .bytes = { 0x49,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r8)
 { .bytes = { 0x49,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r9)
 { .bytes = { 0x49,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r10)
 { .bytes = { 0x49,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r11)
 { .bytes = { 0x49,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r12)
 { .bytes = { 0x49,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r13)
 { .bytes = { 0x49,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r14)
 { .bytes = { 0x49,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subq  %rdx, (%r15)
 { .bytes = { 0x48,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rax)
 { .bytes = { 0x48,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rcx)
 { .bytes = { 0x48,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rdx)
 { .bytes = { 0x48,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rbx)
 { .bytes = { 0x48,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rsp)
 { .bytes = { 0x48,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rbp)
 { .bytes = { 0x48,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rsi)
 { .bytes = { 0x48,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%rdi)
 { .bytes = { 0x49,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r8)
 { .bytes = { 0x49,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r9)
 { .bytes = { 0x49,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r10)
 { .bytes = { 0x49,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r11)
 { .bytes = { 0x49,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r12)
 { .bytes = { 0x49,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r13)
 { .bytes = { 0x49,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r14)
 { .bytes = { 0x49,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subq  %rbx, (%r15)
 { .bytes = { 0x48,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rax)
 { .bytes = { 0x48,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rcx)
 { .bytes = { 0x48,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rdx)
 { .bytes = { 0x48,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rbx)
 { .bytes = { 0x48,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rsp)
 { .bytes = { 0x48,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rbp)
 { .bytes = { 0x48,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rsi)
 { .bytes = { 0x48,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%rdi)
 { .bytes = { 0x49,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r8)
 { .bytes = { 0x49,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r9)
 { .bytes = { 0x49,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r10)
 { .bytes = { 0x49,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r11)
 { .bytes = { 0x49,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r12)
 { .bytes = { 0x49,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r13)
 { .bytes = { 0x49,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r14)
 { .bytes = { 0x49,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subq  %rsp, (%r15)
 { .bytes = { 0x48,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rax)
 { .bytes = { 0x48,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rcx)
 { .bytes = { 0x48,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rdx)
 { .bytes = { 0x48,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rbx)
 { .bytes = { 0x48,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rsp)
 { .bytes = { 0x48,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rbp)
 { .bytes = { 0x48,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rsi)
 { .bytes = { 0x48,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%rdi)
 { .bytes = { 0x49,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r8)
 { .bytes = { 0x49,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r9)
 { .bytes = { 0x49,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r10)
 { .bytes = { 0x49,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r11)
 { .bytes = { 0x49,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r12)
 { .bytes = { 0x49,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r13)
 { .bytes = { 0x49,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r14)
 { .bytes = { 0x49,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subq  %rbp, (%r15)
 { .bytes = { 0x48,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rax)
 { .bytes = { 0x48,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rcx)
 { .bytes = { 0x48,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rdx)
 { .bytes = { 0x48,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rbx)
 { .bytes = { 0x48,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rsp)
 { .bytes = { 0x48,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rbp)
 { .bytes = { 0x48,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rsi)
 { .bytes = { 0x48,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%rdi)
 { .bytes = { 0x49,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r8)
 { .bytes = { 0x49,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r9)
 { .bytes = { 0x49,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r10)
 { .bytes = { 0x49,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r11)
 { .bytes = { 0x49,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r12)
 { .bytes = { 0x49,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r13)
 { .bytes = { 0x49,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r14)
 { .bytes = { 0x49,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subq  %rsi, (%r15)
 { .bytes = { 0x48,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rax)
 { .bytes = { 0x48,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rcx)
 { .bytes = { 0x48,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rdx)
 { .bytes = { 0x48,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rbx)
 { .bytes = { 0x48,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rsp)
 { .bytes = { 0x48,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rbp)
 { .bytes = { 0x48,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rsi)
 { .bytes = { 0x48,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%rdi)
 { .bytes = { 0x49,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r8)
 { .bytes = { 0x49,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r9)
 { .bytes = { 0x49,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r10)
 { .bytes = { 0x49,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r11)
 { .bytes = { 0x49,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r12)
 { .bytes = { 0x49,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r13)
 { .bytes = { 0x49,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r14)
 { .bytes = { 0x49,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subq  %rdi, (%r15)
 { .bytes = { 0x4c,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rax)
 { .bytes = { 0x4c,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rcx)
 { .bytes = { 0x4c,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rdx)
 { .bytes = { 0x4c,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rbx)
 { .bytes = { 0x4c,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rsp)
 { .bytes = { 0x4c,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rbp)
 { .bytes = { 0x4c,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rsi)
 { .bytes = { 0x4c,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%rdi)
 { .bytes = { 0x4d,0x29,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r8)
 { .bytes = { 0x4d,0x29,0x01, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r9)
 { .bytes = { 0x4d,0x29,0x02, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r10)
 { .bytes = { 0x4d,0x29,0x03, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r11)
 { .bytes = { 0x4d,0x29,0x04,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r12)
 { .bytes = { 0x4d,0x29,0x45,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r13)
 { .bytes = { 0x4d,0x29,0x06, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r14)
 { .bytes = { 0x4d,0x29,0x07, }, .expectedOpcode = UD_Isub }, // subq  %r8, (%r15)
 { .bytes = { 0x4c,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rax)
 { .bytes = { 0x4c,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rcx)
 { .bytes = { 0x4c,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rdx)
 { .bytes = { 0x4c,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rbx)
 { .bytes = { 0x4c,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rsp)
 { .bytes = { 0x4c,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rbp)
 { .bytes = { 0x4c,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rsi)
 { .bytes = { 0x4c,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%rdi)
 { .bytes = { 0x4d,0x29,0x08, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r8)
 { .bytes = { 0x4d,0x29,0x09, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r9)
 { .bytes = { 0x4d,0x29,0x0a, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r10)
 { .bytes = { 0x4d,0x29,0x0b, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r11)
 { .bytes = { 0x4d,0x29,0x0c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r12)
 { .bytes = { 0x4d,0x29,0x4d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r13)
 { .bytes = { 0x4d,0x29,0x0e, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r14)
 { .bytes = { 0x4d,0x29,0x0f, }, .expectedOpcode = UD_Isub }, // subq  %r9, (%r15)
 { .bytes = { 0x4c,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rax)
 { .bytes = { 0x4c,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rcx)
 { .bytes = { 0x4c,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rdx)
 { .bytes = { 0x4c,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rbx)
 { .bytes = { 0x4c,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rsp)
 { .bytes = { 0x4c,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rbp)
 { .bytes = { 0x4c,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rsi)
 { .bytes = { 0x4c,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%rdi)
 { .bytes = { 0x4d,0x29,0x10, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r8)
 { .bytes = { 0x4d,0x29,0x11, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r9)
 { .bytes = { 0x4d,0x29,0x12, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r10)
 { .bytes = { 0x4d,0x29,0x13, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r11)
 { .bytes = { 0x4d,0x29,0x14,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r12)
 { .bytes = { 0x4d,0x29,0x55,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r13)
 { .bytes = { 0x4d,0x29,0x16, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r14)
 { .bytes = { 0x4d,0x29,0x17, }, .expectedOpcode = UD_Isub }, // subq  %r10, (%r15)
 { .bytes = { 0x4c,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rax)
 { .bytes = { 0x4c,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rcx)
 { .bytes = { 0x4c,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rdx)
 { .bytes = { 0x4c,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rbx)
 { .bytes = { 0x4c,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rsp)
 { .bytes = { 0x4c,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rbp)
 { .bytes = { 0x4c,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rsi)
 { .bytes = { 0x4c,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%rdi)
 { .bytes = { 0x4d,0x29,0x18, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r8)
 { .bytes = { 0x4d,0x29,0x19, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r9)
 { .bytes = { 0x4d,0x29,0x1a, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r10)
 { .bytes = { 0x4d,0x29,0x1b, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r11)
 { .bytes = { 0x4d,0x29,0x1c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r12)
 { .bytes = { 0x4d,0x29,0x5d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r13)
 { .bytes = { 0x4d,0x29,0x1e, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r14)
 { .bytes = { 0x4d,0x29,0x1f, }, .expectedOpcode = UD_Isub }, // subq  %r11, (%r15)
 { .bytes = { 0x4c,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rax)
 { .bytes = { 0x4c,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rcx)
 { .bytes = { 0x4c,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rdx)
 { .bytes = { 0x4c,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rbx)
 { .bytes = { 0x4c,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rsp)
 { .bytes = { 0x4c,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rbp)
 { .bytes = { 0x4c,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rsi)
 { .bytes = { 0x4c,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%rdi)
 { .bytes = { 0x4d,0x29,0x20, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r8)
 { .bytes = { 0x4d,0x29,0x21, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r9)
 { .bytes = { 0x4d,0x29,0x22, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r10)
 { .bytes = { 0x4d,0x29,0x23, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r11)
 { .bytes = { 0x4d,0x29,0x24,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r12)
 { .bytes = { 0x4d,0x29,0x65,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r13)
 { .bytes = { 0x4d,0x29,0x26, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r14)
 { .bytes = { 0x4d,0x29,0x27, }, .expectedOpcode = UD_Isub }, // subq  %r12, (%r15)
 { .bytes = { 0x4c,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rax)
 { .bytes = { 0x4c,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rcx)
 { .bytes = { 0x4c,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rdx)
 { .bytes = { 0x4c,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rbx)
 { .bytes = { 0x4c,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rsp)
 { .bytes = { 0x4c,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rbp)
 { .bytes = { 0x4c,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rsi)
 { .bytes = { 0x4c,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%rdi)
 { .bytes = { 0x4d,0x29,0x28, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r8)
 { .bytes = { 0x4d,0x29,0x29, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r9)
 { .bytes = { 0x4d,0x29,0x2a, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r10)
 { .bytes = { 0x4d,0x29,0x2b, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r11)
 { .bytes = { 0x4d,0x29,0x2c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r12)
 { .bytes = { 0x4d,0x29,0x6d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r13)
 { .bytes = { 0x4d,0x29,0x2e, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r14)
 { .bytes = { 0x4d,0x29,0x2f, }, .expectedOpcode = UD_Isub }, // subq  %r13, (%r15)
 { .bytes = { 0x4c,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rax)
 { .bytes = { 0x4c,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rcx)
 { .bytes = { 0x4c,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rdx)
 { .bytes = { 0x4c,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rbx)
 { .bytes = { 0x4c,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rsp)
 { .bytes = { 0x4c,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rbp)
 { .bytes = { 0x4c,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rsi)
 { .bytes = { 0x4c,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%rdi)
 { .bytes = { 0x4d,0x29,0x30, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r8)
 { .bytes = { 0x4d,0x29,0x31, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r9)
 { .bytes = { 0x4d,0x29,0x32, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r10)
 { .bytes = { 0x4d,0x29,0x33, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r11)
 { .bytes = { 0x4d,0x29,0x34,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r12)
 { .bytes = { 0x4d,0x29,0x75,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r13)
 { .bytes = { 0x4d,0x29,0x36, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r14)
 { .bytes = { 0x4d,0x29,0x37, }, .expectedOpcode = UD_Isub }, // subq  %r14, (%r15)
 { .bytes = { 0x4c,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rax)
 { .bytes = { 0x4c,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rcx)
 { .bytes = { 0x4c,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rdx)
 { .bytes = { 0x4c,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rbx)
 { .bytes = { 0x4c,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rsp)
 { .bytes = { 0x4c,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rbp)
 { .bytes = { 0x4c,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rsi)
 { .bytes = { 0x4c,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%rdi)
 { .bytes = { 0x4d,0x29,0x38, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r8)
 { .bytes = { 0x4d,0x29,0x39, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r9)
 { .bytes = { 0x4d,0x29,0x3a, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r10)
 { .bytes = { 0x4d,0x29,0x3b, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r11)
 { .bytes = { 0x4d,0x29,0x3c,0x24, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r12)
 { .bytes = { 0x4d,0x29,0x7d,0x00, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r13)
 { .bytes = { 0x4d,0x29,0x3e, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r14)
 { .bytes = { 0x4d,0x29,0x3f, }, .expectedOpcode = UD_Isub }, // subq  %r15, (%r15)
 { .bytes = { 0x67,0xd3,0x38, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%eax)
 { .bytes = { 0x67,0xd3,0x39, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%ecx)
 { .bytes = { 0x67,0xd3,0x3a, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%edx)
 { .bytes = { 0x67,0xd3,0x3b, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%ebx)
 { .bytes = { 0x67,0xd3,0x3c,0x24, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%esp)
 { .bytes = { 0x67,0xd3,0x7d,0x00, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%ebp)
 { .bytes = { 0x67,0xd3,0x3e, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%esi)
 { .bytes = { 0x67,0xd3,0x3f, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%edi)
 { .bytes = { 0x67,0x41,0xd3,0x38, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r8d)
 { .bytes = { 0x67,0x41,0xd3,0x39, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r9d)
 { .bytes = { 0x67,0x41,0xd3,0x3a, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r10d)
 { .bytes = { 0x67,0x41,0xd3,0x3b, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r11d)
 { .bytes = { 0x67,0x41,0xd3,0x3c,0x24, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r12d)
 { .bytes = { 0x67,0x41,0xd3,0x7d,0x00, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r13d)
 { .bytes = { 0x67,0x41,0xd3,0x3e, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r14d)
 { .bytes = { 0x67,0x41,0xd3,0x3f, }, .expectedOpcode = UD_Isar }, // sarl  %cl, (%r15d)
 { .bytes = { 0x67,0xd3,0x20, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%eax)
 { .bytes = { 0x67,0xd3,0x21, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%ecx)
 { .bytes = { 0x67,0xd3,0x22, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%edx)
 { .bytes = { 0x67,0xd3,0x23, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%ebx)
 { .bytes = { 0x67,0xd3,0x24,0x24, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%esp)
 { .bytes = { 0x67,0xd3,0x65,0x00, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%ebp)
 { .bytes = { 0x67,0xd3,0x26, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%esi)
 { .bytes = { 0x67,0xd3,0x27, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%edi)
 { .bytes = { 0x67,0x41,0xd3,0x20, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r8d)
 { .bytes = { 0x67,0x41,0xd3,0x21, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r9d)
 { .bytes = { 0x67,0x41,0xd3,0x22, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r10d)
 { .bytes = { 0x67,0x41,0xd3,0x23, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r11d)
 { .bytes = { 0x67,0x41,0xd3,0x24,0x24, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r12d)
 { .bytes = { 0x67,0x41,0xd3,0x65,0x00, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r13d)
 { .bytes = { 0x67,0x41,0xd3,0x26, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r14d)
 { .bytes = { 0x67,0x41,0xd3,0x27, }, .expectedOpcode = UD_Ishl }, // shll  %cl, (%r15d)
 { .bytes = { 0x67,0xd3,0x28, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%eax)
 { .bytes = { 0x67,0xd3,0x29, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%ecx)
 { .bytes = { 0x67,0xd3,0x2a, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%edx)
 { .bytes = { 0x67,0xd3,0x2b, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%ebx)
 { .bytes = { 0x67,0xd3,0x2c,0x24, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%esp)
 { .bytes = { 0x67,0xd3,0x6d,0x00, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%ebp)
 { .bytes = { 0x67,0xd3,0x2e, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%esi)
 { .bytes = { 0x67,0xd3,0x2f, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%edi)
 { .bytes = { 0x67,0x41,0xd3,0x28, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r8d)
 { .bytes = { 0x67,0x41,0xd3,0x29, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r9d)
 { .bytes = { 0x67,0x41,0xd3,0x2a, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r10d)
 { .bytes = { 0x67,0x41,0xd3,0x2b, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r11d)
 { .bytes = { 0x67,0x41,0xd3,0x2c,0x24, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r12d)
 { .bytes = { 0x67,0x41,0xd3,0x6d,0x00, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r13d)
 { .bytes = { 0x67,0x41,0xd3,0x2e, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r14d)
 { .bytes = { 0x67,0x41,0xd3,0x2f, }, .expectedOpcode = UD_Ishr }, // shrl  %cl, (%r15d)
 { .bytes = { 0x48,0x0f,0x7f,0x00, }, .expectedOpcode = UD_Imovq }, // movqq  %mmx0, (%rax)
};
#define NUM_TEST_INSNS 2609
#define MAX_INSN_BYTES 15

