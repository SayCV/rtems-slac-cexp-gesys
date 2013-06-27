/* $Id: cexpsyms.c,v 1.26 2009/03/09 18:30:53 till Exp $ */

/* generic symbol table handling */

/* SLAC Software Notices, Set 4 OTT.002a, 2004 FEB 03
 *
 * Authorship
 * ----------
 * This software (CEXP - C-expression interpreter and runtime
 * object loader/linker) was created by
 *
 *    Till Straumann <strauman@slac.stanford.edu>, 2002-2008,
 * 	  Stanford Linear Accelerator Center, Stanford University.
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
 * SLAC Software Notices, Set 4 OTT.002a, 2004 FEB 03
 */ 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cexp_regex.h>

#include "cexpsymsP.h"
#include "cexpmod.h"
#include "vars.h"
/* NOTE: DONT EDIT 'cexp.tab.h'; it is automatically generated by 'bison' */
#include "cexp.tab.h"

#ifndef LINKER_VERSION_SEPARATOR
#define LINKER_VERSION_SEPARATOR '@'
#endif

/* compare the name of two symbols 
 * (in a not very fancy way)
 * The clue is to handle the symbol
 * versioning in an appropriate way...
 */
int
_cexp_namecomp(const void *key, const void *cmp)
{
CexpSym				sa=(CexpSym)key;
CexpSym				sb=(CexpSym)cmp;
#if	LINKER_VERSION_SEPARATOR
register const char	*k=sa->name, *c=sb->name;

	while (*k) {
		register int	rval;
		if ((rval=*k++-*c++))
			return rval; /* this also handles the case where *c=='\0' */
		
	}
	/* key string is exhausted */
	return !*c || LINKER_VERSION_SEPARATOR==*c ? 0 : -1;
#else
	return strcmp(sa->name, sb->name);
#endif
}

/* compare the 'values' of two symbols, i.e. the addresses
 * they represent.
 */
int
_cexp_addrcomp(const void *a, const void *b)
{
	CexpSym *sa=(CexpSym*)a;
	CexpSym *sb=(CexpSym*)b;
	return (*sa)->value.ptv-(*sb)->value.ptv;
}

CexpSym
cexpSymTblLookup(const char *name, CexpSymTbl t)
{
CexpSymRec key;
	key.name = name;
	return (CexpSym)bsearch((void*)&key,
				t->syms,
				t->nentries,
				sizeof(*t->syms),
				_cexp_namecomp);
}

#define USE_ELF_MEMORY

#ifdef HAVE_RCMD
#include <sys/time.h>
#include <errno.h>
#if !defined(HAVE_RTEMS_H) && defined(__rtems__)
/* avoid pulling in networking headers under __rtems__
 * until BSP stuff is separated out from the core
 */
#define	AF_INET	2
extern char *inet_ntop();
extern int	socket();
extern int  select();
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define RSH_PORT 514

static char *
handleInput(int fd, int errfd, unsigned long *psize)
{
long	n=0,size,avail;
fd_set	r,w,e;
char	errbuf[1000],*ptr,*buf;
struct  timeval timeout;

register long ntot=0,got,put,idx;

	if (n<fd)		n=fd;
	if (n<errfd)	n=errfd;

	n++;

	buf=ptr=0;
	size=avail=0;

	while (fd>=0 || errfd>=0) {
		FD_ZERO(&r);
		FD_ZERO(&w);
		FD_ZERO(&e);

		timeout.tv_sec=5;
		timeout.tv_usec=0;
		if (fd>=0) 		FD_SET(fd,&r);
		if (errfd>=0)	FD_SET(errfd,&r);
		if ((got=select(n,&r,&w,&e,&timeout))<=0) {
				if (got) {
					fprintf(stderr,"rsh select() error: %s.\n",
							strerror(errno));
				} else {
					fprintf(stderr,"rsh timeout\n");
				}
				goto cleanup;
		}
		if (errfd>=0 && FD_ISSET(errfd,&r)) {
				got=read(errfd,errbuf,sizeof(errbuf));
				if (got<0) {
					fprintf(stderr,"rsh error (reading stderr): %s.\n",
							strerror(errno));
					goto cleanup;
				}
				if (got) {
					idx = 0;
					do {
						put = write(2,errbuf+idx,got);
						if ( put <= 0 ) {
							fprintf(stderr,"rsh error (writing stderr): %s.\n",
									strerror(errno));
							goto cleanup;
						}
						idx += put;
						got -= put;
					} while ( got > 0 );
				} else {
					errfd=-1; 
				}
		}
		if (fd>=0 && FD_ISSET(fd,&r)) {
				if (avail < LOAD_CHUNK) {
					size+=LOAD_CHUNK; avail+=LOAD_CHUNK;
					if (!(buf=realloc(buf,size))) {
						fprintf(stderr,"out of memory\n");
						goto cleanup;
					}
					ptr = buf + (size-avail);
				}
				got=read(fd,ptr,avail);
				if (got<0) {
					fprintf(stderr,"rsh error (reading stdout): %s.\n",
							strerror(errno));
					goto cleanup;
				}
				if (got) {
					ptr+=got;
					ntot+=got;
					avail-=got;
				} else {
					fd=-1;
				}
		}
	}
	if (psize) *psize=ntot;
	return buf;
cleanup:
	free(buf);
	return 0;
}

char *
rshLoad(char *host, char *user, char *cmd)
{
char	*chpt=host,*buf=0;
int		fd,errfd;
long	ntot;
extern  int rcmd();

	fd=rcmd(&chpt,RSH_PORT,user,user,cmd,&errfd);
	if (fd<0) {
		fprintf(stderr,"rcmd: got no remote stdout descriptor\n");
		goto cleanup;
	}
	if (errfd<0) {
		fprintf(stderr,"rcmd: got no remote stderr descriptor\n");
		goto cleanup;
	}

	if (!(buf=handleInput(fd,errfd,&ntot))) {
		goto cleanup; /* error message has already been printed */
	}

	fprintf(stderr,"0x%lx (%li) bytes read\n",ntot,ntot);

cleanup:
	if (fd>=0)		close(fd);
	if (errfd>=0)	close(errfd);
	return buf;
}
#endif

/* a semi-public routine which takes a precompiled regexp.
 * The reason this is not public is that we try to keep
 * the public from having to deal with/know about the regexp
 * implementation, i.e. which variant, which headers etc.
 */
CexpSym
_cexpSymTblLookupRegex(cexp_regex *rc, int *pmax, CexpSym s, FILE *f, CexpSymTbl t)
{
CexpSym	found=0;
int		max=24;

	if (!pmax)
		pmax=&max;

	if (!s)		s=t->syms;

	while (s->name && *pmax) {
		if (cexp_regexec(rc,s->name)) {
			if (f) cexpSymPrintInfo(s,f);
			(*pmax)--;
			found=s;
		}
		s++;
	}

	return s->name ? found : 0;
}

CexpSym
cexpSymTblLookupRegex(char *re, int *pmax, CexpSym s, FILE *f, CexpSymTbl t)
{
CexpSym		found;
cexp_regex	*rc;
int			max=24;

	if (!pmax)
		pmax=&max;

	if (!(rc=cexp_regcomp(re))) {
		fprintf(stderr,"unable to compile regexp '%s'\n",re);
		return 0;
	}
	found=_cexpSymTblLookupRegex(rc,pmax,s,f,t);

	if (rc) cexp_regfree(rc);
	return found;
}

CexpSymTbl
cexpCreateSymTbl(void *syms, int symSize, int nsyms, CexpSymFilterProc filter, CexpSymAssignProc assign, void *closure)
{
char		*sp,*dst;
const char	*symname;
CexpSymTbl	rval;
CexpSym		cesp;
int			n,nDstSyms,nDstChars;

	if (!(rval=(CexpSymTbl)malloc(sizeof(*rval))))
			return 0;

	memset(rval,0,sizeof(*rval));
	
	if ( filter && assign ) {
		/* count the number of valid symbols */
		for (sp=syms,n=0,nDstSyms=0,nDstChars=0; n<nsyms; sp+=symSize,n++) {
				if ((symname=filter(sp,closure))) {
					nDstChars+=strlen(symname)+1;
					nDstSyms++;
				}
		}


		/* create our copy of the symbol table - the object format contains
		 * many things we're not interested in and also, it's not
		 * sorted...
		 */
		
		/* allocate all the table space */
		if (!(rval->syms=(CexpSym)malloc(sizeof(CexpSymRec)*(nDstSyms+1))))
			goto cleanup;
	
		if (!(rval->strtbl=(char*)malloc(nDstChars)) ||
   	     !(rval->aindex=(CexpSym*)malloc(nDstSyms*sizeof(*rval->aindex))))
			goto cleanup;
	
		/* now copy the relevant stuff */
		for (sp=syms,n=0,cesp=rval->syms,dst=rval->strtbl; n<nsyms; sp+=symSize,n++) {
			if ((symname=filter(sp,closure))) {
					memset(cesp,0,sizeof(*cesp));
					/* copy the name to the string table and put a pointer
					 * into the symbol table.
					 */
					cesp->name=dst;
					while ((*(dst++)=*(symname++)))
							/* do nothing else */;
					cesp->flags = 0;
					rval->aindex[cesp-rval->syms]=cesp;
	
					assign(sp,cesp,closure);
	
				
					cesp++;
			}
		}
		/* mark the last table entry */
		cesp->name=0;
	} else { /* no filter or assign callback -- they pass us a list of symbols in already */
		nDstSyms   = nsyms;
		if ( !(rval->aindex=(CexpSym*)malloc(nDstSyms*sizeof(*rval->aindex))) )
			goto cleanup;
		rval->syms = syms;
		for ( cesp = rval->syms; cesp->name; cesp++ ) {
			rval->aindex[cesp-rval->syms] = cesp;
		}
	}

	rval->nentries=nDstSyms;

	/* sort the tables */
	qsort((void*)rval->syms,
		rval->nentries,
		sizeof(*rval->syms),
		_cexp_namecomp);
	qsort((void*)rval->aindex,
		rval->nentries,
		sizeof(*rval->aindex),
		_cexp_addrcomp);

	return rval;

cleanup:
	cexpFreeSymTbl(&rval);
	return 0;
}


void
cexpFreeSymTbl(CexpSymTbl *pt)
{
CexpSymTbl	st=*pt;
CexpSym		s;
int			i;
	if (st) {
		/* release help info */
		for (s=st->syms, i=0;  i<st->nentries; i++,s++) {
			if (s->flags & CEXP_SYMFLG_MALLOC_HELP) {
				free(s->help);
			}
		}
		free(st->syms);
		free(st->strtbl);
		free(st->aindex);
		free(st);
	}
	*pt=0;
}

int
cexpSymPrintInfo(CexpSym s, FILE *f)
{
int			i=0,k;
CexpType	t=s->value.type;

	if (!f) f=stdout;

	i+=fprintf(f,"%10p[%6d]: ",
			(void*)s->value.ptv,
			s->size);
	if (!CEXP_TYPE_FUNQ(t)) {
		i+=cexpTAPrintInfo(&s->value, f);
	} else {
		for (k=0; k<30; k++)
			fputc(' ',f);
		i+=k;
		i+=fprintf(f,"%s",cexpTypeInfoString(t));
	}
	while (i++<50)
		fputc(' ',f);
	i+=fprintf(f,"%s\n", s->name);
	return i;
}

/* do a binary search for an address returning its aindex number;
 * if multiple entries exist, return the highest index.
 */
int
cexpSymTblLkAddrIdx(void *addr, int margin, FILE *f, CexpSymTbl t)
{
int			lo,hi,mid;

	lo=0; hi=t->nentries-1;
		
	while (lo < hi) {
		mid=(lo+hi+1)>>1; /* round up */
		if (addr < (void*)t->aindex[mid]->value.ptv)
			hi = mid-1;
		else
			lo = mid;
	}
	
	mid=lo;

	if (f) {
		lo=mid-margin; if (lo<0) 		 	lo=0;
		hi=mid+margin; if (hi>=t->nentries)	hi=t->nentries-1;
		while (lo<=hi)
			cexpSymPrintInfo(t->aindex[lo++],f);
	}
	return mid;
}

CexpSym
cexpSymTblLkAddr(void *addr, int margin, FILE *f, CexpSymTbl t)
{
	return t->aindex[cexpSymTblLkAddrIdx(addr,margin,f,t)];
}

/* currently, we have only very rudimentary support; just enough
 * for 'HELP'
 */
static char *
symHelp(CexpTypedVal returnVal, CexpSym sym, va_list ap)
{
CexpTypedVal v;
char *newhelp=0;
int  verbose=0;

	returnVal->type=TUCharP;
	returnVal->tv.p=sym->help;

	if ((v=va_arg(ap,CexpTypedVal))) {
		switch (v->type) {
			case TUCharP:
				newhelp = v->tv.p;
				break;
			case TULong:
				verbose = v->tv.l;
				break;
			default:
				return "Cexp Help: Warning, invalid argument";

		}
	}
	
	if (newhelp) {
		if (sym->flags & CEXP_SYMFLG_MALLOC_HELP)
			free(sym->help);
#if defined(CONFIG_STRINGS_LIVE_FOREVER) && 0 /* might come from another module; we better make a copy */
		/* the help storage is probably an 'eternal' string */
		sym->help=newhelp;
#else
		sym->help=strdup(newhelp);
		sym->flags |= CEXP_SYMFLG_MALLOC_HELP;
#endif
	} else {
		if (verbose || !sym->help) {
			CexpSym		s;
			CexpModule	m;
			if ((s=cexpSymLkAddr(sym->value.ptv,0,0,&m)) &&
				 s==sym && m) {
				fprintf(stdout,"In module %s:\n",cexpModuleName(m));
			} else if ((s=cexpVarLookup(sym->name,0)) &&
						s==sym) {
				fprintf(stdout,"User Variable:\n");
			}
			cexpSymPrintInfo(sym,stdout);
		}
		if (sym->help)
			fprintf(stdout,"%s\n",sym->help);
		else
			fprintf(stdout,"No help available\n");
	}
	return 0;
}

char *
cexpSymMember(CexpTypedVal returnVal, CexpSym sym, char *mname, ...)
{
char 	*rval="member not implemented";
va_list ap;

	va_start(ap, mname);

	if (!strcmp("help",mname)) {
		rval=symHelp(returnVal, sym, ap);
	}

	va_end(ap);
	return rval;
}

const char *
cexpSymName(CexpSym s)
{
	return s ? s->name : 0;
}

void *
cexpSymValue(CexpSym s)
{
	return s ? (void*)s->value.ptv : 0;
}
