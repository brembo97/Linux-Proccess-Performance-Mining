//
// Created by brembo on 12/12/19.
//

#ifndef PERMONITOR_JSON_H
#define PERMONITOR_JSON_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "http.h"

int formatToJSON(long double valorCPU,long double valorMEM,long double valorNET,long double valorDISK);

#endif //PERMONITOR_JSON_H
