#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "disk.h"
#include "net.h"
#include "cpu.h"
#include "mem.h"


static int miner_id = -1;

double diskMine() {
    return getDisk();
}

double getNetUsage(){
    return getNet();
}

long getMemUsage() {
    return getMem();
}

double getCpuUsage(){
    return getCurrentCpu();
}

void mem(){
    printf("MEMORY Child Process Created\n");
    getMemUsage();
    exit(0);
}

void cpu(){
    printf("CPU Child Process Created\n");
    getCpuUsage();
    exit(0);
}

void net(){
    printf("NET Child Process Created\n");
    getNetUsage();
    exit(0);
}

void disk(){
    printf("DISK Child Process Created\n");
    diskMine();
    exit(0);
}

void route_to_miner_function(){
    switch(miner_id){
        case 1:
            cpu();
            break;
        case 2:
            mem();
            break;
        case 3:
            net();
            break;
        case 4:
            disk();
            break;
        default:
            break;
    }
}

pid_t init_miner(int new_miner_id){
    miner_id = new_miner_id;
    pid_t child_process_id;
    switch(child_process_id = fork()){
        case -1:
            break;
        case 0:
            route_to_miner_function();
            break;
        default:
            sleep(3);
            wait(0);
            break;
    }
}

int main(int argc, char * argv[]) {

    for(int i = 0; i < argc;++i){

        if(strcmp(argv[i], "-c") == 0){
            init_miner(1);
        }
        else if(strcmp(argv[i], "-m") == 0){
            init_miner(2);
        }
        else if(strcmp(argv[i], "-n") == 0){
            init_miner(3);
        }
        else if(strcmp(argv[i], "-d") == 0){
            init_miner(4);
        }
    }
}