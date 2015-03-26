#ifndef __hoodwink_util_h__
#define __hoodwink_util_h__

#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N

#define VA_NUM_ARGS_NOZERO(...) \
	VA_NUM_ARGS_IMPL(__VA_ARGS__, 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)

/* note that this won't handle 0 args for assembly! */
#ifndef __ASSEMBLER__
# define VA_NUM_ARGS(...) \
	(sizeof(#__VA_ARGS__) == sizeof("") ? 0 : VA_NUM_ARGS_NOZERO(__VA_ARGS__))
#endif

#define _CAT(a, b) a ## b
#define CAT(a, b) _CAT(a, b)

#define typeof __typeof__

#define max(a, b) ({			\
	typeof(a) __a = (a);		\
	typeof(b) __b = (b);		\
	__a > __b ? __a : __b;		\
})

#define min(a, b) ({			\
	typeof(a) __a = (a);		\
	typeof(b) __b = (b);		\
	__a < __b ? __a : __b;		\
})

#define isnan __builtin_isnan

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#endif /* __hoodwink_util_h__ */
