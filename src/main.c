#include "debug.h"
#include "frontend.h"
#include "string.h"
#include "syscall.h"

int main(int argc, const char *argv[])
{
	const char *mips_elf_filename;
	int i;

	debug_init("/tmp/hoodwink.log");
	debug("Hoodwink starting\n");

	/* skip hoodwink program name */
	argv++;
	argc--;

	if (argc && !strcmp(argv[0], "-U")) {
		argv += 2;
		argc -= 2;
	}

	if (argc && !strcmp(argv[0], "-0")) {
		argv += 2;
		argc -= 2;
	}

	if (argc < 1) {
		debug("No MIPS ELF specified\n");
		sys_exit(1);
	} else {
		mips_elf_filename = argv[0];
		argv++;
		argc--;
	}

	debug("MIPS ELF: \"%s\"\n", mips_elf_filename);

	if (argc) {
		debug("Arguments:\n");
		for (i = 0; i < argc; i++)
			debug("  [%d] = \"%s\"\n", i, argv[i]);
	}

	frontend_init(mips_elf_filename);
	return 0;
}
