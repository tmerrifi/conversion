
/* find_next_bit.c: fallback find next bit implementation
   2 *
   3 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
   4 * Written by David Howells (dhowells@redhat.com)
   5 *
   6 * This program is free software; you can redistribute it and/or
   7 * modify it under the terms of the GNU General Public License
   8 * as published by the Free Software Foundation; either version
   9 * 2 of the License, or (at your option) any later version.
  10 */


#include <stdlib.h>
#include "bitmap.h"

#define BITS_PER_LONG (sizeof(unsigned long) * 8)
#define BITOP_WORD(nr)          ((nr) / BITS_PER_LONG)

static inline unsigned long __ffs(unsigned long word)
{
  asm("bsf %1,%0"
      : "=r" (word)
      : "rm" (word));
  return word;
}

  
/*
 * Find the next set bit in a memory region.
 */
unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
			    unsigned long offset)
{
  const unsigned long *p = addr + BITOP_WORD(offset);
  unsigned long result = offset & ~(BITS_PER_LONG-1);
  unsigned long tmp;
  
  if (offset >= size)
    return size;
  size -= result;
  offset %= BITS_PER_LONG;
  if (offset) {
    tmp = *(p++);
    tmp &= (~0UL << offset);
    if (size < BITS_PER_LONG)
      goto found_first;
    if (tmp)
      goto found_middle;
    size -= BITS_PER_LONG;
    result += BITS_PER_LONG;
  }
  while (size & ~(BITS_PER_LONG-1)) {
    if ((tmp = *(p++)))
      goto found_middle;
    result += BITS_PER_LONG;
    size -= BITS_PER_LONG;
  }
  if (!size)
    return result;
  tmp = *p;
  
 found_first:
  tmp &= (~0UL >> (BITS_PER_LONG - size));
  if (tmp == 0UL)         /* Are any bits set? */
    return result + size;   /* Nope. */
 found_middle:
  return result + __ffs(tmp);
}
