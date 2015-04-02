#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_poll(const struct sys_state *sys, uint32_t *args)
{
	pollfd_s *fds_f = sys->mem_base + args[0];
	unsigned int i, nfds = args[1];
	int ret, events_ok, timeout_msecs = args[2];
	pollfd_s fds_b[nfds];

	for (i = 0; i < nfds; i++) {
		fds_b[i].fd = fds_f[i].fd;
		fds_b[i].events = f2b_poll_events(fds_f[i].events, &events_ok);
		if (!events_ok) {
			debug("Unrecognised frontend poll events 0x%x\n", fds_f[i].events);
			return -FRONT_EINVAL;
		}
		fds_b[i].revents = 0;
	}

	ret = sys_poll(fds_b, nfds, timeout_msecs);

	for (i = 0; i < nfds; i++) {
		fds_f[i].revents = b2f_poll_events(fds_b[i].revents, &events_ok);
		if (!events_ok) {
			debug("Unrecognised backend poll events 0x%x\n", fds_b[i].revents);
			return -FRONT_EINVAL;
		}
	}

	return ret;
}
