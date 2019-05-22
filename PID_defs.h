/*
 * PID_defs.h
 *
 *  Created on: Mar 7, 2019
 *      Author: Administrator
 */

#ifndef PID_DEFS_H_
#define PID_DEFS_H_

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

#endif /* PID_DEFS_H_ */
