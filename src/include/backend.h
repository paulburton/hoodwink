#ifndef __hoodwink_backend_h__
#define __hoodwink_backend_h__

extern long backend_clone(unsigned long clone_flags, unsigned long newsp,
			  int *parent_tidptr, int *child_tidptr, int tls_val);

extern void *backend_get_tls(void);
extern void backend_set_tls(void *ptr);

#endif /* __hoodwink_backend_h__ */
