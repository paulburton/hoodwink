#include "debug.h"
#include "string.h"
#include "syscall.h"

uint32_t translate_sys_connect(const struct sys_state *sys, uint32_t *args)
{
	int sockfd = args[0];
	sockaddr_s *addr = sys->mem_base + args[1];
	int addrlen = args[2];

	switch (addr->sa_family) {
	case 1:
		debug(" AF_UNIX \"%s\"", addr->sa_data);
		break;

	case 2:
		debug(" AF_INET %u.%u.%u.%u:%u",
		      ((uint8_t *)addr)[4],
		      ((uint8_t *)addr)[5],
		      ((uint8_t *)addr)[6],
		      ((uint8_t *)addr)[7],
		      ((uint8_t *)addr)[2] << 8 | ((uint8_t *)addr)[3]);
		break;

	default:
		debug(" family 0x%x", addr->sa_family);
		break;
	}

	return sys_connect(sockfd, addr, addrlen);
}

uint32_t translate_sys_getpeername(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];
	sockaddr_s *addr = args[1] ? sys->mem_base + args[1] : NULL;
	int *addrlen = args[2] ? sys->mem_base + args[2] : NULL;

	return sys_getpeername(fd, addr, addrlen);
}

uint32_t translate_sys_getsockname(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];
	sockaddr_s *addr = args[1] ? sys->mem_base + args[1] : NULL;
	int *addrlen = args[2] ? sys->mem_base + args[2] : NULL;

	return sys_getsockname(fd, addr, addrlen);
}

uint32_t translate_sys_getsockopt(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];
	int level_b, level_f = args[1];
	int optname_b, optname_f = args[2];
	void *optval = args[3] ? sys->mem_base + args[3] : NULL;
	int *optlen = args[4] ? sys->mem_base + args[4] : NULL;

	switch (level_f) {
	case 0xffff:
		switch (optname_f) {
		case 0x1007:
			optname_b = 4;
			break;

		default:
			return -FRONT_EINVAL;
		}

		level_b = 1;
		break;

	default:
		return -FRONT_EINVAL;
	}

	return sys_getsockopt(fd, level_b, optname_b, optval, optlen);
}

uint32_t translate_sys_recv(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];
	void *buf = sys->mem_base + args[1];
	size_t len = args[2];
	int flags = args[3];

	return sys_recvfrom(fd, buf, len, flags, NULL, 0);
}

uint32_t translate_sys_recvfrom(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];
	void *buf = sys->mem_base + args[1];
	size_t len = args[2];
	int flags = args[3];
	sockaddr_s *addr = args[4] ? sys->mem_base + args[4] : NULL;
	int *addrlen = args[5] ? sys->mem_base + args[5] : NULL;

	return sys_recvfrom(fd, buf, len, flags, addr, addrlen);
}

uint32_t translate_sys_send(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];
	const void *buf = args[1] ? sys->mem_base + args[1] : NULL;
	size_t len = args[2];
	int flags = args[3];

	return sys_sendto(fd, buf, len, flags, NULL, 0);
}

static unsigned int count_iovecs(front_mmsghdr_s *msgvec, unsigned int vlen)
{
	unsigned int i, count = 0;

	for (i = 0; i < vlen; i++)
		count += msgvec[i].msg_hdr.msg_iovlen;

	return count;
}

static unsigned int count_ctl_bytes(const struct sys_state *sys,
				    front_mmsghdr_s *msgvec, unsigned int vlen)
{
	unsigned int i, j, count = 0;
	front_cmsghdr_s *ctl;

	for (i = 0; i < vlen; i++) {
		ctl = sys->mem_base + msgvec[i].msg_hdr.msg_control;
		for (j = 0; j < msgvec[i].msg_hdr.msg_controllen; j++)
			count += ctl[j].cmsg_len;
	}

	return count;
}

uint32_t translate_sys_sendmmsg(const struct sys_state *sys, uint32_t *args)
{
	int ret, sockfd = args[0];
	front_mmsghdr_s *msgvec_f = sys->mem_base + args[1];
	unsigned int vlen = args[2];
	unsigned int flags = args[3];
	unsigned int i, j, iov_idx = 0, ctl_idx = 0;
	unsigned int iov_count = count_iovecs(msgvec_f, vlen);
	unsigned int ctl_bytes = count_ctl_bytes(sys, msgvec_f, vlen);
	mmsghdr_s msgvec_b[vlen];
	uint8_t ctl_buf[ctl_bytes], *ctl_f_ptr;
	iovec_s iov_b[iov_count];
	front_iovec_s *iov_f;
	front_cmsghdr_s *ctl_f;
	cmsghdr_s *ctl_b;

	for (i = 0; i < vlen; i++) {
		msgvec_b[i].msg_hdr.msg_name = (uintptr_t)sys->mem_base + msgvec_f[i].msg_hdr.msg_name;
		msgvec_b[i].msg_hdr.msg_namelen = msgvec_f[i].msg_hdr.msg_namelen;
		msgvec_b[i].msg_hdr.msg_iov = (uintptr_t)&iov_b[iov_idx];
		msgvec_b[i].msg_hdr.msg_iovlen = msgvec_f[i].msg_hdr.msg_iovlen;
		msgvec_b[i].msg_hdr.msg_control = (uintptr_t)&ctl_buf[ctl_idx];
		msgvec_b[i].msg_hdr.msg_controllen = msgvec_f[i].msg_hdr.msg_controllen;;
		msgvec_b[i].msg_hdr.msg_flags = msgvec_f[i].msg_hdr.msg_flags;
		msgvec_b[i].msg_len = msgvec_f[i].msg_len;

		iov_f = sys->mem_base + msgvec_f[i].msg_hdr.msg_iov;
		for (j = 0; j < msgvec_f[i].msg_hdr.msg_iovlen; j++) {
			iov_b[iov_idx].iov_base = (uintptr_t)sys->mem_base + iov_f[j].iov_base;
			iov_b[iov_idx].iov_len = iov_f[j].iov_len;
			iov_idx++;
		}

		ctl_f_ptr = sys->mem_base + msgvec_f[i].msg_hdr.msg_control;
		for (j = 0; j < msgvec_f[i].msg_hdr.msg_controllen; j++) {
			ctl_f = (front_cmsghdr_s *)ctl_f_ptr;
			ctl_b = (cmsghdr_s *)&ctl_buf[ctl_idx];

			ctl_b->cmsg_len = ctl_f[j].cmsg_len + sizeof(*ctl_b) - sizeof(*ctl_f);
			ctl_b->cmsg_level = ctl_f[j].cmsg_level;
			ctl_b->cmsg_type = ctl_f[j].cmsg_type;

			memcpy(&ctl_buf[ctl_idx + sizeof(*ctl_b)],
			       &ctl_f[1], ctl_f[j].cmsg_len - sizeof(*ctl_f));

			ctl_idx += ctl_b->cmsg_len;
			ctl_f_ptr += ctl_f->cmsg_len;
		}
	}

	ret = sys_sendmmsg(sockfd, msgvec_b, vlen, flags);

	for (i = 0; i < vlen; i++)
		msgvec_f[i].msg_len = msgvec_b[i].msg_len;

	return ret;
}

uint32_t translate_sys_socket(const struct sys_state *sys, uint32_t *args)
{
	int domain = args[0];
	int type_ok, type_b, type_f = args[1];
	int protocol = args[2];

	type_b = f2b_open_flags(type_f & ~0xf, &type_ok);
	if (!type_ok) {
		debug("Unrecognised socket flags 0x%x\n", type_f);
		return -FRONT_EINVAL;
	}

	switch (type_f & 0xf) {
	case 1:
		type_b |= 2;
		break;

	case 2:
		type_b |= 1;
		break;

	default:
		debug("Unrecognised socket type 0x%x\n", type_f);
		return -FRONT_EINVAL;
	}

	return sys_socket(domain, type_b, protocol);
}
