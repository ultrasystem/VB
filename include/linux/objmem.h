#ifndef _LINUX_OBJMEM_H
#define _LINUX_OBJMEM_H

#include <linux/limits.h>
#include <linux/ioctl.h>

#define OBJMEM_NAME_LEN		256


struct objmem_create_data {
    char    name[OBJMEM_NAME_LEN];
    size_t  size;
};

#define __OBJMEMIOC		0x90

#define OBJMEM_IOCTL_CREATE		_IOW(__OBJMEMIOC, 1, struct objmem_create_data)
#define OBJMEM_IOCTL_INTERVAL   _IOW(__OBJMEMIOC, 2, uint64_t)
#define OBJMEM_IOCTL_GETPID     _IOR(__OBJMEMIOC, 3, pid_t)
#endif	/* _LINUX_ASHMEM_H */
