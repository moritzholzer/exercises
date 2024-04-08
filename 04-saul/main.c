/*
 * Copyright (C) 2022 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>

#include "ztimer.h"
#include "phydat.h"
#include "saul_reg.h"
#include "board.h"

#define TEMPERATURE_THRESHOLD 2400 /* factor of 10^-2 */

int main(void)
{
    /* Sleep so that we do not miss this message while connecting */
    ztimer_sleep(ZTIMER_MSEC, 3000);
    puts("SAUL example application");

    /* start by finding a temperature sensor in the system */
    saul_reg_t *temp_sensor = saul_reg_find_type(SAUL_SENSE_TEMP);
    if (!temp_sensor) {
        puts("No temperature sensor present");
        return 1;
    }
    else {
        printf("Found temperature device: %s\n", temp_sensor->name);
    }

    /* [TASK 3: find your device here] */
    saul_reg_t *accel_sensor = saul_reg_find_type(SAUL_SENSE_ACCEL);
    /* record the starting time */
    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);
    int before = 0;
    while (1) {
        /* read a temperature value from the sensor */
        phydat_t temperature;
        int dimensions = saul_reg_read(temp_sensor, &temperature);
        if (dimensions < 1) {
            puts("Error reading a value from the device");
            break;
        }

        /* dump the read value to STDIO */
        phydat_dump(&temperature, dimensions);

        /* [TASK 3: perform the acceleration read here ] */

        /* check if the temperature value is above the threshold */
        if (temperature.val[0] >= TEMPERATURE_THRESHOLD) {
            LED0_ON;
        }
        else {
            LED0_OFF;
        }
        
        phydat_t acceleration;
        int acc_dim = saul_reg_read(accel_sensor, &acceleration);
        if (acc_dim < 1) {
            puts("Error reading a value from the device");
        break;
        }
        int diff = before - acceleration.val[2];
        before = acceleration.val[2];
        phydat_dump(&acceleration, acc_dim);   
        
        if(diff <= 100 && diff >=-100){
            LED1_ON;
        }else{
            LED1_OFF;
        }
        /* wait for 500 ms */
        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 500);
    }

    return 0;
}
