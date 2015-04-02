#ifndef __hoodwink_backend_h__
#define __hoodwink_backend_h__

extern long backend_clone(unsigned long flags, int *parent_tidptr, int *child_tidptr);

extern void *backend_get_tls(void);
extern void backend_set_tls(void *ptr);

#endif /* __hoodwink_backend_h__ */
