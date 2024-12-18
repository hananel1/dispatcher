/*
TO DO:
1) queue data type to store commands
2) thread function
3) support log enable
4) finish main

*/
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//DEFINES
#define MAX_THREADS 4096
#define MAX_COUNTERS 100
#define MAX_LINE 1024

//VARIABLES
typedef unsigned long long int u64; // for the counters

pthread_t tid[MAX_THREADS]; // array of type pthread_t
FILE *counters[MAX_COUNTERS]; // array of pointers to  pointers to counter files
FILE *log_threads[MAX_THREADS]; // array of pointers to  pointers to thread log files

/*
void* thread_func(void* arg){
    FILE *fp = (FILE*)arg; //cast file* on the arg, this is the pointer to the log file
}
*/

int main(int argc, char *argv[]){
    int num_threads, num_counters;
    FILE *commands = fopen(argv[1], "r");

    //check input

    if(commands==NULL){
        printf("Error openning cmdfile.txt\n");
        exit(-1);
    }
    
    if (argc != 5){
        printf("Incorrect number of arguments\n");
        exit(-1);
    }
    
    num_threads = atoi(argv[2]); num_counters = atoi(argv[3]);

    if (num_threads> MAX_THREADS || num_threads<0){
        printf("Max threads shoud be between 0 and %d\n", MAX_THREADS);
        exit(-1);
    }

    if (num_counters> MAX_COUNTERS || num_counters<0){
        printf("Max counters shoud be between 0 and %d\n", MAX_COUNTERS);
        exit(-1);
    }
    //counter files intitialization

    

    for(int i = 0; i<num_counters;i++){
        char filename[20];
        sprintf(filename,"counter%02d.txt",i);
        counters[i] = fopen(filename,"w");

        if (counters[i] == NULL) {
            printf("Error opening file %d", i);
            // Clean up already opened files
            for (int j = 0; j < i; j++) {
                fclose(counters[j]);
            }
            exit(-1);
        }
        fprintf(counters[i],"%lld",(u64)0);
        fclose(counters[i]);
    }

    // worker thread creation
    /*
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(int i=0; i<num_threads;i++){
        pthread_create(&tid[i],&attr,thread_func,(void*)&log_threads[i]); //forward the log file
    }
    */

    // dispatcher initialization
    
    char line[MAX_LINE];

    while(fgets(line,MAX_LINE,commands)){     //iterate over lines of file
        char *token= strtok(line," ;\n"); // get first argument

        if(!strcmp(token,"worker")){
            //printf("worker \n"); 
        }

        else{
            if(!strcmp(token,"dispatcher_msleep")){
                token = strtok(NULL," ;\n");
                int tsleep;
                tsleep = atoi(token);
                usleep(1000*tsleep);
                //printf("dispatcher sleep for %d msec\n", tsleep);
            }
            else{
                //printf("dispatcher should wait\n");
            }
        }

    }
    
    fclose(commands); //close the cmdfile.txt
}