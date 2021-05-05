#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
/*==================[definiciones y macros]==================================*/
#define EVIDENCIAR_PROBLEMA 0

#if EVIDENCIAR_PROBLEMA==1
#define CRITICAL_DECLARE
#define CRITICAL_CONFIG
#define CRITICAL_START
#define CRITICAL_END
#else
#include "freertos/semphr.h"
#define CRITICAL_DECLARE    SemaphoreHandle_t mutex
#define CRITICAL_CONFIG     mutex = xSemaphoreCreateMutex()
#define CRITICAL_START      xSemaphoreTake( mutex , portMAX_DELAY )
#define CRITICAL_END        xSemaphoreGive( mutex )
#endif

/*==================[declaraciones de funciones]====================*/
CRITICAL_DECLARE;

// Prototipo de funcion de la tarea
void tareaA( void* parametroTarea );
void tareaB( void* parametroTarea );

/*==================[funcion principal]======================================*/

void app_main()
{
    BaseType_t res;

    // ---------- CONFIGURACIONES ------------------------------

    res = xTaskCreatePinnedToCore (
              tareaA,                     // Funcion de la tarea a ejecutar
              ( const char * )"Tarea A",   	// Nombre de la tarea como String amigable para el usuario
              configMINIMAL_STACK_SIZE*2, 	// Cantidad de stack de la tarea
              NULL,                          	// Parametros de tarea
              tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
              NULL,                          		// Puntero a la tarea creada en el sistema
              0
          );

    configASSERT( res == pdPASS ); // gestion de errores

    res = xTaskCreatePinnedToCore (
              tareaB,                     // Funcion de la tarea a ejecutar
              ( const char * )"Tarea B",   	// Nombre de la tarea como String amigable para el usuario
              configMINIMAL_STACK_SIZE*2, 	// Cantidad de stack de la tarea
              NULL,                          	// Parametros de tarea
              tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
              NULL,                          		// Puntero a la tarea creada en el sistema
              1
          );

    configASSERT( res == pdPASS ); // gestion de errores

    CRITICAL_CONFIG;
}

/*==================[definiciones de funciones]=====================*/

// Implementacion de funcion de la tarea
void tareaA( void* parametroTarea )
{
    while( true )
    {
        CRITICAL_START; //abrir seccion critica
        printf( "Hola, soy la tarea A " );
        printf( "y estoy ejecuntadome en el procesador numero 0\n" );
        CRITICAL_END;	//cerrar seccion critica

        vTaskDelay( 1 / portTICK_RATE_MS );
    }
}

void tareaB( void* parametroTarea )
{
    while( true )
    {
        CRITICAL_START; //abrir seccion critica
        printf( "Hola, soy la tarea B " );
        printf( "y estoy ejecuntadome en el procesador numero 1\n" );
        CRITICAL_END;	//cerrar seccion critica

        vTaskDelay( 1 / portTICK_RATE_MS );
    }
}

void tarea(){

    while( true )
    {
        printf( "Hola, soy la tarea B " );
        printf( "y estoy ejecuntadome en el procesador numero 1\n" );

        vTaskDelay( 1 / portTICK_RATE_MS );
    }
}