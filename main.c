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

void route_to_miner_function(){
    switch(miner_id){
        case 1:
            getCpu();
            break;
        case 2:
            getMem();
            break;
        case 3:
            getNet();
            break;
        case 4:
            getDisk();
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
            printf("Running miner %u", new_miner_id);
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
        else {
            init_miner(1);
            init_miner(2);
            init_miner(3);
            init_miner(4);
        }
    }
}