/* Librerias */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* Definiciones y Macros*/
#define CANTIDAD (uint8_t) 3 // Cantidad de numeros a los cuales tomare el promedio
#define BUFFER (uint8_t) 20 // Buffer del teclado
#define VALIDO (uint8_t) 0 // Definiciones de lo que tomo como invalido o valido
#define INVALIDO (uint8_t) 1

/* Prototipos */
uint8_t Es_Valido(char c[BUFFER]); //Funcion que valida strings
float Promedio(int vec[CANTIDAD],int cant); //funcion promediadora

/*Main*/

int main(){
    char c[BUFFER] = ""; // En esta variable guardare lo ingresado por teclado, la inicializo para entrar en el while
    int vec[CANTIDAD],cant=0; //Los numeros los guardo en un vector para mantener el orden, utilizo cant para saber cuantos numeros,
                              //fueron ingresados hasta el momento
    float promedio = 0; 
    /* inicializo el vector en cero */
    for(int i=0;i<CANTIDAD;i++){
        vec[i] = 0;
    }

    while(strcmp(c,"EXIT") != 0){ //mientras que c no sea EXIT estara dentro del while
        // lo consideramos case sensitive, es decir solo toma EXIT, no eXiT ni exit ni ninguna otra combinacion
        printf("Ingrese numeros enteros y se calculara el promedio de los ultimos %d numeros ingresados\n", CANTIDAD);
        printf("Para salir ingrese EXIT\n");
        fflush(stdin); //limpio el buffer del teclado
        fgets(c, BUFFER, stdin);
        for(int i=0; i<BUFFER; i++){// cambio el enter por un 0 para que pueda ser comparado por strcmp
            if(c[i] == '\n'){
                c[i] = '\0';
            }
        }
        /*Si lo ingresado por teclado no es un numero ni EXIT, entrara en un ciclo hasta que se ingresen valores VALIDOS*/
        while(Es_Valido(c) == INVALIDO){
            printf("Ha ingresado un caracter no valido y no sera tenido en cuenta.\nPor favor vuelva a ingresar valores o EXIT: \n");
            fflush(stdin); 
            fgets(c,BUFFER,stdin);
            for(int i=0; i<BUFFER; i++){
                if(c[i] == '\n'){
                    c[i] = '\0';
                }
            }
            
        }
        /* Una vez que se verifico que no se trata de un caracter invalido, calculo el promedio*/
        if(Es_Valido(c)== VALIDO){
            cant+=1;
            //Para los primeros valores calculo el promedio sobre la cantidad ingresada hasta el momento
            //Una vez superado DIGITOS (10 en el ejercicio) empiezo a caclular el promedio sobre los ultimos DIGITOS ingresados
            if(cant > CANTIDAD){
                // Una vez que la cantidad de numeros a promediar se vuelve fija, puedo calcular el promedio de una manera mucho mas
                // simple, solo teniendo en cuenta el valor entrante y el saliente
                promedio = promedio - (float)vec[0]/CANTIDAD + (float)atoi(c)/CANTIDAD; 
                // Reordeno el vector y me deshago del valor mas viejo
                for(int i= 0;i < CANTIDAD;i++){
                    vec[i] = vec[i+1];
                }
                // Guardo el valor mas nuevo
                vec[CANTIDAD - 1] = atoi(c);
                for(int i=0;i<CANTIDAD;i++){
                    printf("%d \t", vec[i]);
                }
                printf("\n");
                // Imprimo por pantalla
                printf("El promedio es: %f \n",promedio);
            }
            if(cant <= CANTIDAD){
                // reordeno el vector
                for(int i= 0;i < CANTIDAD;i++){
                    vec[i] = vec[i+1];
                }
                // le asigno el ultimo valor ingresado al ultimo espacio del vector
                vec[CANTIDAD-1] = atoi(c);
                // Imprimo el vector para verificar que se haya ingresado correctamente
                for(int i=0;i<CANTIDAD;i++){
                    printf("%d \t", vec[i]);
                }
                printf("\n");
                // Calculo el promedio e imprimo por pantalla
                promedio=Promedio(vec, cant);
                printf("El promedio es: %f \n",promedio);
            }
            
        }

    }
    // Si selecciono EXIT se termina el programa
    if(strcmp(c,"EXIT") == 0 ){
        printf("Se ha seleccionado EXIT \n**** Fin del Programa ****");
        return 0;
    }
    return 0;
}

float Promedio(int vec[CANTIDAD],int cant){
    float prom =0;
    // El promedio lo calculo de atras hacia adelante, de manera tal que siempre tenga en cuenta los valores mas nuevos
    for(int i =CANTIDAD - 1; i >= CANTIDAD-cant; i--){
        prom += vec[i];
    }
    return (float)prom/cant;
}

// Funcion que verifica si lo ingresado por teclado es valido
uint8_t Es_Valido(char c[BUFFER]){
    int inicio = 0;
    int index;
    // como antes cambie el \n del teclado por un \0 al final, si el usuario simplemente presiona enter
    // lo tomo como invalido
    if(c[0]== '\0'){
        return INVALIDO;
    }
    // Como el - es un caracter valido dependiente unicamente de la posicion, si lo encuentro al inicio arranco a 
    // contar una posicion por delante. Luego lo tomare como un caracter invalido
    // De esta manera, evito que se tome por ejemplo 12-2 como un numero valido pero que si se tome a -122 como valido
    if (c[0] == '-' ){
        inicio = 1;
    }
    for(index = inicio; index < BUFFER && c[index] != '\0'; index++){
        //si encuentro un caracter que no es un numero y que la palabra no se trata de EXIT retorno INVALIDO
        if((c[index] < '0' || c[index] > '9') && (strcmp(c,"EXIT") !=0)){
            return (uint8_t) INVALIDO;
        }
    }
    // para cualquier otro caso retorno valido
    return (uint8_t) VALIDO;
}