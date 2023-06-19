#include "mysemop.h"
/* 创建信号量 */
int CreateSem(int value)
{
	int sem_id;
	/* 获取一个信号量集的句柄 */
	sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	if(sem_id == -1) return -1;
	/* 设置信号量初始值 */
	if(SetSemValue(sem_id, value)== 0) return -1;
	return sem_id;		
}

/* 强制设置信号量的值 */
int SetSemValue(int  sem_id,  int  value)
{
	if (semctl(sem_id, 0, SETVAL, value) == -1) return 0;
	return 1;  }
/* 删除信号量 */
void DeleteSem(int sem_id)
{
	if(semctl(sem_id, 0, IPC_RMID) == -1)
		fprintf(stderr,"Failed to delete semaphore\n");		
}

//获取信号量值
int GetSemValue(int  sem_id)
{
	if (semctl(sem_id, 0, GETVAL) == -1) return 0;
	int count = semctl(sem_id, 0, GETVAL);
	return count;  
}

//进餐计数函数
int CountSemEat(int sem_id){
	/* 设计操作结构体 */
	struct  sembuf  sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	
	/* 调用库函数，进行V操作 */
	if(semop(sem_id, &sem_b, 1) == -1){
		fprintf(stderr, "V failed\n");
		return 0;
	}
	return 1;
}

/* P原语*/
int Psem(int sem_id)
{
	/* 设计操作结构体 */
	struct  sembuf  sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	
	/* 调用库函数，进行P操作 */
	if(semop(sem_id, &sem_b, 1) == -1){
		fprintf(stderr, "P failed\n");
		return 0;
	}
	return 1;
}

/* V原语*/
int Vsem(int sem_id)
{
	/* 设计操作结构体 */
	struct  sembuf  sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	
	/* 调用库函数，进行V操作 */
	if(semop(sem_id, &sem_b, 1) == -1){
		fprintf(stderr, "V failed\n");
		return 0;
	}
	return 1;
}

