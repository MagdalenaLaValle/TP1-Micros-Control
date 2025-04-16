//Librerías
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "stdlib.h"

//MACROS
//Establecemos la cantidad de caracteres en el buffer con el nomrbe del usuario.
#define _MaxCaract 30 

//Definimos una macro que pasa a mayúsculas los caracteres en minúscula.
#define paso_mayus(x) ('a'<= x  && x<= 'z' ) ? (x -= ('a' - 'A')) : x 

//Definimos valores para reconocer los errores. 
typedef enum{ 
    _SI_ERROR = 1,
    _NO_ERROR = 0
}error_t; 

//Handler
//Definimos una función que al recibir una señal determinada finalice el programa. 
void handler_sig( int señal){
    printf("\nFinalizo el programa. \n");
    exit(0);
}

//PROTOTIPOS DE FUNCIONES
error_t check_error (char *pc);

//PROGRAMA PRINCIPAL
int main (void){
    char ingreso[_MaxCaract]={0}; //Buffer en donde se almacena el stirng ingresado por el usuario
    error_t tiene_error = _NO_ERROR; //Variable tipo error_t para detectar cuando hay un error en el string ingresado. 
    int i; //Índice de iteración para los bucles for.

    signal(SIGINT, handler_sig);

    while(1){
        //Solicitamos el nombre al usuario
        printf("\nIngrese su nombre: \t");
        fflush(stdin);
        fgets(ingreso, _MaxCaract, stdin);

        //Evaluamos que no haya errores de ingreso por medio de la función check_error.
        tiene_error = check_error (ingreso);

        if (tiene_error == _SI_ERROR){ //Si hay errores, no imprime nada y reinicia el bucle. 
            printf("\nERROR\n");
        }
        else{ //Si no hay errores, se imprimirá el nombre en mayúsculas. 
            printf("\nNombre en mayusculas: \t");
            for (i=0; i<_MaxCaract &&ingreso[i]!='\n'; i++){
                paso_mayus(ingreso[i]);
                printf("%c", ingreso[i]);
            }
        }
    }
}


//FUNCIONES 
//Función de detección de errores. 
error_t check_error (char *pc){
    int i; //índice de iteración para el bucle for. 
    error_t tiene_error = _NO_ERROR; 
    for (i=0; i<_MaxCaract && *pc != '\n'; i++, *pc++){ //Se recorre el string ingresado caracter por caracter. 
        if(!((*pc>='a' && *pc<='z') || (*pc>='A' && *pc<='Z') || *pc== ' ')){ 
            //Si se encuentra un caracter que no es un letra o un espacio, significa que hay un error
            tiene_error = _SI_ERROR;
            break;
        }
    }
    return tiene_error;
}