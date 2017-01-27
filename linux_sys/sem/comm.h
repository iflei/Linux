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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>


#define PATHNAME "."
#define PROJ_ID 64

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux specific) */
};

int creatSemSet(int nums);
int initSemSet(int semid, int num, int initVal);
int getSemSet();
int destroySemSet(int semid);
int P(int semid, int num);
int V(int semid, int num);

#endif
