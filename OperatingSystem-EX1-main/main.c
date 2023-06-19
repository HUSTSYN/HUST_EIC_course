//#include "mysemop.c"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

//全局变量
int root_sem_id = 0;
int chopsticks_sem_id[5];//筷子信号量数组初始化
int count_sem_id[5];//哲学家进餐次数数组初始化 

int main(int argc, char argv[]){

	pid_t pid;//创建进程标识符
	
	pid_t chldpid[5];//子进程标识符有5个
	
	char quit;//用于检测退出程序的单字符
	int i = 0;//循环检测
 
	int room_sem_id = CreateSem(4);//一个房间里最多同时有4位哲学家准备进餐
	//初始化信号量
	for (i = 0; i < 5; i++) {
		chopsticks_sem_id[i] = CreateSem(1);//为每只筷子创建信号量
	}
	for (i = 0; i < 5; i++) {
		count_sem_id[i] = CreateSem(0);
	}
 	
	//创建子进程
	for (i = 0; i < 5; i++) {
		pid = fork();
		if (pid < 0) {
			fprintf(stderr,"创建进程时，哲学家 %d 失败！\n", i);
			exit(-1);
		}
		if (pid == 0) {
			while (1) {
				printf("哲学家 %d 正在思考！\n", i);
				sleep(1);
 
				Psem(room_sem_id);//进入房间
				printf("哲学家 %d 饿了，因此他进入了房间\n", i);
 
				Psem(chopsticks_sem_id[i]);//试图拿起左侧筷子
				printf("哲学家 %d 拿起了他左侧的筷子\n", i);
 
				Psem(chopsticks_sem_id[(i + 1) % 5]);//试图拿起右侧筷子
				printf("哲学家 %d 拿起了他右侧的筷子\n", i);
 
				printf("哲学家 %d 开始进餐！\n", i);
				sleep(5 - i);//开始进餐
 
				printf("哲学家 %d 完成进餐，停止进餐\n", i);
				
				printf("哲学家 %d 结束进餐！\n", i);
				Vsem(chopsticks_sem_id[(i + 1) % 5]);//结束进餐
 				CountSemEat(count_sem_id[i]);//记录进餐次数 

				printf("哲学家 %d 放下了他右侧的筷子\n", i);
				Vsem(chopsticks_sem_id[i]);//把右侧筷子放回原处
 
				printf("哲学家 %d 放下了他左侧的筷子\n", i);
				Vsem(room_sem_id);//把左侧筷子放回原处
				
				printf("哲学家 %d 离开了房间！\n",i);
				printf("哲学家 %d 开始思考！\n",i);
				sleep(1);
			}
		} else {
			chldpid[i] = pid;
		}
	}
	
	do {//结束所有的哲学家进餐进程
		quit = getchar();//获取输入的单字符
			if (quit == 'q'){
				for (i = 0; i < 5; i++)
					kill(chldpid[i], SIGTERM);//杀掉子进程
					printf("哲学家 %d 进餐次数为 %d 次\n", i ,GetSemValue(count_sem_id[i]));
			}
			//删除信号量
			for(i = 0; i <5 ; i++){
				DeleteSem(chopsticks_sem_id[i]);
				DeleteSem(count_sem_id[i]);
			}
			DeleteSem(room_sem_id);
		

	} while (quit != 'q');
}

