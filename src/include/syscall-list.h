#ifndef SYSCALL
# error Define SYSCALL before inclusion
#endif

SYSCALL(_llseek, int, int fd, unsigned long offset_high, unsigned long offset_low, loff_t *result, unsigned int whence)
SYSCALL(access, int, const char *pathname, int mode)
SYSCALL(brk, int, void *addr)
SYSCALL(close, int, int fd)
SYSCALL(execve, int, const char *filename, char *const argv[], char *const envp[])
SYSCALL(exit, void, int status)
SYSCALL(exit_group, void, int status)
SYSCALL(fork, pid_t)
SYSCALL(fcntl, long, int fd, unsigned int cmd, unsigned long arg)
SYSCALL(fcntl64, long, int fd, unsigned int cmd, unsigned long arg)
SYSCALL(fstat, int, int fd, stat_s *buf)
SYSCALL(fstat64, int, int fd, stat64_s *buf)
SYSCALL(futex, int, int *uaddr, int op, int val, const timespec_s *timeout, int *uaddr2, int val3)
SYSCALL(getcwd, long, char *buf, size_t size)
SYSCALL(getdents, int, int fd, linux_dirent_s *dirent, unsigned int count)
SYSCALL(getdents64, int, int fd, linux_dirent64_s *dirent, unsigned int count)
SYSCALL(getegid, gid_t)
SYSCALL(geteuid, uid_t)
SYSCALL(getgid, gid_t)
SYSCALL(getuid, uid_t)
SYSCALL(getpgid, pid_t, pid_t pid)
SYSCALL(getpgrp, pid_t)
SYSCALL(getpid, pid_t)
SYSCALL(getppid, pid_t)
SYSCALL(getxattr, ssize_t, const char *path, const char *name, void *value, size_t size)
SYSCALL(ioctl, int, int fd, unsigned int cmd, unsigned long arg)
SYSCALL(lseek, off_t, int fd, off_t offset, int whence)
SYSCALL(lstat, int, const char *pathname, stat_s *buf)
SYSCALL(lstat64, int, const char *pathname, stat64_s *buf)
SYSCALL(mkdir, int, const char *pathname, mode_t mode)
SYSCALL(mkdirat, int, int dirfd, const char *pathname, mode_t mode)
SYSCALL(mmap, void *, void *addr, size_t length, int prot, int flags, int fd, off_t offset)
SYSCALL(mmap2, void *, void *addr, size_t length, int prot, int flags, int fd, off_t pgoffset)
SYSCALL(mprotect, int, void *addr, size_t len, int prot)
SYSCALL(munmap, int, void *addr, size_t length)
SYSCALL(open, int, const char *pathname, int flags, mode_t mode)
SYSCALL(openat, int, int dirfd, const char *pathname, int flags, mode_t mode)
SYSCALL(read, ssize_t, int fd, void *buf, size_t count)
SYSCALL(readlink, size_t, const char *pathname, char *buf, size_t bufsiz)
SYSCALL(rt_sigaction, int, int signum, const sigaction_s *act, sigaction_s *oldact, size_t sigsetsize)
SYSCALL(setpgid, int, pid_t pid, pid_t pgid)
SYSCALL(socket, int, int domain, int type, int protocol)
SYSCALL(stat, int, const char *filename, stat_s *buf)
SYSCALL(stat64, int, const char *filename, stat64_s *buf)
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
