/* See LICENSE file for copyright and license details. */
#include <sys/types.h>

#include "regex.h"
#include <stddef.h>
#include <stdio.h>

#include "arg.h"
#include "compat.h"

#define UTF8_POINT(c) (((c) & 0xc0) != 0x80)

#undef MIN
#define MIN(x,y)  ((x) < (y) ? (x) : (y))
#undef MAX
#define MAX(x,y)  ((x) > (y) ? (x) : (y))
#undef LIMIT
#define LIMIT(x, a, b)  (x) = (x) < (a) ? (a) : (x) > (b) ? (b) : (x)

#define LEN(x) (sizeof (x) / sizeof *(x))

#ifndef _POSIX_HOST_NAME_MAX
    #define _POSIX_HOST_NAME_MAX 255
#endif

extern char *argv0;

void *ecalloc(size_t, size_t);
void *emalloc(size_t);
void *erealloc(void *, size_t);
#undef reallocarray
void *reallocarray(void *, size_t, size_t);
void *ereallocarray(void *, size_t, size_t);
char *estrdup(const char *);
char *estrndup(const char *, size_t);
void *encalloc(int, size_t, size_t);
void *enmalloc(int, size_t);
void *enrealloc(int, void *, size_t);
char *enstrdup(int, const char *);
char *enstrndup(int, const char *, size_t);

void enfshut(int, FILE *, const char *);
void efshut(FILE *, const char *);
int  fshut(FILE *, const char *);

void enprintf(int, const char *, ...);
void eprintf(const char *, ...);
void weprintf(const char *, ...);

double estrtod(const char *);

#undef strcasestr
char *strcasestr(const char *, const char *);

#undef strlcat
size_t strlcat(char *, const char *, size_t);
size_t estrlcat(char *, const char *, size_t);
#undef strlcpy
size_t strlcpy(char *, const char *, size_t);
size_t estrlcpy(char *, const char *, size_t);

#undef strsep
char *strsep(char **, const char *);

/* regex */
int enregcomp(int, regex_t *, const char *, int);
int eregcomp(regex_t *, const char *, int);

/* misc */
void enmasse(int, char **, int (*)(const char *, const char *, int));
void fnck(const char *, const char *, int (*)(const char *, const char *, int), int);
mode_t getumask(void);
char *humansize(double);
mode_t parsemode(const char *, mode_t, mode_t);
void putword(const char *);
#undef strtonum
long long strtonum(const char *, long long, long long, const char **);
long long enstrtonum(int, const char *, long long, long long);
long long estrtonum(const char *, long long, long long);
size_t unescape(char *);

/* ubase */

// For dd.c: get device size
#define BLKGETSIZE64 _IOR(0x12,114,size_t)
//
#define POSIX_FADV_SEQUENTIAL   2
#define POSIX_FADV_DONTNEED     4
// expect more data
#define SPLICE_F_MORE   (0x04)

#ifndef __ANDROID__
    #include <sys/statvfs.h>
#else
    #include <sys/vfs.h>
    #define statvfs statfs
    #define fstatvfs fstatfs
#endif

#define MS_RELATIME     (1<<21)
#define MNTOPT_NOAUTO   "noauto"
#define MNTTYPE_SWAP    "swap" 
#define TTY_NAME_MAX 32

long estrtol(const char *, int);
unsigned long estrtoul(const char *, int);
FILE* setmntent(const char* path, const char* mode);
int endmntent(FILE* fp);
ssize_t agetline(char **, size_t *, FILE *);
void devtotty(int, int *, int *);
int ttytostr(int, int, char *, size_t);
