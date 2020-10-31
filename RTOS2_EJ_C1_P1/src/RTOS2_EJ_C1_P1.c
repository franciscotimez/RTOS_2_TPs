/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/10/30
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "RTOS2_EJ_C1_P1.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"


#include "sapi.h"
#include "userTasks.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   boardInit();

   iniciar_teclas();

   // Inicio la cola para enviar el mensaje
   cola_1 = xQueueCreate( 5 , sizeof(void *) );

   // Creo las tareas
   	crear_tarea(Tarea_A, "Tarea_A", NULL);
   	crear_tarea(Tarea_B, "Tarea_B", teclas_g);
   	crear_tarea(Tarea_C, "Tarea_C", NULL);

   vTaskStartScheduler(); // Initialize scheduler

   while( true ); // If reach heare it means that the scheduler could not start

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
