//
// Created by jeremymolina on 11/30/19.
//

#ifndef PERMONITOR_DISK_H
#define PERMONITOR_DISK_H

long double getDisk(){
    double totalDiskReads, totalDiskWrites, diskThroughput;
    FILE *diskInfo = fopen("/proc/diskstats", "rb");
    char line[1024];
    while (fgets(line, 1024, diskInfo) != NULL) {
        if (strstr(line, "sda ")) {
            //puts(line);
            sscanf(line, "%*d %*d %*s %lf %*d %*d %*d %lf", &totalDiskReads, &totalDiskWrites);
            diskThroughput = totalDiskReads/totalDiskWrites;
            //printf("Total successful reads: %lf||Total successful writes %lf||Throughput : %lf \n", totalDiskReads, totalDiskWrites, diskThroughput);
        }
    }

    //printf("disk= %lf \n",diskThroughput);

    return diskThroughput;
}

#endif //PERMONITOR_DISK_H
