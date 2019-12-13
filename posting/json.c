//
// Created by brembo on 12/12/19.
//

#include "json.h"

#define BUF_LEN 256

int formatToJSON(long double valorMinado){
    //buffer del timestamp
    char buf[BUF_LEN] = {0};
    time_t rawtime = time(NULL);
    if (rawtime == -1) {

        puts("The time() function failed");
        return 1;
    }
    //struct tm tipo timestamp
    struct tm *ptm = localtime(&rawtime);
    if (ptm == NULL) {

        puts("The localtime() function failed");
        return 1;
    }
    //conversion del struct tm a string
    strftime(buf, BUF_LEN, "%FT%T%z", ptm);

    char payload[4096];
    snprintf(
            payload,
            4096,
            "[{\"measurement\":\"cpu\",\"tags\":{\"host_name\":\"NEM\",\"miner_id\":\"miner_69\"},\"time\":\"%s\",\"captures\":{\"value\":%Lf}}]",
            buf,
            valorMinado
    );
    printf("Generated Payload: %s \n", payload);

    //envio http al server
    int result = send_http_post(
            "/cpu_metric",
            payload,
            "application/json"
    );
    //Verificar estado del post request
    printf("\n CODE: %d \n", result);
    printf("Sent! \n");

    return result;
}