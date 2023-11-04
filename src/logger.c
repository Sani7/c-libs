/**
 * @file log.c
 * @brief Logger implementation
 * @author Lorenz C. && Speetjens S.
 */

#include <stdint.h>
#include <stdio.h>
#include "logger.h"

uint32_t logger_get_timestamp(clock_t* start) {
    clock_t t1 = clock();
    return (uint32_t)((t1 - *start) * 1000 / CLOCKS_PER_SEC);
}