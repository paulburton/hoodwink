local_dir := src/backend/x86_64

local_c_source := \
	clone.c

local_s_source := \
	start.S \
	syscall.S

c_source += $(addprefix $(local_dir)/,$(local_c_source))
s_source += $(addprefix $(local_dir)/,$(local_s_source))
