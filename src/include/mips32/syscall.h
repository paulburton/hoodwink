#ifndef __hoodwink_mips32_syscall_h__
#define __hoodwink_mips32_syscall_h__

#define MIPS32_NR__min				4000

#define MIPS32_NR_syscall			4000
#define MIPS32_NR_exit				4001
#define MIPS32_NR_fork			(4000 +	2)
#define MIPS32_NR_read			(4000 +	3)
#define MIPS32_NR_write			(4000 +	4)
#define MIPS32_NR_open			(4000 +	5)
#define MIPS32_NR_close			(4000 +	6)
#define MIPS32_NR_waitpid			(4000 +	7)
#define MIPS32_NR_creat			(4000 +	8)
#define MIPS32_NR_link			(4000 +	9)
#define MIPS32_NR_unlink			(4000 +  10)
#define MIPS32_NR_execve			(4000 +  11)
#define MIPS32_NR_chdir			(4000 +  12)
#define MIPS32_NR_time			(4000 +  13)
#define MIPS32_NR_mknod			(4000 +  14)
#define MIPS32_NR_chmod			(4000 +  15)
#define MIPS32_NR_lchown			(4000 +  16)
#define MIPS32_NR_break			(4000 +  17)
#define MIPS32_NR_lseek			(4000 +  19)
#define MIPS32_NR_getpid			(4000 +  20)
#define MIPS32_NR_mount			(4000 +  21)
#define MIPS32_NR_umount			(4000 +  22)
#define MIPS32_NR_setuid			(4000 +  23)
#define MIPS32_NR_getuid			(4000 +  24)
#define MIPS32_NR_stime			(4000 +  25)
#define MIPS32_NR_ptrace			(4000 +  26)
#define MIPS32_NR_alarm			(4000 +  27)
#define MIPS32_NR_pause			(4000 +  29)
#define MIPS32_NR_utime			(4000 +  30)
#define MIPS32_NR_stty			(4000 +  31)
#define MIPS32_NR_gtty			(4000 +  32)
#define MIPS32_NR_access			(4000 +  33)
#define MIPS32_NR_nice			(4000 +  34)
#define MIPS32_NR_ftime			(4000 +  35)
#define MIPS32_NR_sync			(4000 +  36)
#define MIPS32_NR_kill			(4000 +  37)
#define MIPS32_NR_rename			(4000 +  38)
#define MIPS32_NR_mkdir			(4000 +  39)
#define MIPS32_NR_rmdir			(4000 +  40)
#define MIPS32_NR_dup			(4000 +  41)
#define MIPS32_NR_pipe			(4000 +  42)
#define MIPS32_NR_times			(4000 +  43)
#define MIPS32_NR_prof			(4000 +  44)
#define MIPS32_NR_brk			(4000 +  45)
#define MIPS32_NR_setgid			(4000 +  46)
#define MIPS32_NR_getgid			(4000 +  47)
#define MIPS32_NR_signal			(4000 +  48)
#define MIPS32_NR_geteuid			(4000 +  49)
#define MIPS32_NR_getegid			(4000 +  50)
#define MIPS32_NR_acct			(4000 +  51)
#define MIPS32_NR_umount2			(4000 +  52)
#define MIPS32_NR_lock			(4000 +  53)
#define MIPS32_NR_ioctl			(4000 +  54)
#define MIPS32_NR_fcntl			(4000 +  55)
#define MIPS32_NR_mpx			(4000 +  56)
#define MIPS32_NR_setpgid			(4000 +  57)
#define MIPS32_NR_ulimit			(4000 +  58)
#define MIPS32_NR_umask			(4000 +  60)
#define MIPS32_NR_chroot			(4000 +  61)
#define MIPS32_NR_ustat			(4000 +  62)
#define MIPS32_NR_dup2			(4000 +  63)
#define MIPS32_NR_getppid			(4000 +  64)
#define MIPS32_NR_getpgrp			(4000 +  65)
#define MIPS32_NR_setsid			(4000 +  66)
#define MIPS32_NR_sigaction			(4000 +  67)
#define MIPS32_NR_sgetmask			(4000 +  68)
#define MIPS32_NR_ssetmask			(4000 +  69)
#define MIPS32_NR_setreuid			(4000 +  70)
#define MIPS32_NR_setregid			(4000 +  71)
#define MIPS32_NR_sigsuspend			(4000 +  72)
#define MIPS32_NR_sigpending			(4000 +  73)
#define MIPS32_NR_sethostname		(4000 +  74)
#define MIPS32_NR_setrlimit			(4000 +  75)
#define MIPS32_NR_getrlimit			(4000 +  76)
#define MIPS32_NR_getrusage			(4000 +  77)
#define MIPS32_NR_gettimeofday		(4000 +  78)
#define MIPS32_NR_settimeofday		(4000 +  79)
#define MIPS32_NR_getgroups			(4000 +  80)
#define MIPS32_NR_setgroups			(4000 +  81)
#define MIPS32_NR_symlink			(4000 +  83)
#define MIPS32_NR_readlink			(4000 +  85)
#define MIPS32_NR_uselib			(4000 +  86)
#define MIPS32_NR_swapon			(4000 +  87)
#define MIPS32_NR_reboot			(4000 +  88)
#define MIPS32_NR_readdir			(4000 +  89)
#define MIPS32_NR_mmap			(4000 +  90)
#define MIPS32_NR_munmap			(4000 +  91)
#define MIPS32_NR_truncate			(4000 +  92)
#define MIPS32_NR_ftruncate			(4000 +  93)
#define MIPS32_NR_fchmod			(4000 +  94)
#define MIPS32_NR_fchown			(4000 +  95)
#define MIPS32_NR_getpriority		(4000 +  96)
#define MIPS32_NR_setpriority		(4000 +  97)
#define MIPS32_NR_profil			(4000 +  98)
#define MIPS32_NR_statfs			(4000 +  99)
#define MIPS32_NR_fstatfs			(4000 + 100)
#define MIPS32_NR_ioperm			(4000 + 101)
#define MIPS32_NR_socketcall			(4000 + 102)
#define MIPS32_NR_syslog			(4000 + 103)
#define MIPS32_NR_setitimer			(4000 + 104)
#define MIPS32_NR_getitimer			(4000 + 105)
#define MIPS32_NR_stat			(4000 + 106)
#define MIPS32_NR_lstat			(4000 + 107)
#define MIPS32_NR_fstat			(4000 + 108)
#define MIPS32_NR_iopl			(4000 + 110)
#define MIPS32_NR_vhangup			(4000 + 111)
#define MIPS32_NR_idle			(4000 + 112)
#define MIPS32_NR_vm86			(4000 + 113)
#define MIPS32_NR_wait4			(4000 + 114)
#define MIPS32_NR_swapoff			(4000 + 115)
#define MIPS32_NR_sysinfo			(4000 + 116)
#define MIPS32_NR_ipc			(4000 + 117)
#define MIPS32_NR_fsync			(4000 + 118)
#define MIPS32_NR_sigreturn			(4000 + 119)
#define MIPS32_NR_clone			(4000 + 120)
#define MIPS32_NR_setdomainname		(4000 + 121)
#define MIPS32_NR_uname			(4000 + 122)
#define MIPS32_NR_modify_ldt			(4000 + 123)
#define MIPS32_NR_adjtimex			(4000 + 124)
#define MIPS32_NR_mprotect			(4000 + 125)
#define MIPS32_NR_sigprocmask		(4000 + 126)
#define MIPS32_NR_create_module		(4000 + 127)
#define MIPS32_NR_init_module		(4000 + 128)
#define MIPS32_NR_delete_module		(4000 + 129)
#define MIPS32_NR_get_kernel_syms		(4000 + 130)
#define MIPS32_NR_quotactl			(4000 + 131)
#define MIPS32_NR_getpgid			(4000 + 132)
#define MIPS32_NR_fchdir			(4000 + 133)
#define MIPS32_NR_bdflush			(4000 + 134)
#define MIPS32_NR_sysfs			(4000 + 135)
#define MIPS32_NR_personality		(4000 + 136)
#define MIPS32_NR_afs_syscall		(4000 + 137)
#define MIPS32_NR_setfsuid			(4000 + 138)
#define MIPS32_NR_setfsgid			(4000 + 139)
#define MIPS32_NR__llseek			(4000 + 140)
#define MIPS32_NR_getdents			(4000 + 141)
#define MIPS32_NR__newselect			(4000 + 142)
#define MIPS32_NR_flock			(4000 + 143)
#define MIPS32_NR_msync			(4000 + 144)
#define MIPS32_NR_readv			(4000 + 145)
#define MIPS32_NR_writev			(4000 + 146)
#define MIPS32_NR_cacheflush			(4000 + 147)
#define MIPS32_NR_cachectl			(4000 + 148)
#define MIPS32_NR_sysmips			(4000 + 149)
#define MIPS32_NR_getsid			(4000 + 151)
#define MIPS32_NR_fdatasync			(4000 + 152)
#define MIPS32_NR__sysctl			(4000 + 153)
#define MIPS32_NR_mlock			(4000 + 154)
#define MIPS32_NR_munlock			(4000 + 155)
#define MIPS32_NR_mlockall			(4000 + 156)
#define MIPS32_NR_munlockall			(4000 + 157)
#define MIPS32_NR_sched_setparam		(4000 + 158)
#define MIPS32_NR_sched_getparam		(4000 + 159)
#define MIPS32_NR_sched_setscheduler		(4000 + 160)
#define MIPS32_NR_sched_getscheduler		(4000 + 161)
#define MIPS32_NR_sched_yield		(4000 + 162)
#define MIPS32_NR_sched_get_priority_max	(4000 + 163)
#define MIPS32_NR_sched_get_priority_min	(4000 + 164)
#define MIPS32_NR_sched_rr_get_interval	(4000 + 165)
#define MIPS32_NR_nanosleep			(4000 + 166)
#define MIPS32_NR_mremap			(4000 + 167)
#define MIPS32_NR_accept			(4000 + 168)
#define MIPS32_NR_bind			(4000 + 169)
#define MIPS32_NR_connect			(4000 + 170)
#define MIPS32_NR_getpeername		(4000 + 171)
#define MIPS32_NR_getsockname		(4000 + 172)
#define MIPS32_NR_getsockopt			(4000 + 173)
#define MIPS32_NR_listen			(4000 + 174)
#define MIPS32_NR_recv			(4000 + 175)
#define MIPS32_NR_recvfrom			(4000 + 176)
#define MIPS32_NR_recvmsg			(4000 + 177)
#define MIPS32_NR_send			(4000 + 178)
#define MIPS32_NR_sendmsg			(4000 + 179)
#define MIPS32_NR_sendto			(4000 + 180)
#define MIPS32_NR_setsockopt			(4000 + 181)
#define MIPS32_NR_shutdown			(4000 + 182)
#define MIPS32_NR_socket			(4000 + 183)
#define MIPS32_NR_socketpair			(4000 + 184)
#define MIPS32_NR_setresuid			(4000 + 185)
#define MIPS32_NR_getresuid			(4000 + 186)
#define MIPS32_NR_query_module		(4000 + 187)
#define MIPS32_NR_poll			(4000 + 188)
#define MIPS32_NR_nfsservctl			(4000 + 189)
#define MIPS32_NR_setresgid			(4000 + 190)
#define MIPS32_NR_getresgid			(4000 + 191)
#define MIPS32_NR_prctl			(4000 + 192)
#define MIPS32_NR_rt_sigreturn		(4000 + 193)
#define MIPS32_NR_rt_sigaction		(4000 + 194)
#define MIPS32_NR_rt_sigprocmask		(4000 + 195)
#define MIPS32_NR_rt_sigpending		(4000 + 196)
#define MIPS32_NR_rt_sigtimedwait		(4000 + 197)
#define MIPS32_NR_rt_sigqueueinfo		(4000 + 198)
#define MIPS32_NR_rt_sigsuspend		(4000 + 199)
#define MIPS32_NR_pread64			(4000 + 200)
#define MIPS32_NR_pwrite64			(4000 + 201)
#define MIPS32_NR_chown			(4000 + 202)
#define MIPS32_NR_getcwd			(4000 + 203)
#define MIPS32_NR_capget			(4000 + 204)
#define MIPS32_NR_capset			(4000 + 205)
#define MIPS32_NR_sigaltstack		(4000 + 206)
#define MIPS32_NR_sendfile			(4000 + 207)
#define MIPS32_NR_getpmsg			(4000 + 208)
#define MIPS32_NR_putpmsg			(4000 + 209)
#define MIPS32_NR_mmap2			(4000 + 210)
#define MIPS32_NR_truncate64			(4000 + 211)
#define MIPS32_NR_ftruncate64		(4000 + 212)
#define MIPS32_NR_stat64			(4000 + 213)
#define MIPS32_NR_lstat64			(4000 + 214)
#define MIPS32_NR_fstat64			(4000 + 215)
#define MIPS32_NR_pivot_root			(4000 + 216)
#define MIPS32_NR_mincore			(4000 + 217)
#define MIPS32_NR_madvise			(4000 + 218)
#define MIPS32_NR_getdents64			(4000 + 219)
#define MIPS32_NR_fcntl64			(4000 + 220)
#define MIPS32_NR_gettid			(4000 + 222)
#define MIPS32_NR_readahead			(4000 + 223)
#define MIPS32_NR_setxattr			(4000 + 224)
#define MIPS32_NR_lsetxattr			(4000 + 225)
#define MIPS32_NR_fsetxattr			(4000 + 226)
#define MIPS32_NR_getxattr			(4000 + 227)
#define MIPS32_NR_lgetxattr			(4000 + 228)
#define MIPS32_NR_fgetxattr			(4000 + 229)
#define MIPS32_NR_listxattr			(4000 + 230)
#define MIPS32_NR_llistxattr			(4000 + 231)
#define MIPS32_NR_flistxattr			(4000 + 232)
#define MIPS32_NR_removexattr		(4000 + 233)
#define MIPS32_NR_lremovexattr		(4000 + 234)
#define MIPS32_NR_fremovexattr		(4000 + 235)
#define MIPS32_NR_tkill			(4000 + 236)
#define MIPS32_NR_sendfile64			(4000 + 237)
#define MIPS32_NR_futex			(4000 + 238)
#define MIPS32_NR_sched_setaffinity		(4000 + 239)
#define MIPS32_NR_sched_getaffinity		(4000 + 240)
#define MIPS32_NR_io_setup			(4000 + 241)
#define MIPS32_NR_io_destroy			(4000 + 242)
#define MIPS32_NR_io_getevents		(4000 + 243)
#define MIPS32_NR_io_submit			(4000 + 244)
#define MIPS32_NR_io_cancel			(4000 + 245)
#define MIPS32_NR_exit_group			(4000 + 246)
#define MIPS32_NR_lookup_dcookie		(4000 + 247)
#define MIPS32_NR_epoll_create		(4000 + 248)
#define MIPS32_NR_epoll_ctl			(4000 + 249)
#define MIPS32_NR_epoll_wait			(4000 + 250)
#define MIPS32_NR_remap_file_pages		(4000 + 251)
#define MIPS32_NR_set_tid_address		(4000 + 252)
#define MIPS32_NR_restart_syscall		(4000 + 253)
#define MIPS32_NR_fadvise64			(4000 + 254)
#define MIPS32_NR_statfs64			(4000 + 255)
#define MIPS32_NR_fstatfs64			(4000 + 256)
#define MIPS32_NR_timer_create		(4000 + 257)
#define MIPS32_NR_timer_settime		(4000 + 258)
#define MIPS32_NR_timer_gettime		(4000 + 259)
#define MIPS32_NR_timer_getoverrun		(4000 + 260)
#define MIPS32_NR_timer_delete		(4000 + 261)
#define MIPS32_NR_clock_settime		(4000 + 262)
#define MIPS32_NR_clock_gettime		(4000 + 263)
#define MIPS32_NR_clock_getres		(4000 + 264)
#define MIPS32_NR_clock_nanosleep		(4000 + 265)
#define MIPS32_NR_tgkill			(4000 + 266)
#define MIPS32_NR_utimes			(4000 + 267)
#define MIPS32_NR_mbind			(4000 + 268)
#define MIPS32_NR_get_mempolicy		(4000 + 269)
#define MIPS32_NR_set_mempolicy		(4000 + 270)
#define MIPS32_NR_mq_open			(4000 + 271)
#define MIPS32_NR_mq_unlink			(4000 + 272)
#define MIPS32_NR_mq_timedsend		(4000 + 273)
#define MIPS32_NR_mq_timedreceive		(4000 + 274)
#define MIPS32_NR_mq_notify			(4000 + 275)
#define MIPS32_NR_mq_getsetattr		(4000 + 276)
#define MIPS32_NR_vserver			(4000 + 277)
#define MIPS32_NR_waitid			(4000 + 278)
#define MIPS32_NR_add_key			(4000 + 280)
#define MIPS32_NR_request_key		(4000 + 281)
#define MIPS32_NR_keyctl			(4000 + 282)
#define MIPS32_NR_set_thread_area		(4000 + 283)
#define MIPS32_NR_inotify_init		(4000 + 284)
#define MIPS32_NR_inotify_add_watch		(4000 + 285)
#define MIPS32_NR_inotify_rm_watch		(4000 + 286)
#define MIPS32_NR_migrate_pages		(4000 + 287)
#define MIPS32_NR_openat			(4000 + 288)
#define MIPS32_NR_mkdirat			(4000 + 289)
#define MIPS32_NR_mknodat			(4000 + 290)
#define MIPS32_NR_fchownat			(4000 + 291)
#define MIPS32_NR_futimesat			(4000 + 292)
#define MIPS32_NR_fstatat64			(4000 + 293)
#define MIPS32_NR_unlinkat			(4000 + 294)
#define MIPS32_NR_renameat			(4000 + 295)
#define MIPS32_NR_linkat			(4000 + 296)
#define MIPS32_NR_symlinkat			(4000 + 297)
#define MIPS32_NR_readlinkat			(4000 + 298)
#define MIPS32_NR_fchmodat			(4000 + 299)
#define MIPS32_NR_faccessat			(4000 + 300)
#define MIPS32_NR_pselect6			(4000 + 301)
#define MIPS32_NR_ppoll			(4000 + 302)
#define MIPS32_NR_unshare			(4000 + 303)
#define MIPS32_NR_splice			(4000 + 304)
#define MIPS32_NR_sync_file_range		(4000 + 305)
#define MIPS32_NR_tee			(4000 + 306)
#define MIPS32_NR_vmsplice			(4000 + 307)
#define MIPS32_NR_move_pages			(4000 + 308)
#define MIPS32_NR_set_robust_list		(4000 + 309)
#define MIPS32_NR_get_robust_list		(4000 + 310)
#define MIPS32_NR_kexec_load			(4000 + 311)
#define MIPS32_NR_getcpu			(4000 + 312)
#define MIPS32_NR_epoll_pwait		(4000 + 313)
#define MIPS32_NR_ioprio_set			(4000 + 314)
#define MIPS32_NR_ioprio_get			(4000 + 315)
#define MIPS32_NR_utimensat			(4000 + 316)
#define MIPS32_NR_signalfd			(4000 + 317)
#define MIPS32_NR_timerfd			(4000 + 318)
#define MIPS32_NR_eventfd			(4000 + 319)
#define MIPS32_NR_fallocate			(4000 + 320)
#define MIPS32_NR_timerfd_create		(4000 + 321)
#define MIPS32_NR_timerfd_gettime		(4000 + 322)
#define MIPS32_NR_timerfd_settime		(4000 + 323)
#define MIPS32_NR_signalfd4			(4000 + 324)
#define MIPS32_NR_eventfd2			(4000 + 325)
#define MIPS32_NR_epoll_create1		(4000 + 326)
#define MIPS32_NR_dup3			(4000 + 327)
#define MIPS32_NR_pipe2			(4000 + 328)
#define MIPS32_NR_inotify_init1		(4000 + 329)
#define MIPS32_NR_preadv			(4000 + 330)
#define MIPS32_NR_pwritev			(4000 + 331)
#define MIPS32_NR_rt_tgsigqueueinfo		(4000 + 332)
#define MIPS32_NR_perf_event_open		(4000 + 333)
#define MIPS32_NR_accept4			(4000 + 334)
#define MIPS32_NR_recvmmsg			(4000 + 335)
#define MIPS32_NR_fanotify_init		(4000 + 336)
#define MIPS32_NR_fanotify_mark		(4000 + 337)
#define MIPS32_NR_prlimit64			(4000 + 338)
#define MIPS32_NR_name_to_handle_at		(4000 + 339)
#define MIPS32_NR_open_by_handle_at		(4000 + 340)
#define MIPS32_NR_clock_adjtime		(4000 + 341)
#define MIPS32_NR_syncfs			(4000 + 342)
#define MIPS32_NR_sendmmsg			(4000 + 343)
#define MIPS32_NR_setns			(4000 + 344)
#define MIPS32_NR_process_vm_readv		(4000 + 345)
#define MIPS32_NR_process_vm_writev		(4000 + 346)
#define MIPS32_NR_kcmp			(4000 + 347)
#define MIPS32_NR_finit_module		(4000 + 348)
#define MIPS32_NR_sched_setattr		(4000 + 349)
#define MIPS32_NR_sched_getattr		(4000 + 350)
#define MIPS32_NR_renameat2			(4000 + 351)
#define MIPS32_NR_seccomp			(4000 + 352)
#define MIPS32_NR_getrandom			(4000 + 353)
#define MIPS32_NR_memfd_create		(4000 + 354)
#define MIPS32_NR_bpf			(4000 + 355)
#define MIPS32_NR_execveat			(4000 + 356)

#endif /* __hoodwink_mips32_syscall_h__ */
