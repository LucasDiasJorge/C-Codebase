#include <stdio.h>
#include <time.h>

#define LOOP_TIME 3

int main() {

    time_t send_time = time(NULL) + LOOP_TIME;
    time_t now = time(NULL);

    while(1){

        if (send_time <= now){
            // function here
            printf("Function Call example\n");
            send_time = time(NULL) + LOOP_TIME;
        }
        now = time(NULL);
    }

    return 0;

}