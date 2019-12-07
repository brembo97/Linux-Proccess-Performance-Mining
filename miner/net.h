//
// Created by jeremymolina on 11/30/19.
//

#ifndef PERMONITOR_NET_H
#define PERMONITOR_NET_H

long double getNet(){
    FILE *netInfo = fopen("/proc/net/dev", "r");
    char line[1024];
    double bytesReceived=1, bytesTransmitted=1, byteThroughput = 0;
    while(fgets(line, 1024, netInfo) != NULL){
        if(strstr(line, "ens33")){
            //puts(line);
            sscanf(line, "%*s %lf %*d %*d %*d %*d %*d %*d %*d %lf", &bytesReceived, &bytesTransmitted);
            byteThroughput = bytesReceived/bytesTransmitted;
            //printf("Number of bytes received: %lf | Number of bytes transmitted: %lf | Total Throughput: %lf \n", bytesReceived, bytesTransmitted, byteThroughput);
        }
    }

    //printf("net= %lf \n",byteThroughput);

    return byteThroughput;
}

#endif //PERMONITOR_NET_H
