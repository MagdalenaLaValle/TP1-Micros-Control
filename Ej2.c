 //LIBRERÍAS
 #include "stdio.h"
 #include "stdlib.h"
 
 //Definición de un alias para poder identificar los errores
 typedef enum{ 
    _SI_ERROR = 1,
    _NO_ERROR = 0
}error_t; 

 //PROTOTIPOS DE FUNCIONES
 error_t revision_errores(char *pIngresado);
 int ordenamiento(int *pv, int len);
 
 //MACROS
 #define long_teclado 100 //Tamaño del buffer que almacena el string ingresado por el usuario.
 #define cant_numeros 10 //Máxima cantidad de números a ingresar. 
 #define max_digitos 3 //Máxima cantidad de dígitos que puede tene runo de los números. 
 
 //PROGRAMA PRINCIPAL 
 int main(void){
     char ingresado[long_teclado]={0}; //Buffer en el que se almacenará el string ingresado por teclado. 
     char numero_char[max_digitos+1]={0}; //String de manor tamaño en donde se almacenen de forma transitoria los números en tipo char.
     int i; //Índice para iteración en los bucles for
     int pos_char=0; //índice para indicar cómo almacenar los caracteres en numero_char 
     int numero_int; //Variable en donde se almacenan transitoriamente los números ingresados, ya pasados a tipo int. 
     int count_numeros=0; //Contador para determinar la cantidad de números ingresados (podrían ser 100 o menos)
     error_t tiene_errores; //Identificador de errores.
     static int vector_numeros[cant_numeros]; //Vector en donde almacenan los números ingresados en tipo int
     int suma; //Variable para sumar los números ingresados
     double promedio; //Variable para almacenar el promedio de los números ingresados. 

     
     //Solicitamos al usuario que ingrese los números
     printf("Introduzca %d numeros enteros. No deben tener mas de %d digitos. Separe cada numero por una coma \n", cant_numeros, max_digitos);
     fflush(stdin); 
     fgets(ingresado, long_teclado, stdin);
     
     //Se verifica que no haya errores. 
     tiene_errores= revision_errores(ingresado);

     //Se vuelve a solicitar que se ingresen los números hasta que no haya errores. 
     while (tiene_errores == _SI_ERROR){
        printf("Intente de nuevo:\n");
        fflush(stdin);  
        fgets(ingresado, long_teclado, stdin);
        tiene_errores= revision_errores(ingresado);
     }
    
    //Recorremos el buffer y extraemos los números 
    for (i=0; i< long_teclado; i++){ 
        if(ingresado[i]<='9' && ingresado[i]>='0'){ 
            //Si el caracter es un número, lo almacenamos en este nuevo caracter 
            numero_char[pos_char]=ingresado[i];
            pos_char+=1; 
        }
        else{ 
            //Al llegar a una coma o \n se interpreta que terminó el número, se pasa todo el número a tipo int y se vuelve a inicializar numero_char para el siguiente número 
            //Esto se puede hacer de esta manera porque ya se revisó previamente que no haya errores.
            numero_char[pos_char]= '\0'; //Establecemos el caracter después del último dígito como caracter de terminación 
            numero_int=atoi(numero_char); //Pasamos el número a entero
            vector_numeros[count_numeros]=numero_int; //Se almacenan los números en un vector para su posterior ordenamiento. 
            suma+=numero_int; //Sumamos todos los ingresados
            pos_char=0; //Volvemos a iniciar la posición en numero_char como 0 para poder trabajar con el siguiente número
            count_numeros++; //Contamos cuántos números se ingresaron. 
        }
        if (ingresado[i]=='\n'){
            //Al llegar al enter, se interpreta que terminó el string ingresado y se detiene el bucle. 
            break;
        }
    }
    //Calculamos el promedio 
    printf("\nSUMA=%d\n", suma);    
    promedio=(double)suma/count_numeros;
    printf("El promedio es %.2f \n", promedio);

    //Realizamos el ordenamiento del vector. 
    ordenamiento(vector_numeros, count_numeros);
    return 0;
 }
 
//FUNCIONES
//Función de detección de errores
 error_t revision_errores(char *pIngresado) {
     error_t error= _NO_ERROR; 
     int i, digitos=1, numeros=0;

    //Iteramos sobre cada unuo de los caracteres
     for (i=0; i< long_teclado && *(pIngresado + i)!='\n'; i++){
         if(*(pIngresado +i)!=44 && (57 < *(pIngresado + i) || *(pIngresado + i)<48)){
            //Si el caracter no es un número ni una coma, marca eror
            error=1;
            printf("ERROR. Solo puede ingresar caracteres de tipo: digitos 0-9 o coma.\n");
            break;
         }

        //Evaluación de la cantidad de números y dígitos sea la correcta
        if('0'< *(pIngresado + i) && *(pIngresado + i)<'9'){
            digitos++;
         }
        if (*(pIngresado + i)==','){
            //Al llegar a una coma, se interpreta que terminó un número. 
            digitos=0; 
            numeros++; 
        }
        if(digitos==4){
            error=_SI_ERROR;
            printf("ERROR. Los numeros no deben tener mas de tres digitos.\n");
            break;
        }  
        if(numeros>cant_numeros){
            error=_SI_ERROR;
            printf("ERROR. Solo puede ingresar un maximo de 10 numeros\n");
            break;
        }

        //Revisamos que no haya dos comas seguidas 
        if(*(pIngresado + i)==',' && *(pIngresado + i + 1)==','){
            error=_SI_ERROR;
            printf("ERROR. Cada numero debe estar separado por una unica coma\n");
            break;
        }
     }
     return error;
 }


//Función de ordenamiento del vector
int ordenamiento(int *pv, int len){
    int m, c; //índices de iteración
    int aux; //Variable auxiliar donde guardar los valores temporalmente al hacer el ordenamiento. 
    int *pcopy=pv; //Almacenamos el valor original del puntero 

    //Ordenamiento de tipo BubbleSort 
    for(c=0; c < len-1; c++){
        for(m=0; m<(len-c-1) ; m++, pv++){
            if (*(pv) > *(pv+1)){
                //Si un número es mayor al número que le sigue, se intercambian sus posiciones.
                aux = *(pv);
                *(pv) = *(pv+1);
                *(pv+1) = aux;
            } 
        }
        pv=pcopy; //Al final de cada iteración, regresamos el puntero a su valor original para volver al inicio del array
    }
    
    //Imprimimos el vector ordenado
    printf("\nNumeros ingresados de menor a mayor\n");
    for(m=0; m<len ;m++){
        printf("%d,",*(pcopy+m));
    }
 }