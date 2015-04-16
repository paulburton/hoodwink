#ifndef SYSCALL
# error Define SYSCALL before inclusion
#endif

SYSCALL(_llseek, int, int fd, unsigned long offset_high, unsigned long offset_low, loff_t *result, unsigned int whence)
SYSCALL(access, int, const char *pathname, int mode)
SYSCALL(brk, int, void *addr)
SYSCALL(clock_gettime, int, int clk_id, timespec_s *tp)
SYSCALL(close, int, int fd)
SYSCALL(connect, int, int sockfd, const sockaddr_s *addr, int addrlen)
SYSCALL(execve, int, const char *filename, char *const argv[], char *const envp[])
SYSCALL(exit, void, int status)
SYSCALL(exit_group, void, int status)
SYSCALL(fork, pid_t)
SYSCALL(fcntl, long, int fd, unsigned int cmd, unsigned long arg)
SYSCALL(fcntl64, long, int fd, unsigned int cmd, unsigned long arg)
SYSCALL(fdatasync, int, int fd)
SYSCALL(fstat, int, int fd, stat_s *buf)
SYSCALL(fstat64, int, int fd, stat64_s *buf)
SYSCALL(fsync, int, int fd)
SYSCALL(futex, int, int *uaddr, int op, int val, const timespec_s *timeout, int *uaddr2, int val3)
SYSCALL(getcwd, long, char *buf, size_t size)
SYSCALL(getdents, int, int fd, linux_dirent_s *dirent, unsigned int count)
SYSCALL(getdents64, int, int fd, linux_dirent64_s *dirent, unsigned int count)
SYSCALL(getegid, gid_t)
SYSCALL(geteuid, uid_t)
SYSCALL(getgid, gid_t)
SYSCALL(getuid, uid_t)
SYSCALL(getpeername, int, int fd, sockaddr_s *addr, int *addrlen)
SYSCALL(getpgid, pid_t, pid_t pid)
SYSCALL(getpgrp, pid_t)
SYSCALL(getpid, pid_t)
SYSCALL(getppid, pid_t)
SYSCALL(getsockname, int, int fd, sockaddr_s *addr, int *addrlen)
SYSCALL(getsockopt, int, int fd, int level, int optname, void *optval, int *optlen)
SYSCALL(gettimeofday, int, timeval_s *tv, timezone_s *tz)
SYSCALL(getxattr, ssize_t, const char *path, const char *name, void *value, size_t size)
SYSCALL(ioctl, int, int fd, unsigned int cmd, unsigned long arg)
SYSCALL(lseek, off_t, int fd, off_t offset, int whence)
SYSCALL(lstat, int, const char *pathname, stat_s *buf)
SYSCALL(lstat64, int, const char *pathname, stat64_s *buf)
SYSCALL(madvise, int, void *addr, size_t length, int advice)
SYSCALL(mkdir, int, const char *pathname, mode_t mode)
SYSCALL(mkdirat, int, int dirfd, const char *pathname, mode_t mode)
SYSCALL(mmap, void *, void *addr, size_t length, int prot, int flags, int fd, off_t offset)
SYSCALL(mmap2, void *, void *addr, size_t length, int prot, int flags, int fd, off_t pgoffset)
SYSCALL(mprotect, int, void *addr, size_t len, int prot)
SYSCALL(munmap, int, void *addr, size_t length)
SYSCALL(open, int, const char *pathname, int flags, mode_t mode)
SYSCALL(openat, int, int dirfd, const char *pathname, int flags, mode_t mode)
SYSCALL(poll, int, pollfd_s *fds, unsigned int nfds, int timeout_msecs)
SYSCALL(read, ssize_t, int fd, void *buf, size_t count)
SYSCALL(readlink, size_t, const char *pathname, char *buf, size_t bufsiz)
SYSCALL(recv, ssize_t, int fd, void *buf, size_t len, int flags)
SYSCALL(recvfrom, ssize_t, int fd, void *buf, size_t len, int flags, sockaddr_s *src_addr, int *addrlen)
SYSCALL(rename, int, const char *oldpath, const char *newpath)
SYSCALL(rt_sigaction, int, int signum, const sigaction_s *act, sigaction_s *oldact, size_t sigsetsize)
SYSCALL(send, ssize_t, int fd, const void *buf, size_t len, int flags)
SYSCALL(sendmmsg, int, int sockfd, mmsghdr_s *msgvec, unsigned int vlen, unsigned int flags)
SYSCALL(sendto, ssize_t, int fd, const void *buf, size_t len, int flags, sockaddr_s *dest_addr, int *addrlen)
SYSCALL(set_tid_address, long, int *tidptr)
SYSCALL(setgid, int, gid_t gid)
SYSCALL(setpgid, int, pid_t pid, pid_t pgid)
SYSCALL(socket, int, int domain, int type, int protocol)
SYSCALL(stat, int, const char *filename, stat_s *buf)
SYSCALL(stat64, int, const char *filename, stat64_s *buf)
SYSCALL(statfs, int, const char *pathname, statfs_s *buf)
SYSCALL(statfs64, int, const char *pathname, size_t sz, statfs64_s *buf)
SYSCALL(tgkill, int, int tgid, int tid, int sig)
SYSCALL(time, time_t, time_t *t)
SYSCALL(times, clock_t, tms_s *buf)
SYSCALL(umask, mode_t, mode_t mask)
SYSCALL(uname, int, utsname_s *buf)
SYSCALL(unlink, int, const char *pathname)
SYSCALL(unlinkat, int, int dirfd, const char *pathname, int flags)
SYSCALL(wait4, pid_t, pid_t pid, int *status, int options, void *rusage)
SYSCALL(waitpid, pid_t, pid_t pid, int *status, int options)
SYSCALL(write, ssize_t, int fd, const void *buf, size_t count)
SYSCALL(writev, ssize_t, int fd, const iovec_s *iov, int iovcnt)
