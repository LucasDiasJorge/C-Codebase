#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "time.h"

bool debug = false;

void debugging(char *message) {
    time_t now = time(NULL); // Now
    struct tm tm = *localtime(&now);

    if (debug) {
        printf("\tLog (%s %s): %s;\n",__DATE__, __TIME__, message);
    }
}

void init() {
    if (debug) {
        printf("\n=====Starting=====\n");
        printf("File: %s\n", __FILE__);
        printf("Date: %s\n", __DATE__);
        printf("Time: %s\n", __TIME__);
        printf("Line: %d\n", __LINE__);
        printf("ANSI: %d\n", __STDC__);
        printf("=====Starting=====\n\n");
    }
}

int main(int argc, char *argv[]) {

    if (argc >= 2 && strcmp("--debug", argv[1]) == 0) {
        debug = true;
    }

    init();

    debugging("Press \"Enter\" to stop");

    getchar(); // Code here

    debugging("Stopping");

    sleep(3);

    debugging("Exiting");

    return 0;
}
