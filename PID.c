/*
 * PID.c
 *
 *  Created on: Sep 17, 2018
 *      Author: Mourad-Rashwan
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "PID_driver.h"

void PID_init(PIDobject_t *ptPIDobject, PIDmode_t tPIDmode, PIDgain_t tPIDgain,
              PIDoutBound_t tPIDoutBound)
{
    ptPIDobject->dActualVal = 0;
    ptPIDobject->dDesiredVal = 0;
    ptPIDobject->dLastError = 0;
    ptPIDobject->dPIDout = 0;
    ptPIDobject->dSumError = 0;
    ptPIDobject->tPIDmode = tPIDmode;
    ptPIDobject->tPIDgain = tPIDgain;
    ptPIDobject->tPIDoutBound = tPIDoutBound;
}

void PID_update(PIDobject_t *ptPIDobject, float dPeriodInSec)
{
    float dCurrentError = ptPIDobject->dDesiredVal - ptPIDobject->dActualVal;

    ptPIDobject->dSumError += dCurrentError;

    switch (ptPIDobject->tPIDmode)
    {
    case MODE_P:
        ptPIDobject->dPIDout = (ptPIDobject->tPIDgain.dKP * dCurrentError);
        break;

    case MODE_PI:
        ptPIDobject->dPIDout = (ptPIDobject->tPIDgain.dKP * dCurrentError)
                + (ptPIDobject->tPIDgain.dKI * ptPIDobject->dSumError
                        * dPeriodInSec);
        break;

    case MODE_PD:
        ptPIDobject->dPIDout = (ptPIDobject->tPIDgain.dKP * dCurrentError)
                + ((ptPIDobject->tPIDgain.dKD
                        * (dCurrentError - ptPIDobject->dLastError))
                        / dPeriodInSec);
        break;

    case MODE_PID:
        ptPIDobject->dPIDout = (ptPIDobject->tPIDgain.dKP * dCurrentError)
                + (ptPIDobject->tPIDgain.dKI * ptPIDobject->dSumError
                        * dPeriodInSec)
                + ((ptPIDobject->tPIDgain.dKD
                        * (dCurrentError - ptPIDobject->dLastError))
                        / dPeriodInSec);
        break;

    default:
        break;
    }

    if (ptPIDobject->dPIDout < ptPIDobject->tPIDoutBound.dOutMin)
    {
        ptPIDobject->dPIDout = ptPIDobject->tPIDoutBound.dOutMin;
        ptPIDobject->dSumError -= dCurrentError; /* Wind-up protection (stop updating dSumError) */
    }
    else if (ptPIDobject->dPIDout > ptPIDobject->tPIDoutBound.dOutMax)
    {
        ptPIDobject->dPIDout = ptPIDobject->tPIDoutBound.dOutMax;
        ptPIDobject->dSumError -= dCurrentError; /* Wind-up protection (stop updating dSumError) */
    }
    else
    {

    }

    ptPIDobject->dLastError = dCurrentError;
}

void PID_reset(PIDobject_t *ptPIDobject)
{
    ptPIDobject->dLastError = 0;
    ptPIDobject->dPIDout = 0;
    ptPIDobject->dSumError = 0;
}

void PID_setMode(PIDobject_t *ptPIDobject, PIDmode_t tPIDmode)
{
    ptPIDobject->tPIDmode = tPIDmode;
}

PIDmode_t PID_getMode(PIDobject_t *ptPIDobject)
{
    return ptPIDobject->tPIDmode;
}

void PID_setGain(PIDobject_t *ptPIDobject, PIDgain_t tPIDgain)
{
    ptPIDobject->tPIDgain = tPIDgain;
}

PIDgain_t PID_getGain(PIDobject_t *ptPIDobject)
{
    return ptPIDobject->tPIDgain;
}

void PID_setOutBound(PIDobject_t *ptPIDobject, PIDoutBound_t tPIDoutBound)
{
    ptPIDobject->tPIDoutBound = tPIDoutBound;
}

PIDoutBound_t PID_getOutBound(PIDobject_t *ptPIDobject)
{
    return ptPIDobject->tPIDoutBound;
}

float PID_getOut(PIDobject_t *ptPIDobject)
{
    return ptPIDobject->dPIDout;
}

void PID_setActualVal(PIDobject_t *ptPIDobject, float dActualVal)
{
    ptPIDobject->dActualVal = dActualVal;
}

float PID_getActualVal(PIDobject_t *ptPIDobject)
{
    return ptPIDobject->dActualVal;
}

void PID_setDesiredVal(PIDobject_t *ptPIDobject, float dDesiredVal)
{
    ptPIDobject->dDesiredVal = dDesiredVal;
}

float PID_getDesiredVal(PIDobject_t *ptPIDobject)
{
    return ptPIDobject->dDesiredVal;
}

