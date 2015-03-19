#ifndef __hoodwink_x86_64_syscall_h__
#define __hoodwink_x86_64_syscall_h__

#define X86_64_NR__min	0

#define X86_64_NR_read 0
#define X86_64_NR_write 1
#define X86_64_NR_open 2
#define X86_64_NR_close 3
#define X86_64_NR_stat 4
#define X86_64_NR_fstat 5
#define X86_64_NR_lstat 6
#define X86_64_NR_poll 7
#define X86_64_NR_lseek 8
#define X86_64_NR_mmap 9
#define X86_64_NR_mprotect 10
#define X86_64_NR_munmap 11
#define X86_64_NR_brk 12
#define X86_64_NR_rt_sigaction 13
#define X86_64_NR_rt_sigprocmask 14
#define X86_64_NR_rt_sigreturn 15
#define X86_64_NR_ioctl 16
#define X86_64_NR_pread64 17
#define X86_64_NR_pwrite64 18
#define X86_64_NR_readv 19
#define X86_64_NR_writev 20
#define X86_64_NR_access 21
#define X86_64_NR_pipe 22
#define X86_64_NR_select 23
#define X86_64_NR_sched_yield 24
#define X86_64_NR_mremap 25
#define X86_64_NR_msync 26
#define X86_64_NR_mincore 27
#define X86_64_NR_madvise 28
#define X86_64_NR_shmget 29
#define X86_64_NR_shmat 30
#define X86_64_NR_shmctl 31
#define X86_64_NR_dup 32
#define X86_64_NR_dup2 33
#define X86_64_NR_pause 34
#define X86_64_NR_nanosleep 35
#define X86_64_NR_getitimer 36
#define X86_64_NR_alarm 37
#define X86_64_NR_setitimer 38
#define X86_64_NR_getpid 39
#define X86_64_NR_sendfile 40
#define X86_64_NR_socket 41
#define X86_64_NR_connect 42
#define X86_64_NR_accept 43
#define X86_64_NR_sendto 44
#define X86_64_NR_recvfrom 45
#define X86_64_NR_sendmsg 46
#define X86_64_NR_recvmsg 47
#define X86_64_NR_shutdown 48
#define X86_64_NR_bind 49
#define X86_64_NR_listen 50
#define X86_64_NR_getsockname 51
#define X86_64_NR_getpeername 52
#define X86_64_NR_socketpair 53
#define X86_64_NR_setsockopt 54
#define X86_64_NR_getsockopt 55
#define X86_64_NR_clone 56
#define X86_64_NR_fork 57
#define X86_64_NR_vfork 58
#define X86_64_NR_execve 59
#define X86_64_NR_exit 60
#define X86_64_NR_wait4 61
#define X86_64_NR_kill 62
#define X86_64_NR_uname 63
#define X86_64_NR_semget 64
#define X86_64_NR_semop 65
#define X86_64_NR_semctl 66
#define X86_64_NR_shmdt 67
#define X86_64_NR_msgget 68
#define X86_64_NR_msgsnd 69
#define X86_64_NR_msgrcv 70
#define X86_64_NR_msgctl 71
#define X86_64_NR_fcntl 72
#define X86_64_NR_flock 73
#define X86_64_NR_fsync 74
#define X86_64_NR_fdatasync 75
#define X86_64_NR_truncate 76
#define X86_64_NR_ftruncate 77
#define X86_64_NR_getdents 78
#define X86_64_NR_getcwd 79
#define X86_64_NR_chdir 80
#define X86_64_NR_fchdir 81
#define X86_64_NR_rename 82
#define X86_64_NR_mkdir 83
#define X86_64_NR_rmdir 84
#define X86_64_NR_creat 85
#define X86_64_NR_link 86
#define X86_64_NR_unlink 87
#define X86_64_NR_symlink 88
#define X86_64_NR_readlink 89
#define X86_64_NR_chmod 90
#define X86_64_NR_fchmod 91
#define X86_64_NR_chown 92
#define X86_64_NR_fchown 93
#define X86_64_NR_lchown 94
#define X86_64_NR_umask 95
#define X86_64_NR_gettimeofday 96
#define X86_64_NR_getrlimit 97
#define X86_64_NR_getrusage 98
#define X86_64_NR_sysinfo 99
#define X86_64_NR_times 100
#define X86_64_NR_ptrace 101
#define X86_64_NR_getuid 102
#define X86_64_NR_syslog 103
#define X86_64_NR_getgid 104
#define X86_64_NR_setuid 105
#define X86_64_NR_setgid 106
#define X86_64_NR_geteuid 107
#define X86_64_NR_getegid 108
#define X86_64_NR_setpgid 109
#define X86_64_NR_getppid 110
#define X86_64_NR_getpgrp 111
#define X86_64_NR_setsid 112
#define X86_64_NR_setreuid 113
#define X86_64_NR_setregid 114
#define X86_64_NR_getgroups 115
#define X86_64_NR_setgroups 116
#define X86_64_NR_setresuid 117
#define X86_64_NR_getresuid 118
#define X86_64_NR_setresgid 119
#define X86_64_NR_getresgid 120
#define X86_64_NR_getpgid 121
#define X86_64_NR_setfsuid 122
#define X86_64_NR_setfsgid 123
#define X86_64_NR_getsid 124
#define X86_64_NR_capget 125
#define X86_64_NR_capset 126
#define X86_64_NR_rt_sigpending 127
#define X86_64_NR_rt_sigtimedwait 128
#define X86_64_NR_rt_sigqueueinfo 129
#define X86_64_NR_rt_sigsuspend 130
#define X86_64_NR_sigaltstack 131
#define X86_64_NR_utime 132
#define X86_64_NR_mknod 133
#define X86_64_NR_uselib 134
#define X86_64_NR_personality 135
#define X86_64_NR_ustat 136
#define X86_64_NR_statfs 137
#define X86_64_NR_fstatfs 138
#define X86_64_NR_sysfs 139
#define X86_64_NR_getpriority 140
#define X86_64_NR_setpriority 141
#define X86_64_NR_sched_setparam 142
#define X86_64_NR_sched_getparam 143
#define X86_64_NR_sched_setscheduler 144
#define X86_64_NR_sched_getscheduler 145
#define X86_64_NR_sched_get_priority_max 146
#define X86_64_NR_sched_get_priority_min 147
#define X86_64_NR_sched_rr_get_interval 148
#define X86_64_NR_mlock 149
#define X86_64_NR_munlock 150
#define X86_64_NR_mlockall 151
#define X86_64_NR_munlockall 152
#define X86_64_NR_vhangup 153
#define X86_64_NR_modify_ldt 154
#define X86_64_NR_pivot_root 155
#define X86_64_NR__sysctl 156
#define X86_64_NR_prctl 157
#define X86_64_NR_arch_prctl 158
#define X86_64_NR_adjtimex 159
#define X86_64_NR_setrlimit 160
#define X86_64_NR_chroot 161
#define X86_64_NR_sync 162
#define X86_64_NR_acct 163
#define X86_64_NR_settimeofday 164
#define X86_64_NR_mount 165
#define X86_64_NR_umount2 166
#define X86_64_NR_swapon 167
#define X86_64_NR_swapoff 168
#define X86_64_NR_reboot 169
#define X86_64_NR_sethostname 170
#define X86_64_NR_setdomainname 171
#define X86_64_NR_iopl 172
#define X86_64_NR_ioperm 173
#define X86_64_NR_create_module 174
#define X86_64_NR_init_module 175
#define X86_64_NR_delete_module 176
#define X86_64_NR_get_kernel_syms 177
#define X86_64_NR_query_module 178
#define X86_64_NR_quotactl 179
#define X86_64_NR_nfsservctl 180
#define X86_64_NR_getpmsg 181
#define X86_64_NR_putpmsg 182
#define X86_64_NR_afs_syscall 183
#define X86_64_NR_tuxcall 184
#define X86_64_NR_security 185
#define X86_64_NR_gettid 186
#define X86_64_NR_readahead 187
#define X86_64_NR_setxattr 188
#define X86_64_NR_lsetxattr 189
#define X86_64_NR_fsetxattr 190
#define X86_64_NR_getxattr 191
#define X86_64_NR_lgetxattr 192
#define X86_64_NR_fgetxattr 193
#define X86_64_NR_listxattr 194
#define X86_64_NR_llistxattr 195
#define X86_64_NR_flistxattr 196
#define X86_64_NR_removexattr 197
#define X86_64_NR_lremovexattr 198
#define X86_64_NR_fremovexattr 199
#define X86_64_NR_tkill 200
#define X86_64_NR_time 201
#define X86_64_NR_futex 202
#define X86_64_NR_sched_setaffinity 203
#define X86_64_NR_sched_getaffinity 204
#define X86_64_NR_set_thread_area 205
#define X86_64_NR_io_setup 206
#define X86_64_NR_io_destroy 207
#define X86_64_NR_io_getevents 208
#define X86_64_NR_io_submit 209
#define X86_64_NR_io_cancel 210
#define X86_64_NR_get_thread_area 211
#define X86_64_NR_lookup_dcookie 212
#define X86_64_NR_epoll_create 213
#define X86_64_NR_epoll_ctl_old 214
#define X86_64_NR_epoll_wait_old 215
#define X86_64_NR_remap_file_pages 216
#define X86_64_NR_getdents64 217
#define X86_64_NR_set_tid_address 218
#define X86_64_NR_restart_syscall 219
#define X86_64_NR_semtimedop 220
#define X86_64_NR_fadvise64 221
#define X86_64_NR_timer_create 222
#define X86_64_NR_timer_settime 223
#define X86_64_NR_timer_gettime 224
#define X86_64_NR_timer_getoverrun 225
#define X86_64_NR_timer_delete 226
#define X86_64_NR_clock_settime 227
#define X86_64_NR_clock_gettime 228
#define X86_64_NR_clock_getres 229
#define X86_64_NR_clock_nanosleep 230
#define X86_64_NR_exit_group 231
#define X86_64_NR_epoll_wait 232
#define X86_64_NR_epoll_ctl 233
#define X86_64_NR_tgkill 234
#define X86_64_NR_utimes 235
#define X86_64_NR_vserver 236
#define X86_64_NR_mbind 237
#define X86_64_NR_set_mempolicy 238
#define X86_64_NR_get_mempolicy 239
#define X86_64_NR_mq_open 240
#define X86_64_NR_mq_unlink 241
#define X86_64_NR_mq_timedsend 242
#define X86_64_NR_mq_timedreceive 243
#define X86_64_NR_mq_notify 244
#define X86_64_NR_mq_getsetattr 245
#define X86_64_NR_kexec_load 246
#define X86_64_NR_waitid 247
#define X86_64_NR_add_key 248
#define X86_64_NR_request_key 249
#define X86_64_NR_keyctl 250
#define X86_64_NR_ioprio_set 251
#define X86_64_NR_ioprio_get 252
#define X86_64_NR_inotify_init 253
#define X86_64_NR_inotify_add_watch 254
#define X86_64_NR_inotify_rm_watch 255
#define X86_64_NR_migrate_pages 256
#define X86_64_NR_openat 257
#define X86_64_NR_mkdirat 258
#define X86_64_NR_mknodat 259
#define X86_64_NR_fchownat 260
#define X86_64_NR_futimesat 261
#define X86_64_NR_newfstatat 262
#define X86_64_NR_unlinkat 263
#define X86_64_NR_renameat 264
#define X86_64_NR_linkat 265
#define X86_64_NR_symlinkat 266
#define X86_64_NR_readlinkat 267
#define X86_64_NR_fchmodat 268
#define X86_64_NR_faccessat 269
#define X86_64_NR_pselect6 270
#define X86_64_NR_ppoll 271
#define X86_64_NR_unshare 272
#define X86_64_NR_set_robust_list 273
#define X86_64_NR_get_robust_list 274
#define X86_64_NR_splice 275
#define X86_64_NR_tee 276
#define X86_64_NR_sync_file_range 277
#define X86_64_NR_vmsplice 278
#define X86_64_NR_move_pages 279
#define X86_64_NR_utimensat 280
#define X86_64_NR_epoll_pwait 281
#define X86_64_NR_signalfd 282
#define X86_64_NR_timerfd_create 283
#define X86_64_NR_eventfd 284
#define X86_64_NR_fallocate 285
#define X86_64_NR_timerfd_settime 286
#define X86_64_NR_timerfd_gettime 287
#define X86_64_NR_accept4 288
#define X86_64_NR_signalfd4 289
#define X86_64_NR_eventfd2 290
#define X86_64_NR_epoll_create1 291
#define X86_64_NR_dup3 292
#define X86_64_NR_pipe2 293
#define X86_64_NR_inotify_init1 294
#define X86_64_NR_preadv 295
#define X86_64_NR_pwritev 296
#define X86_64_NR_rt_tgsigqueueinfo 297
#define X86_64_NR_perf_event_open 298
#define X86_64_NR_recvmmsg 299
#define X86_64_NR_fanotify_init 300
#define X86_64_NR_fanotify_mark 301
#define X86_64_NR_prlimit64 302
#define X86_64_NR_name_to_handle_at 303
#define X86_64_NR_open_by_handle_at 304
#define X86_64_NR_clock_adjtime 305
#define X86_64_NR_syncfs 306
#define X86_64_NR_sendmmsg 307
#define X86_64_NR_setns 308
#define X86_64_NR_getcpu 309
#define X86_64_NR_process_vm_readv 310
#define X86_64_NR_process_vm_writev 311
#define X86_64_NR_kcmp 312
#define X86_64_NR_finit_module 313
#define X86_64_NR_sched_setattr 314
#define X86_64_NR_sched_getattr 315
#define X86_64_NR_renameat2 316
#define X86_64_NR_seccomp 317
#define X86_64_NR_getrandom 318
#define X86_64_NR_memfd_create 319
#define X86_64_NR_kexec_file_load 320
#define X86_64_NR_bpf 321

/* dummies */
#define X86_64_NR_fstat64	-1
#define X86_64_NR_lstat64	-1
#define X86_64_NR_mmap2		-1
#define X86_64_NR_stat64	-1

#endif /* __hoodwink_x86_64_syscall_h__ */
