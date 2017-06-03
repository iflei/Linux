/*************************************************************************
	> File Name: comm.h
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#ifndef _COMM_H
#define _COMM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define PATHNAME "."
#define PROJ_ID 64

int creatShm(int size);
int getShm();
int destroyShm(int shmid);

#endif
