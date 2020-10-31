/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/10/30
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/
#define LED_BLINK LEDB
#define LED_ERROR LEDR

#define	PERIODO_MS		3000
#define	PERIODO			pdMS_TO_TICKS(PERIODO_MS)
/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

void crear_tarea(TaskFunction_t tarea, const char * const Nombre, void * const parametros)
{
	BaseType_t res;
	// Crear tarea para recepcion UART
	res = xTaskCreate(
			tarea,                  		// Funcion de la tarea a ejecutar
			( const char * ) Nombre, 		// Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE*3,   	// Cantidad de stack de la tarea
			parametros,                     // Parametros de tarea
			tskIDLE_PRIORITY+1,           	// Prioridad de la tarea
			0                             	// Puntero a la tarea creada en el sistema
	);

	// Gestion de errores
	if(res == pdFAIL)
	{
		gpioWrite( LED_ERROR, ON );
		printf( "Error al crear las tareas. \n\r" );
		while(TRUE);						// VER ESTE LINK: https://pbs.twimg.com/media/BafQje7CcAAN5en.jpg
	}

	return;
}

void iniciar_teclas()
{
	for(uint32_t i = 0 ; i < N_TECLAS ; i++)
	{
		teclas_g[i].tecla = teclas[i];
	}
	return;
}

// Task implementation
void Tarea_A( void* taskParmPtr )
{
	// ---------- CONFIGURACIONES ------------------------------
	TickType_t xPeriodicity =  PERIODO;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	// ---------- REPETIR POR SIEMPRE --------------------------
	char * msj;

	while( TRUE )
	{
		// Envio mensaje a la cola
		msj = malloc(7);
		sprintf(msj, "LED ON");

		xQueueSend( cola_1 , &msj,  0 );			// Esperamos tecla

		gpioWrite( LED_BLINK , ON );
		vTaskDelay( PERIODO / 2 );

		gpioWrite( LED_BLINK , OFF );

		vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
	}
}

// Task implementation
void Tarea_B( void* pvParameters )
{
	tLedTecla* tecla_l = (tLedTecla*) pvParameters;

	fsmButtonInit( tecla_l, N_TECLAS );			// Inicio la FSM

	while( TRUE )
	{
		fsmButtonUpdate( tecla_l, N_TECLAS  );	// Actualizo la FSM
		vTaskDelay( 0 );						// Forzar cambio de contexto
	}
}

// Task implementation
void Tarea_C( void* taskParmPtr )
{
	uartInit( UART_USB, 115200 );

	char *buffer;

	while( TRUE ){
		if(xQueueReceive(cola_1, &buffer, portMAX_DELAY) == pdPASS)
		{

			taskENTER_CRITICAL();
			uartWriteString( UART_USB, buffer );
			taskEXIT_CRITICAL();

			free(buffer);//libero el espacio de memoria ocupado por el puntero recibido
		}
	}
}
/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

