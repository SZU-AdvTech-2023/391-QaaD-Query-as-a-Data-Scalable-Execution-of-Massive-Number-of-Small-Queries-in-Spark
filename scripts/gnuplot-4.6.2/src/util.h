/*
 * $Id: util.h,v 1.36.2.2 2012/09/26 23:03:15 sfeam Exp $
 */

/* GNUPLOT - util.h */

/*[
 * Copyright 1986 - 1993, 1998, 2004   Thomas Williams, Colin Kelley
 *
 * Permission to use, copy, and distribute this software and its
 * documentation for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 *
 * Permission to modify the software is granted, but not the right to
 * distribute the complete modified source code.  Modifications are to
 * be distributed as patches to the released version.  Permission to
 * distribute binaries produced by compiling modified sources is granted,
 * provided you
 *   1. distribute the corresponding source modifications from the
 *    released version in the form of a patch file along with the binaries,
 *   2. add special version identification to distinguish your version
 *    in addition to the base release version number,
 *   3. provide your name and address as the primary contact for the
 *    support of your modified version, and
 *   4. retain our contact information in regard to use of the base
 *    software.
 * Permission to distribute the released version of the source code along
 * with corresponding source modifications in the form of a patch file is
 * granted with same provisions 2 through 4 for binary distributions.
 *
 * This software is provided "as is" without express or implied warranty
 * to the extent permitted by applicable law.
]*/

#ifndef GNUPLOT_UTIL_H
# define GNUPLOT_UTIL_H

#include "gp_types.h"
#include "stdfn.h"		/* for size_t */

/* special token number meaning 'do not draw the "caret"', for
 * int_error and friends: */
#define NO_CARET (-1)

/* token number meaning 'the error was in the datafile, not the
   command line' */
#define DATAFILE (-2)

/* TRUE if command just typed; becomes FALSE whenever we
 * send some other output to screen.  If FALSE, the command line
 * will be echoed to the screen before the ^ error message.
 */
extern TBOOLEAN screen_ok;

/* decimal sign */
extern char *decimalsign;
extern char *numeric_locale;	/* LC_NUMERIC */
extern char *current_locale;	/* LC_TIME */

/* degree sign */
extern char degree_sign[8];

extern const char *current_prompt; /* needed by is_error() and friends */

/* Functions exported by util.c: */

/* Command parsing helpers: */
int equals __PROTO((int, const char *));
int almost_equals __PROTO((int, const char *));
int isstring __PROTO((int));
int isanumber __PROTO((int));
int isletter __PROTO((int));
int is_definition __PROTO((int));
void copy_str __PROTO((char *, int, int));
size_t token_len __PROTO((int));
void quote_str __PROTO((char *, int, int));
void capture __PROTO((char *, int, int, int));
void m_capture __PROTO((char **, int, int));
void m_quote_capture __PROTO((char **, int, int));
char *try_to_get_string __PROTO((void));
void parse_esc __PROTO((char *));
int type_udv __PROTO((int));

char *gp_stradd __PROTO((const char *, const char *));
#define isstringvalue(c_token) (isstring(c_token) || type_udv(c_token)==STRING)

/* HBB 20010726: IMHO this one belongs into alloc.c: */
char *gp_strdup __PROTO((const char *));

/* HBB 20020405: moved this here, from axis.[ch] */
void gprintf __PROTO((char *, size_t, char *, double, double));

/* Error message handling */
#if defined(VA_START) && defined(STDC_HEADERS)
#  if defined(__GNUC__)
    void os_error __PROTO((int, const char *, ...)) __attribute__((noreturn));
    void int_error __PROTO((int, const char *, ...)) __attribute__((noreturn));
    void graph_error __PROTO((const char *, ...)) __attribute__((noreturn));
#  else
    void os_error __PROTO((int, const char *, ...));
    void int_error __PROTO((int, const char *, ...));
    void graph_error __PROTO((const char *, ...));
#  endif
void int_warn __PROTO((int, const char *, ...));
#else
void os_error __PROTO(());
void int_error __PROTO(());
void int_warn __PROTO(());
void graph_error __PROTO(());
#endif

/* FIXME HBB 20010726: should be moved to where help_comamnd() is, and
 * made static. Currently, that's command.c, but it should probably
 * move to help.c, instead.
 */
void squash_spaces __PROTO((char *));

TBOOLEAN existdir __PROTO((const char *));

char *getusername __PROTO((void));

TBOOLEAN contains8bit __PROTO((const char *s));
TBOOLEAN utf8toulong __PROTO((unsigned long * wch, const char ** str));
size_t strlen_utf8 __PROTO((const char *s));
size_t gp_strlen __PROTO((const char *s));
char * gp_strchrn __PROTO((const char *s, int N));
TBOOLEAN streq __PROTO((const char *a, const char *b));

#endif /* GNUPLOT_UTIL_H */
