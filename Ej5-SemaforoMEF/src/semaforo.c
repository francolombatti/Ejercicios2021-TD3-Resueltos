#include "../include/led.h"
#include "../include/semaforo.h"

// Tipo de datos para la variable de estados
typedef enum{
    ROJO,
    ROJO_AMARILLO,
    VERDE,
    AMARILLO
} estadoMEF_t;

// Variable de estado (global)
estadoMEF_t estadoActual;
int contador;
// Función Inicializar MEF
void iniciarSemaforo(void){
	 estadoActual = ROJO;
	 contador = 0;
    // Resto de la inicializacion
}


// Función Actualizar MEF
void actualizarSemaforo(void)
{
	switch (estadoActual) {
		case ROJO:
        {
            // Actualizar salida del estado
			prenderLed("Rojo");
			apagarLed("Amarillo");
			apagarLed("Verde");
    		// Chequear condiciones de transición de estado
			if(contador == 60 ){
				// Cambiar a otro estado
				 estadoActual = ROJO_AMARILLO;
				 contador = 0;
			}
			contador++;
		}
		break;
		case ROJO_AMARILLO:{
			// Actualizar salida del estado
			prenderLed("Rojo");
			prenderLed("Amarillo");
			apagarLed("Verde");
    		// Chequear condiciones de transición de estado
			if(contador == 10 ){
				// Cambiar a otro estado
				 estadoActual = VERDE;
				 contador = 0;
			}
			contador++;
		}
		break;
		case VERDE:{
			// Actualizar salida del estado
			apagarLed("Rojo");
			apagarLed("Amarillo");
			prenderLed("Verde");
    		// Chequear condiciones de transición de estado
			if(contador == 30 ){
				// Cambiar a otro estado
				 estadoActual = AMARILLO;
				 contador = 0;
			}
			contador++;
		}
		case AMARILLO:{
			// Actualizar salida del estado
			apagarLed("Rojo");
			apagarLed("Amarillo");
			prenderLed("Verde");
    		// Chequear condiciones de transición de estado
			if(contador == 10 ){
				// Cambiar a otro estado
				 estadoActual = ROJO;
				 contador = 0;
			}
			contador++;
		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
			InicializarMEF();
		}
		break;
	}	
}