#include "debug.h"
#include "frontend.h"
#include "string.h"
#include "syscall.h"

int main(int argc, const char *argv[])
{
	const char *mips_elf_filename;
	const char *new_argv[argc];
	int i, new_argc = 0;

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

	new_argv[new_argc++] = mips_elf_filename;

	for (i = 0; i < argc; i++)
		new_argv[new_argc++] = argv[i];

	debug("Arguments:\n");
	for (i = 0; i < new_argc; i++)
		debug("  [%d] = \"%s\"\n", i, new_argv[i]);

	frontend_init(mips_elf_filename, new_argc, new_argv);
	return 0;
}
