/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>

#include <stdio.h>

#include "util.h"

static int mflag = 0;

static unsigned int
b64e(unsigned char b[2])
{
	unsigned int o = 0;
	unsigned int p = b[2] | (b[1] << 8) | (b[0] << 16);
	const char b64et[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	o = b64et[p & 0x3f]; p >>= 6;
	o = (o << 8) | b64et[p & 0x3f]; p >>= 6;
	o = (o << 8) | b64et[p & 0x3f]; p >>= 6;
	o = (o << 8) | b64et[p & 0x3f];

	return o;
}

static void
uuencodeb64(FILE *fp, const char *name, const char *s)
{
	struct stat st;
	ssize_t n, m = 0;
	unsigned char buf[45], *pb;
	unsigned int out[sizeof(buf)/3 + 1], *po;

	if (fstat(fileno(fp), &st) < 0)
		eprintf("fstat %s:", s);
	printf("begin-base64 %o %s\n", st.st_mode & 0777, name);
	/* write line by line */
	while ((n = fread(buf, 1, sizeof(buf), fp))) {
		/* clear old buffer if converting with non-multiple of 3 */
		if (n != sizeof(buf) && (m = n % 3) != 0) {
			buf[n] = '\0'; /* m == 2 */
			if (m == 1) buf[n+1] = '\0'; /* m == 1 */
		}
		for (pb = buf, po = out; pb < buf + n; pb += 3)
			*po++ = b64e(pb);
		if (m != 0) {
			unsigned int mask = 0xffffffff, dest = 0x3d3d3d3d;
			/* m==2 -> 0x00ffffff; m==1 -> 0x0000ffff */
			mask >>= ((3-m) << 3);
			po[-1] = (po[-1] & mask) | (dest & ~mask);
		}
		*po++ = '\n';
		fwrite(out, 1, (po - out) * sizeof(unsigned int) - 3, stdout);
	}
	if (ferror(fp))
		eprintf("'%s' read error:", s);
	puts("====");
}

static void
uuencode(FILE *fp, const char *name, const char *s)
{
	struct stat st;
	unsigned char buf[45], *p;
	ssize_t n;
	int ch;

	if (fstat(fileno(fp), &st) < 0)
		eprintf("fstat %s:", s);
	printf("begin %o %s\n", st.st_mode & 0777, name);
	while ((n = fread(buf, 1, sizeof(buf), fp))) {
		ch = ' ' + (n & 0x3f);
		putchar(ch == ' ' ? '`' : ch);
		for (p = buf; n > 0; n -= 3, p += 3) {
			if (n < 3) {
				p[2] = '\0';
				if (n < 2)
					p[1] = '\0';
			}
			ch = ' ' + ((p[0] >> 2) & 0x3f);
			putchar(ch == ' ' ? '`' : ch);
			ch = ' ' + (((p[0] << 4) | ((p[1] >> 4) & 0xf)) & 0x3f);
			putchar(ch == ' ' ? '`' : ch);
			ch = ' ' + (((p[1] << 2) | ((p[2] >> 6) & 0x3)) & 0x3f);
			putchar(ch == ' ' ? '`' : ch);
			ch = ' ' + (p[2] & 0x3f);
			putchar(ch == ' ' ? '`' : ch);
		}
		putchar('\n');
	}
	if (ferror(fp))
		eprintf("'%s' read error:", s);
	printf("%c\nend\n", '`');
}

static void
usage(void)
{
	eprintf("usage: %s [-m] [file] name\n", argv0);
}

int
main(int argc, char *argv[])
{
	FILE *fp = NULL;

	ARGBEGIN {
	case 'm':
		mflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (!argc || argc > 2)
		usage();

	if (argc == 1) {
		if (mflag)
			uuencodeb64(stdin, argv[0], "<stdin>");
		else
			uuencode(stdin, argv[0], "<stdin>");
	} else {
		if (!(fp = fopen(argv[0], "r")))
			eprintf("fopen %s:", argv[0]);
		if (mflag)
			uuencodeb64(fp, argv[1], argv[0]);
		else
			uuencode(fp, argv[1], argv[0]);
	}

	return !!((fp && fshut(fp, argv[0])) + fshut(stdin, "<stdin>") +
	          fshut(stdout, "<stdout>"));
}
