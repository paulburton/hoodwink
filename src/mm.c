#include "debug.h"
#include "mm.h"
#include "string.h"
#include "sys.h"
#include "syscall.h"

#define BITS_PER_LONG (sizeof(long) * 8)

void mm_init(struct sys_state *sys)
{
	size_t addr_space;
	size_t bitmap_sz;

	addr_space = 1u << 31;
	bitmap_sz = (addr_space >> sys->page_bits) / 8;

	sys->page_bitmap = sys_mmap(NULL, bitmap_sz, PROT_READ | PROT_WRITE,
				    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (IS_ERROR(sys->page_bitmap)) {
		debug("Failed to allocate %u byte page bitmap\n", (unsigned)bitmap_sz);
		sys_exit(1);
	}
	memset(sys->page_bitmap, 0, bitmap_sz);

	sys->mmap_pfn_min = addr_to_pfn(sys, 0x40000000);
	sys->mmap_pfn_max = addr_to_pfn(sys, 0x6fffffff);
}

static void mm_mark_alloc(struct sys_state *sys, unsigned pfn_start, unsigned pfn_end)
{
	unsigned pfn;

	for (pfn = pfn_start; pfn <= pfn_end; pfn++)
		sys->page_bitmap[pfn / BITS_PER_LONG] |= 1ul << (pfn % BITS_PER_LONG);
}

#if 0
static void mm_clear_alloc(struct sys_state *sys, unsigned pfn_start, unsigned pfn_end)
{
	unsigned pfn;

	for (pfn = pfn_start; pfn <= pfn_end; pfn++)
		sys->page_bitmap[pfn / BITS_PER_LONG] &= ~(1 << (pfn % BITS_PER_LONG));
}
#endif

static int mm_page_avail(struct sys_state *sys, unsigned pfn)
{
	return !(sys->page_bitmap[pfn / BITS_PER_LONG] & (1ul << (pfn % BITS_PER_LONG)));
}

static void range_to_pfns(struct sys_state *sys, uint32_t addr, uint32_t length, unsigned *pfn_start, unsigned *pfn_end)
{
	length -= addr & ((1 << sys->page_bits) - 1);
	length += (1 << sys->page_bits) - 1;
	length &= ~((1 << sys->page_bits) - 1);

	*pfn_start = addr >> sys->page_bits;
	*pfn_end = *pfn_start + ((length - 1) >> sys->page_bits);
}

static int mm_pages_avail(struct sys_state *sys, unsigned pfn_start, unsigned pfn_end)
{
	unsigned pfn;

	for (pfn = pfn_start; pfn <= pfn_end; pfn++) {
		if (!mm_page_avail(sys, pfn)) {
			debug("page %u unavailable!\n", pfn);
			return 0;
		}
	}

	return 1;
}

static int mm_region_avail(struct sys_state *sys, uint32_t addr, uint32_t length)
{
	unsigned pfn_start, pfn_end;

	range_to_pfns(sys, addr, length, &pfn_start, &pfn_end);
	return mm_pages_avail(sys, pfn_start, pfn_end);
}

static uint32_t mm_region_find(struct sys_state *sys, uint32_t length)
{
	unsigned pfn, page_span;

	page_span = (length - 1) >> sys->page_bits;

	for (pfn = sys->mmap_pfn_min; pfn <= sys->mmap_pfn_max; pfn++) {
		debug("mmap try pages %u-%u...", pfn, pfn + page_span);
		if (mm_pages_avail(sys, pfn, pfn + page_span)) {
			debug(" ok!\n");
			return pfn << sys->page_bits;
		}
		debug(" nope...\n");
	}

	return 0;
}

uint32_t mm_mmap(struct sys_state *sys, uint32_t addr, uint32_t length, int prot, int flags, int fd, uint32_t offset)
{
	unsigned pfn_start, pfn_end;
	void *map;

	if (!(flags & MAP_FIXED)) {
		if (!addr || !mm_region_avail(sys, addr, length))
			addr = mm_region_find(sys, length);
	}

	debug("mm_mmap using addr 0x%x\n", addr);

	range_to_pfns(sys, addr, length, &pfn_start, &pfn_end);
	debug("mm_mmap checking availability of pages %u to %u\n", pfn_start, pfn_end);
	if (!mm_pages_avail(sys, pfn_start, pfn_end)) {
		debug("mm_mmap pages not avaiilable\n");
	}

	//addr = pfn_start << sys->page_bits;
	//length = (1 + pfn_end - pfn_start) << sys->page_bits;
	flags |= MAP_FIXED;

	debug("mm_mmap re-mapping with flags 0x%x\n", flags);
	map = sys_mmap(sys->mem_base + addr, length, prot, flags, fd, offset);
	if (IS_ERROR(map)) {
		debug("Failed to mmap region\n");
		sys_exit(1);
	}
	if (map - sys->mem_base != addr) {
		debug("System mmap'ed at an unexpected address\n");
		sys_exit(1);
	}

	debug("mm_mmap marking pages %u to %u\n", pfn_start, pfn_end);
	mm_mark_alloc(sys, pfn_start, pfn_end);

	return addr;
}
