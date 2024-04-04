/*
 * Copyright (C) 2022 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>

#include "board.h"
#include "ztimer.h"
#include "periph/gpio.h"

/* [TASK 1: define led0 here] */

/* [TASK 2: define button and led1 here] */

/* [TASK 2: write the callback function here] */


int main(void)
{
    /* Sleep so that we do not miss this message while connecting */
    ztimer_sleep(ZTIMER_MSEC, 3000);
    puts("GPIOs example.");

    /* [TASK 1: initialize and use led0 here] */

    return 0;
}
