#include <stdarg.h>

#include "debug.h"
#include "string.h"
#include "syscall.h"

unsigned debug_mask = DEBUG_SYSCALL;
static int debug_fd;

void debug_init(const char *filename)
{
	debug_fd = sys_open(filename, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (debug_fd < 0) {
		/* no good way to log this... exit? */
		debug_fd = -1;
	}
}

static void debug_char(char ch)
{
	if (debug_fd == -1)
		return;

	sys_write(debug_fd, &ch, 1);
}

struct debug_buf {
	char data[64];
	unsigned count;
};

static void debug_buf_flush(struct debug_buf *buf)
{
	if (debug_fd == -1)
		return;

	sys_write(debug_fd, buf->data, buf->count);
	buf->count = 0;
}

static void debug_buf_write_char(struct debug_buf *buf, char ch)
{
	buf->data[buf->count++] = ch;

	if (buf->count == sizeof(buf->data))
		debug_buf_flush(buf);
}

static void debug_buf_write_str(struct debug_buf *buf, char *str)
{
	while (*str)
		debug_buf_write_char(buf, *str++);
}

static void debug_buf_write_u64(struct debug_buf *buf, uint64_t val, unsigned base, unsigned digits, char pad)
{
	char str[32], *ch = &str[sizeof(str)];
	unsigned d, len = 0;

	/* NULL terminate */
	*--ch = 0;

	do {
		d = val % base;
		val /= base;

		*--ch = (d >= 10) ? ('a' + d - 10) : ('0' + d);
		len++;
	} while (val);

	while (len < digits) {
		*--ch = pad;
		len++;
	}

	debug_buf_write_str(buf, ch);
}

static void debug_buf_write_i64(struct debug_buf *buf, int64_t val, unsigned base, unsigned digits, char pad)
{
	if (val < 0) {
		debug_buf_write_char(buf, '-');
		val = -val;
	}

	debug_buf_write_u64(buf, val, base, digits, pad);
}

void debug(const char *fmt, ...)
{
	struct debug_buf buf;
	va_list ap;
	char ch, pad;
	unsigned digits;

	buf.count = 0;
	va_start(ap, fmt);

	for (ch = *fmt++; ch; ch = *fmt++) {
		if (ch != '%') {
			debug_buf_write_char(&buf, ch);
			continue;
		}

		ch = *fmt++;

		pad = ' ';
		if (ch == '0') {
			pad = '0';
			ch = *fmt++;
		}

		digits = 0;
		while (ch >= '0' && ch <= '9') {
			digits *= 10;
			digits += ch - '0';
			ch = *fmt++;
		}

		switch (ch) {
		default:
			debug_buf_write_char(&buf, ch);
			break;

		case 'd':
			debug_buf_write_i64(&buf, va_arg(ap, int), 10, digits, pad);
			break;

		case 'p':
			debug_buf_write_u64(&buf, (uint64_t)va_arg(ap, void *), 16, sizeof(void *) * 2, '0');
			break;

		case 's':
			debug_buf_write_str(&buf, va_arg(ap, char *));
			break;

		case 'u':
			debug_buf_write_u64(&buf, va_arg(ap, unsigned), 10, digits, pad);
			break;

		case 'x':
			debug_buf_write_u64(&buf, va_arg(ap, unsigned), 16, digits, pad);
			break;
		}
	}

	va_end(ap);
	debug_buf_flush(&buf);
}

void debug_x64(uint64_t val, int ndigits)
{
	char str[16], zero = '0';
	unsigned digit;
	int i, len;

	if (debug_fd == -1)
		return;

	for (i = 15; i >= 0 && (val || i == 15); i--) {
		digit = val % 16;
		val /= 16;

		if (digit >= 10)
			str[i] = 'a' + digit - 10;
		else
			str[i] = '0' + digit;
	}

	len = 15 - i;

	ndigits -= len;
	while (ndigits-- > 0)
		sys_write(debug_fd, &zero, 1);

	sys_write(debug_fd, str + (sizeof(str) - len), len);
}

void debug_x32(uint32_t val, int ndigits)
{
	debug_x64(val, ndigits);
}

void debug_u64(uint64_t val)
{
	char str[22], *ch = &str[22];
	unsigned digit, len = 0;

	if (debug_fd == -1)
		return;

	do {
		digit = val % 10;
		val /= 10;
		*--ch = '0' + digit;
		len++;
	} while (val);

	sys_write(debug_fd, ch, len);
}

void debug_u32(uint32_t val)
{
	debug_u64(val);
}

void debug_i64(int64_t val)
{
	if (val < 0) {
		debug_char('-');
		val = -val;
	}

	debug_u64(val);
}

void debug_i32(int32_t val)
{
	debug_i64(val);
}
