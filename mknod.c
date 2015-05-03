/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [-m mode] name type major minor\n", argv0);
}

int
main(int argc, char *argv[])
{
	mode_t type, mode = 0644;
	dev_t dev;

	ARGBEGIN {
	case 'm':
		mode = estrtol(EARGF(usage()), 8);
		break;
	default:
		usage();
	} ARGEND;

	if (argc != 4)
		usage();

	if (strlen(argv[1]) != 1 || !strchr("ucb", argv[1][0]))
		eprintf("mknod: '%s': invalid type\n", argv[1]);
	type = (argv[1][0] == 'b') ? S_IFBLK : S_IFCHR;

	dev = makedev(estrtol(argv[2], 0), estrtol(argv[3], 0));

	if (mknod(argv[0], type|mode, dev) == -1)
		eprintf("mknod: '%s':", argv[0]);
	return 0;
}
