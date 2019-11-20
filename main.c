#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

static int miner_id = -1;

double diskMine() {
    double totalDiskReads, totalDiskWrites, diskThroughput;
    FILE *diskInfo = fopen("/proc/diskstats", "rb");
    char line[1024];
    while (fgets(line, 1024, diskInfo) != NULL) {
        if (strstr(line, "nvme0n1 ")) {
            puts(line);
            sscanf(line, "%*d %*d %*s %lf %*d %*d %*d %lf", &totalDiskReads, &totalDiskWrites);
            diskThroughput = totalDiskReads/totalDiskWrites;
            printf("Total successful reads: %lf||Total successful writes %lf||Throughput : %lf \n", totalDiskReads, totalDiskWrites, diskThroughput);
        }
    }
    return diskThroughput;
}

double getNetUsage(){
    FILE *netInfo = fopen("/proc/net/dev", "r");
    char line[1024];
    double bytesReceived=1, bytesTransmitted=1, byteThroughput = 0;
    while(fgets(line, 1024, netInfo) != NULL){
        if(strstr(line, "wlp2s0")){
            puts(line);
            sscanf(line, "%*s %lf %*d %*d %*d %*d %*d %*d %*d %lf", &bytesReceived, &bytesTransmitted);
            byteThroughput = bytesReceived/bytesTransmitted;
            printf("Number of bytes received: %lf | Number of bytes transmitted: %lf | Total Throughput: %lf \n", bytesReceived, bytesTransmitted, byteThroughput);
        }
    }
    return byteThroughput;
}

int getMemUsage() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);

    printf("The  %ld \n", r_usage.ru_maxrss);
    return r_usage.ru_maxrss;
}

double getCpuUsage(void)
{
    double a[4], b[4], loadavg, calcGB;
    FILE *fp;

    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %lf %lf %lf %lf",&b[0],&b[1],&b[2],&b[3]);
    fclose(fp);

    loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
    printf("The workload of the system for the last 15 minutes is %lf \n",loadavg);

    return loadavg;
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