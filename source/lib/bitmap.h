
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

#ifndef KSNAP_BITMAP_H
#define KSNAP_BITMAP_H

#define for_each_bit(addr,size,val)   val=0;	\
  for(;val<size; val=find_next_bit(addr,size,val+1))


unsigned long find_next_bit(const unsigned long *addr, unsigned long size, unsigned long offset);

#endif
