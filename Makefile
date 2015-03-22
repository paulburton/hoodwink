include util.mk

FRONT_ARCH ?= mips32
BACK_ARCH ?= $(shell uname -m)

DEBUG ?= 1
STRIP ?= 0

c_flags := \
	-std=c11 -Wall -Werror \
	-O2 -ggdb \
	-Isrc/include \
	-fno-asynchronous-unwind-tables \
	-D_DEFAULT_SOURCE \
	-DBACK_ARCH_$(call uppercase,$(BACK_ARCH)) \
	-DFRONT_ARCH_$(call uppercase,$(FRONT_ARCH)) \

s_source :=
c_source := \
	src/elf.c \
	src/main.c \
	src/mm.c \
	src/signal.c \
	src/syscall.c

ifeq ($(DEBUG),1)
c_flags += -DDEBUG
c_source += src/debug.c
endif

include src/syscalls/Makefile
include src/frontend/$(FRONT_ARCH)/Makefile
include src/backend/$(BACK_ARCH)/Makefile

s_objects := $(patsubst %.S,%.o,$(s_source))
c_objects := $(patsubst %.c,%.o,$(c_source))
objects := $(s_objects) $(c_objects)
depfiles := $(patsubst %.o,%.d,$(objects))

.PHONY: all
all: hoodwink

.PHONY: clean
clean:
	rm -f hoodwink hoodwink.elf $(objects) $(depfiles)

ifeq ($(STRIP),1)

hoodwink: hoodwink.elf
	rm -f $@
	strip -s -R .comment -R .note.gnu.build-id -o $@ $<

else

hoodwink: hoodwink.elf
	ln -sf $< $@

endif

hoodwink.elf: $(objects) Makefile
	$(CC) $(c_flags) $(CFLAGS) -o $@ -nostdlib -static $(objects)

%.o: %.c Makefile
	$(CC) $(c_flags) $(CFLAGS) -o $@ -c $<
	$(CC) $(c_flags) $(CFLAGS) -MM -MT $@ -c $< >$*.d

%.o: %.S Makefile
	$(CC) $(c_flags) $(CFLAGS) -o $@ -c $<
	$(CC) $(c_flags) $(CFLAGS) -MM -MT $@ -c $< >$*.d

-include $(depfiles)
