
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <pthread.h>
void *square(void* n){
    int in=*(int*)n;
    int *result=malloc(sizeof(int));
    int res=in*in;
    *result=res;

    printf("im thread1 %d^%d=%d\n",in,in,res);
    return (void *)result;
    
}

void* function2(){
    printf("im thread2,a new chiled will be created\n");
    if(fork()==0){
        printf("child,pricess id=%d, parent=%d\n",getpid(),getppid());


    }
    else{
        printf("parent ,pricess id=%d, parent=%d\n",getpid(),getppid());
    }
}

int main(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    int in;
    int *res;

    printf("enter an integer");
    scanf("%d",&in);
    printf("2 threads will be created");

    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1,NULL,&square,&in);
    pthread_create(&t2,NULL,&function2,NULL);

    pthread_join(t2,NULL);
    pthread_join(t1,(void**)&res);
    printf("%d\n",*res);
    free(res);
    

    wait(NULL);
    return 0;


}
