#include "debug.h"
#include "string.h"
#include "syscall.h"
#include "util.h"

int translate_sys_uname(front_utsname_s *buf)
{
	utsname_s h;
	int err;

	err = sys_uname(&h);
	if (!err) {
		memcpy(buf->sysname, h.sysname, min(sizeof(buf->sysname), sizeof(h.sysname)));
		buf->sysname[sizeof(buf->sysname) - 1] = 0;

		memcpy(buf->nodename, h.nodename, min(sizeof(buf->nodename), sizeof(h.nodename)));
		buf->nodename[sizeof(buf->nodename) - 1] = 0;

		memcpy(buf->release, h.release, min(sizeof(buf->release), sizeof(h.release)));
		buf->release[sizeof(buf->release) - 1] = 0;

		memcpy(buf->version, h.version, min(sizeof(buf->version), sizeof(h.version)));
		buf->version[sizeof(buf->version) - 1] = 0;

		memcpy(buf->machine, h.machine, min(sizeof(buf->machine), sizeof(h.machine)));
		buf->machine[sizeof(buf->machine) - 1] = 0;
	}

	return err;
}
