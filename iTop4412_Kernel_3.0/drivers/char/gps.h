#ifndef _GPS_H_
#define _GPS_H_
#include <linux/ioctl.h>
#define IOCTRL_IOC_MAGIC 'w'

#define RST_HIGH	_IO(IOCTRL_IOC_MAGIC, 1)
#define RST_LOW		_IO(IOCTRL_IOC_MAGIC, 2)
#define EN_HIGH		_IO(IOCTRL_IOC_MAGIC, 3)
#define EN_LOW		_IO(IOCTRL_IOC_MAGIC, 4)
#define POWER_ON	_IO(IOCTRL_IOC_MAGIC, 5)
#define POWER_OFF	_IO(IOCTRL_IOC_MAGIC, 6)

#define IOCTRL_IOC_MAXNR 7
#endif
