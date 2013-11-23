/* Copyright (C) 1986, 1989 Free Software Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley, the University of Illinois,
 * Urbana, and Sun Microsystems, Inc.  The name of either University
 * or Sun Microsystems may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * MS-DOS port (c) 1990 by Thorsten Ohl, ohl@gnu.ai.mit.edu
 *
 * To this port, the same copying conditions apply as to the
 * original release.
 *
 * IMPORTANT:
 * This file is not identical to the original GNU release!
 * You should have received this code as patch to the official
 * GNU release.
 *
 * MORE IMPORTANT:
 * This port comes with ABSOLUTELY NO WARRANTY.
 *
 * $Header: e:/gnu/indent/RCS/globs.c'v 1.1.0.4 90/07/02 20:25:09 tho Exp $
 */

#include "indent_globs.h"

/* Like malloc but get error if no storage available.  */

#ifdef MSDOS
void *xmalloc (size_t size)		/* cleaner anyway ... */
{
  register void *val = malloc (size);
  if (!val)
    {
      fprintf (stderr,"indent: Virtual memory exhausted.\n");
      exit (1);
    }
  return val;
}
#else /* not MSDOS */
char *
xmalloc (size)
     long size;
{
  register char *val = (char *) malloc (size);
  if (!val)
    {
      fprintf (stderr,"indent: Virtual memory exhausted.\n");
      exit (1);
    }
  return val;
}
#endif /* not MSDOS */

/* Like realloc but get error if no storage available.  */

#ifdef MSDOS
void *xrealloc (void *ptr, size_t size)	/* cleaner anyway ... */
{
  register void *val = realloc (ptr, size);
  if (!val)
    {
      fprintf (stderr,"indent: Virtual memory exhausted.\n");
      exit (1);
    }
  return val;
}
#else /* not MSDOS */
char *
xrealloc (ptr, size)
     char *ptr;
     long size;
{
  register char *val = (char *) realloc (ptr, size);
  if (!val)
    {
      fprintf (stderr,"indent: Virtual memory exhausted.\n");
      exit (1);
    }
  return val;
}
#endif /* not MSDOS */

/* Some systems lack memcpy so this does the same thing.
   If your system-supplied memcpy is more efficient, you might want
   to put "#define mymemcpy memcpy" in indent_globs.h.

   Copy LEN bytes starting at SRCADDR to DESTADDR.  Result undefined
   if the source overlaps with the destination.  */
#ifndef MSDOS
char *
mymemcpy (destaddr, srcaddr, len)
     char *destaddr;
     char *srcaddr;
     int len;
{
  for (; len; len--)
    *destaddr++ = *srcaddr++;
  return destaddr;
}
#endif /* not MSDOS */


/* malloc a block of memory, with fatal error message if we can't do it. */

#ifdef M_I86HM

#include <dos.h>

void huge *
xhalloc (long size)
{
  void huge *value = (void huge *) halloc (size, (size_t)1 );

  if (!value)
    {
      fprintf (stderr, "indent: Virtual memory exhausted.\n");
      exit (1);
    }
  return value;
}

/* Here we do a huge "realloc" by allocating a new block and
   moving the old block afterwards.  This is *slow*, but should
   be reliable.  */

void huge *
xhrealloc (void huge *ptr, long new_size, long old_size)
{
  void huge *value = (void huge *) halloc (new_size, (size_t)1 );

  if (!value)
    {
      fprintf (stderr,"indent: Virtual memory exhausted.\n");
      exit (1);
    }
  else
    {
      char huge *dest = value;
      char huge *src = ptr;

      while (old_size > 0L)
	{
	  unsigned int bytes = (unsigned int) min (0x8000L, old_size);
	  memcpy (dest, src, bytes);
	  old_size -= (long) bytes;
	  dest += (long) bytes;
	  src += (long) bytes;
	}
    }
  hfree (ptr);
  return value;
}

long		/* doesn't belong here, but is also a 'huge' pointer kludge */
hread (int fd, void huge *buffer, long bytes)
{
  long bytes_read = 0L;

  while (1)
    {
      int n = read (fd, buffer, (unsigned int) min (0x4000L, bytes));

      if (n > 0)
	{
	  bytes_read += (long) n;
	  bytes -= (long) n;
	  /* we can't say buffer += n here, because we have to make
	     sure that the offset of BUFFER doesn't overflow during
	     the read() system call.  Therefore we add what we read
	     to the segment of BUFFER.  */
	  FP_SEG(buffer) += (n >> 4);
	  FP_OFF(buffer) += (n & 0x0F);
	}
      else if (n == 0)
	return bytes_read;	/* done */
      else
	{
	  perror ("indent: Error while reading input");
	  exit (1);
	}
    }
}


long
hwrite (int fd, void huge *buffer, long bytes)
{
  long bytes_written = 0L;

  while (1)
    {
      unsigned int n = (unsigned int) min (0x4000L, bytes);
      unsigned int m = write (fd, buffer, n);

      if (m == n)
	{
	  bytes_written += (long) m;
	  bytes -= (long) m;

	  if (bytes <= 0)
	    return bytes_written;

	  /* we can't say buffer += n here, because we have to make
	     sure that the offset of BUFFER doesn't overflow during
	     the read() system call.  Therefore we add what we read
	     to the segment of BUFFER.  */
	  FP_SEG(buffer) += (m >> 4);
	  FP_OFF(buffer) += (m & 0x0F);
	}
      else
	{
	  perror ("indent: Error while reading input");
	  exit (1);
	}
    }
}

#endif /* M_I86HM */
