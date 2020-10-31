/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/10/30
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "fsm_debounce.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdlib.h>
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
// Vector de teclas
static gpioMap_t teclas[] 		= {TEC1, TEC2};

#define N_TECLAS sizeof(teclas)/sizeof(gpioMap_t)		// 4 * (gpioMap_t / gpioMap_t) = 4

tLedTecla teclas_g[N_TECLAS];

QueueHandle_t cola_1;

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/
void crear_tarea(TaskFunction_t tarea, const char * const Nombre, void * const parametros);
void iniciar_teclas();
void Tarea_A( void* taskParmPtr );  // Task declaration
void Tarea_B( void* taskParmPtr );  // Task declaration
void Tarea_C( void* taskParmPtr );  // Task declaration

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __USER_TASKS_H__ */
