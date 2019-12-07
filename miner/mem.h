//
// Created by jeremymolina on 11/30/19.
//

#ifndef PERMONITOR_MEM_H
#define PERMONITOR_MEM_H

double long getMem(){ // This value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];
    int i = strlen(line);
    const char* p = line;

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            while (*p <'0' || *p > '9') p++;
            line[i-3] = '\0';
            result = atoi(p);
            break;
        }
    }
    fclose(file);

    //printf("mem= %d Kb \n",result);

    return result;
}

#endif //PERMONITOR_MEM_H
