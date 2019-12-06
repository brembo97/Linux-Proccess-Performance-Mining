//
// Created by jeremymolina on 11/30/19.
//

#ifndef PERMONITOR_NET_H
#define PERMONITOR_NET_H

double getNet(){
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

#endif //PERMONITOR_NET_H
