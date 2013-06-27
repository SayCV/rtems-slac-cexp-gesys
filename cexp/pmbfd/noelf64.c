#include "pmelf.h"
/* $Id: noelf64.c,v 1.1 2008/04/19 04:23:54 strauman Exp $ */

/* Empty stubs so that applications referring to 64-bit
 * routines link even if pmelf was only configured to
 * support 32-bit.
 */

/* 
 * Authorship
 * ----------
 * This software ('pmelf' ELF file reader) was created by
 *     Till Straumann <strauman@slac.stanford.edu>, 2008,
 * 	   Stanford Linear Accelerator Center, Stanford University.
 * 
 * Acknowledgement of sponsorship
 * ------------------------------
 * This software was produced by
 *     the Stanford Linear Accelerator Center, Stanford University,
 * 	   under Contract DE-AC03-76SFO0515 with the Department of Energy.
 * 
 * Government disclaimer of liability
 * ----------------------------------
 * Neither the United States nor the United States Department of Energy,
 * nor any of their employees, makes any warranty, express or implied, or
 * assumes any legal liability or responsibility for the accuracy,
 * completeness, or usefulness of any data, apparatus, product, or process
 * disclosed, or represents that its use would not infringe privately owned
 * rights.
 * 
 * Stanford disclaimer of liability
 * --------------------------------
 * Stanford University makes no representations or warranties, express or
 * implied, nor assumes any liability for the use of this software.
 * 
 * Stanford disclaimer of copyright
 * --------------------------------
 * Stanford University, owner of the copyright, hereby disclaims its
 * copyright and all other rights in this software.  Hence, anyone may
 * freely use it for any purpose without restriction.  
 * 
 * Maintenance of notices
 * ----------------------
 * In the interest of clarity regarding the origin and status of this
 * SLAC software, this and all the preceding Stanford University notices
 * are to remain affixed to any copy or derivative of this software made
 * or distributed by the recipient and are to be affixed to any copy of
 * software made or distributed by the recipient that contains a copy or
 * derivative of this software.
 * 
 * ------------------ SLAC Software Notices, Set 4 OTT.002a, 2004 FEB 03
 */ 

int
pmelf_getshdr64(Elf_Stream s, Elf64_Shdr *pshdr)
{
	return -3;
}

int
pmelf_getsym64(Elf_Stream s, Elf64_Sym *psym)
{
	return -3;
}

void 
pmelf_dump_shdr64(FILE *f, Elf64_Shdr *pshdr, int format)
{
}

void
pmelf_dump_sym64(FILE *f, Elf64_Sym *sym, Pmelf_Shtab shtab, const char *strtab, unsigned strtablen, int format)
{
}

int
pmelf_putehdr64(Elf_Stream s, Elf64_Ehdr *pehdr)
{
	return -3;
}

int
pmelf_putshdr64(Elf_Stream s, Elf64_Shdr *pshdr)
{
	return -3;
}

int
pmelf_putsym64(Elf_Stream s, Elf64_Sym *psym)
{
	return -3;
}
