#include "comm.h"

static int commSemSet(int nums, int flags)
{
    key_t _key = ftok(PATHNAME, PROJ_ID);
    if(_key < 0)
    {
        perror("ftok");
        return -1;
    }
    int semid = semget(_key, nums, flags);
    if(semid < 0)
    {
        perror("semget");
        return -2;
    }
    return semid;
}

static int commPV(int semid, int num, int op)
{
    struct sembuf _sf;
    _sf.sem_num = num; //对哪个信号量操作
    _sf.sem_op = op;
    _sf.sem_flg = 0;
    if(semop(semid, &_sf, 1) < 0)
    {
        perror("semop");
        return -1;
    }
    return 0;
    
}

int creatSemSet(int nums)
{
    return commSemSet(nums, IPC_CREAT|0666);
}

int initSemSet(int semid, int num, int initVal)
{
    union semun _un;
    _un.val = initVal;
    if(semctl(semid, num, SETVAL, _un) < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}

int getSemSet()
{
    return commSemSet(0, IPC_CREAT);
}

int destroySemSet(int semid)
{
    if(semctl(semid, 0, IPC_RMID, NULL) < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}

int P(int semid, int num)
{
    return commPV(semid, num, -1);
}

int V(int semid, int num)
{
    return commPV(semid, num, 1);
}

