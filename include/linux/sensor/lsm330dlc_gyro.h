/*
 *	Copyright (C) 2011, Samsung Electronics Co. Ltd. All Rights Reserved.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 */

#ifndef __L3GD20_H__
#define __L3GD20_H__

#define LSM330DLC_GYRO_DEV_NAME	"lsm330dlc_gyro"
#define L3GD20_GYR_INPUT_NAME "gyro_sensor"
#define GYR_DEV_FILE_NAME "lsm330dlc_gyro_misc"

#define DPS250		250
#define DPS500		500
#define DPS2000		2000

struct lsm330dlc_gyro {
        s16 x;
        s16 y;
        s16 z;
};

#define LSM330DLC_GYRO_IOCTL_BASE	80
#define LSM330DLC_GYRO_IOCTL_SET_DELAY\
	_IOW(LSM330DLC_GYRO_IOCTL_BASE, 0, int64_t)
#define LSM330DLC_GYRO_IOCTL_GET_DELAY\
	_IOR(LSM330DLC_GYRO_IOCTL_BASE, 1, int64_t)
#define LSM330DLC_GYRO_IOCTL_READ_DATA_XYZ\
	_IOR(LSM330DLC_GYRO_IOCTL_BASE, 2, struct lsm330dlc_gyro)
#define LSM330DLC_GYRO_IOCTL_SET_RANGE \
    	_IOW(LSM330DLC_GYRO_IOCTL_BASE, 3, int)
#define LSM330DLC_GYRO_IOCTL_SET_ENABLE   \
    	_IOW(LSM330DLC_GYRO_IOCTL_BASE, 4, bool)

#endif /* __L3GD20_H__ */
