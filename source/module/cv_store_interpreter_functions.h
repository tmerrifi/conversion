#ifndef CV_STORE_INTERP_FUNCS
#define CV_STORE_INTERP_FUNCS

#if defined(__KERNEL__)
#if defined(CV_STORE_INTERP_DEBUG)
#define printf(...) printk(KERN_INFO __VA_ARGS__)
#else
#define printf(...)
#endif
#define assert(...) BUG_ON(!(__VA_ARGS__))
#endif


void verifyOpcodesAndRegisters(void);

int interpret(const uint8_t* instruction_ptr, const uint32_t instruction_len, void* dstAddress, struct pt_regs* context);

#endif
