#ifndef SYSCALL
# error Define SYSCALL before inclusion
#endif

SYSCALL(brk, int, void *addr)
SYSCALL(close, int, int fd)
SYSCALL(exit, void, int status)
SYSCALL(exit_group, void, int status)
SYSCALL(fstat, int, int fd, stat_s *buf)
SYSCALL(fstat64, int, int fd, stat64_s *buf)
SYSCALL(getcwd, long, char *buf, size_t size)
SYSCALL(getegid, gid_t)
SYSCALL(geteuid, uid_t)
SYSCALL(getgid, gid_t)
SYSCALL(getuid, uid_t)
SYSCALL(getpgrp, pid_t)
SYSCALL(getpid, pid_t)
SYSCALL(mmap, void *, void *addr, size_t length, int prot, int flags, int fd, off_t offset)
SYSCALL(mprotect, int, void *addr, size_t len, int prot)
SYSCALL(munmap, int, void *addr, size_t length)
SYSCALL(open, int, const char *pathname, int flags, mode_t mode)
SYSCALL(read, ssize_t, int fd, void *buf, size_t count)
SYSCALL(readlink, size_t, const char *pathname, char *buf, size_t bufsiz)
SYSCALL(rt_sigaction, int, int signum, const sigaction_s *act, sigaction_s *oldact, size_t sigsetsize)
SYSCALL(stat, int, const char *filename, stat_s *buf)
SYSCALL(stat64, int, const char *filename, stat64_s *buf)
SYSCALL(uname, int, utsname_s *buf)
SYSCALL(write, ssize_t, int fd, const void *buf, size_t count)
SYSCALL(writev, ssize_t, int fd, const iovec_s *iov, int iovcnt)
