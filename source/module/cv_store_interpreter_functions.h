#ifndef CV_STORE_INTERP_FUNCS
#define CV_STORE_INTERP_FUNCS

//#define CV_STORE_INTERP_DEBUG

#if defined(__KERNEL__)
#if defined(CV_STORE_INTERP_DEBUG)
#define printf(...) printk(KERN_INFO __VA_ARGS__)
#else
#define printf(...)
#endif
#define assert(...) BUG_ON(!(__VA_ARGS__))
#endif


void verifyOpcodesAndRegisters(void);

int interpret(const uint8_t* instruction_ptr, const uint32_t instruction_len, void* dstAddress, struct pt_regs* context, uint32_t mix, void * disassemble_cache);

void * interpret_allocate_disassemble_cache(void);

void interpret_free_disassemble_cache(void *);


#endif
