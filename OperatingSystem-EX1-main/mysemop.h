#ifndef MYSEMOP_H
#define MYSEMOP_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>

/* 函数声明 */
/* 信号量管理函数 */
int CreateSem(int value);//创建信号量函数
int SetSemValue(int sem_id,int value);//设置信号量值函数
void DeleteSem(int sem_id);//删除信号量函数
int CountSemEat(int sem_id);//进餐计数函数
int GetSemValue(int sem_id);//获取信号量值函数

/* P、V原语 */
int Psem(int sem_id);//P操作
int Vsem(int sem_id);//V操作

#endif

