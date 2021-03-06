#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "wf_interface.h"
#include "common.h"

void mytask(int) { LOG_TIMER("task"); }

LOG_TimeUnit LOG_start, LOG_mid, LOG_stop;

void test(int n) {

    LOG_start = LOG_getTimeStart();
    
    for (int i = 0; i < n; ++i)
        spawn( mytask, 0 );

    LOG_mid = LOG_getTimeStop();

    ssync();

    LOG_stop = LOG_getTimeStop();
}

int main(int argc, char *argv[]) {

    int n = 1000000;

    if (argc > 1)
        n = atoi(argv[1]);
    if (argc > 2)
        delay = atoi(argv[2]);

    TIMING_init();

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        run ( test, n );
        TIMING_add(LOG_start, LOG_mid, LOG_stop);
        LOG_optional_break
    }

    TIMING_end(n);
    LOG_dump("swan.log");

    return 0;
}
