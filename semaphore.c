#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>



//shared file 
int counter;
sem_t s;


void *fun1(){
    while(1){
    sem_wait(&s);
    sleep(1);
    char c;
    FILE *fd=fopen("ff.txt","w");
    c=(counter>0)?c+1:'a';
    counter=(counter>0)?counter-1:25;
    printf("paternt wrote %c\n",c);
    fprintf(fd,"%c\n",c);
    fclose(fd);
    sem_post(&s);
    }

}

void*fun2(){
    while(1){
    sem_wait(&s);
    sleep(1);
    FILE *fd=fopen("ff.txt","r");
    char c;
    fscanf(fd,"%c",&c);
    printf("chiled read %c\n",c);
    fclose(fd);
    sem_post(&s);
    }
}


int main(){
    pthread_t th1,th2;
    sem_init(&s,0,2);

    pthread_create(&th1,NULL,fun1,NULL);
    pthread_create(&th2,NULL,fun2,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    sem_destroy(&s);
    return 0;



}
