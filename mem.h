//
// Created by jeremymolina on 11/30/19.
//

#ifndef PERMONITOR_MEM_H
#define PERMONITOR_MEM_H

#include <sys/resource.h>
#include <unistd.h>

#include "sys/times.h"

long getMem(){
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);

    return r_usage.ru_maxrss;
}

#endif //PERMONITOR_MEM_H
