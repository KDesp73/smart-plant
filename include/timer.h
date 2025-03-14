#pragma once

#define EVERY_MS(TIMER_VAR, INTERVAL, CODE) \
    static unsigned long TIMER_VAR = 0; \
    if (millis() - TIMER_VAR >= INTERVAL) { \
        TIMER_VAR = millis(); \
        CODE \
    }
