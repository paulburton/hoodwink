#ifndef __hoodwink_backend_h__
#define __hoodwink_backend_h__

extern long backend_clone(unsigned long clone_flags, unsigned long newsp,
			  int *parent_tidptr, int *child_tidptr, int tls_val);

#endif /* __hoodwink_backend_h__ */
