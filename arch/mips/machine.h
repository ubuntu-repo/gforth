/* This is the machine-specific part for MIPS R[2346810]000 processors

  Authors: Anton Ertl, Bernd Paysan, David Kühling
  Copyright (C) 1995,1996,1997,1998,2000,2003,2005,2007,2010,2016,2018 Free Software Foundation, Inc.

  This file is part of Gforth.

  Gforth is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation, either version 3
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see http://www.gnu.org/licenses/.
*/

#if !defined(USE_TOS) && !defined(USE_NO_TOS)
/* on the mips this is a mixed blessing, since defining this spills
   the rp with some gcc versions. This machine has 31 regs, yet that's
   not enough for gcc-2.4.5 :-( */
#define USE_TOS
#endif

/* cache flush stuff */
#include "../generic/machine.h"

#ifndef FLUSH_ICACHE
# if defined(ultrix)
#  include <mips/cachectl.h>
# elif (defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__))
#  if (SIZEOF_VOID_P == 4)
#   include <mips/sysarch.h>
#  else
#   include <mips64/sysarch.h>
#  endif
# else
/* works on Irix and Android */
#  include <sys/cachectl.h>
# endif

#define FLUSH_ICACHE(addr,size) \
			cacheflush((char *)(addr), (int)(size), BCACHE)
#endif

#ifdef FORCE_REG
#define IPREG asm("$16")
#define SPREG asm("$17")
#define RPREG asm("$18")
#define LPREG asm("$19")
#define CFAREG asm("$20")
#define TOSREG asm("$21")
#endif /* FORCE_REG */

int check_prim(char *start, int len);

#define CHECK_PRIM(start,len) check_prim(start,len)
