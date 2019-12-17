#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "sys/times.h"
#include <sys/wait.h>
#include "string.h"
#include "sys/types.h"
#include "sys/sysinfo.h"

#include "miner/disk.h"
#include "miner/net.h"
#include "miner/cpu.h"
#include "miner/mem.h"
#include "queue/q.h"
#include "posting/json.h"


static int miner_id = -1;
#define QueueSizeHardLimit 32
#define QueueSizeSoftLimit 24

pid_t init_miner(int new_miner_id){
    miner_id = new_miner_id;
    pid_t child_process_id;
    switch(child_process_id = fork()) {
        case -1:
            break;
        case 0:
            for(;;){
                enqueue(getCpu());
                enqueue(getMem());
                enqueue(getNet());
                enqueue(getDisk());

                if (queueSize() == QueueSizeSoftLimit) {
                    printf("Soft Limit Reached: %d \n", queueSize());

                    sendOut();

                    for (int i = 0; i < QueueSizeSoftLimit; ++i) {
                        printf("Dequeue object: %d \n", dequeue(i));
                    }
                }
                else if (queueSize() == QueueSizeHardLimit){
                    printf("Queue full %d \n", queueSize());
                    exit(0);

                }
                else printf("Queue size: %d \n", queueSize());
            }

        default:
            sleep(1);
            wait(0);
            break;
    }
}

double main() {
    init_miner(0);
    sleep(1);

}