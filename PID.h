/*
 * PID.h
 *
 *  Created on: Sep 17, 2018
 *      Author: Mourad-Rashwan
 */

#ifndef PID_H_
#define PID_H_

typedef enum PIDmode
{
    MODE_P, MODE_PI, MODE_PD, MODE_PID
} PIDmode_t;

typedef struct PIDgain
{
    float dKP, dKI, dKD;
} PIDgain_t;

typedef struct PIDoutBound
{
    float dOutMin, dOutMax;
} PIDoutBound_t;

typedef struct PIDobject
{
    float dPIDout;
    float dActualVal, dDesiredVal;
    float dLastError, dSumError;
    PIDmode_t tPIDmode;
    PIDgain_t tPIDgain;
    PIDoutBound_t tPIDoutBound;
} PIDobject_t;

void PID_init(PIDobject_t *ptPIDobject, PIDmode_t tPIDmode, PIDgain_t tPIDgain,
              PIDoutBound_t tPIDoutBound);

void PID_update(PIDobject_t *ptPIDobject, float dPeriodInSec); /* [PERIODIC] Make sure it will run every dPeriodInSec */

void PID_reset(PIDobject_t *ptPIDobject);

void PID_setMode(PIDobject_t *ptPIDobject, PIDmode_t tPIDmode);

PIDmode_t PID_getMode(PIDobject_t *ptPIDobject);

void PID_setGain(PIDobject_t *ptPIDobject, PIDgain_t tPIDgain);

PIDgain_t PID_getGain(PIDobject_t *ptPIDobject);

void PID_setOutBound(PIDobject_t *ptPIDobject, PIDoutBound_t tPIDoutBound);

PIDoutBound_t PID_getOutBound(PIDobject_t *ptPIDobject);

float PID_getOut(PIDobject_t *ptPIDobject);

void PID_setActualVal(PIDobject_t *ptPIDobject, float dActualVal);

float PID_getActualVal(PIDobject_t *ptPIDobject);

void PID_setDesiredVal(PIDobject_t *ptPIDobject, float dDesiredVal);

float PID_getDesiredVal(PIDobject_t *ptPIDobject);

#endif /* PID_H_ */
