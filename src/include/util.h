#ifndef __hoodwink_util_h__
#define __hoodwink_util_h__

#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 8,7,6,5,4,3,2,1)
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,N,...) N

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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#endif /* __hoodwink_util_h__ */
