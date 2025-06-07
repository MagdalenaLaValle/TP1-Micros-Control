/* Creo una libreria de vectores */

/* librerias */
#include "vectores.h"

/* prototipos*/
void imprimir_vector(vector_t *v);
double norma_2(vector_t *vec);
vector_t Suma(vector_t *vec1, vector_t *vec2);
float Producto_Interno(vector_t *v1, vector_t *v2);
vector_t Producto_Externo(vector_t *v1,vector_t *v2);
vector_t Escalar(vector_t *v,float lambda);
vector_t Resta(vector_t *v1, vector_t *v2);


vector_t inicializar_vector(float x, float y, float z){
    vector_t vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.norma = norma_2;
    vec.imprimir = imprimir_vector;
    vec.Adicion = Suma;
    vec.producto_interno = Producto_Interno;
    vec.producto_X = Producto_Externo;
    vec.Escalar = Escalar;
    vec.Resta = Resta;
    return vec;    
}

double norma_2(vector_t *vec){
    return sqrt(pow(vec->x,2) + pow(vec->y,2) + pow(vec->z,2));
}

void imprimir_vector(vector_t *v){ 
    printf(" ( %.2f, %.2f, %.2f)", v->x,v->y,v->z);
}
/* funciones */



vector_t Suma(vector_t *vec1, vector_t *vec2){
    vector_t vec_resultado;
    float x,y,z;
    x = vec1->x + (vec2->x);
    y = vec1->y + (vec2->y);
    z = vec1->z + (vec2->z);
    vec_resultado = inicializar_vector(x,y,z);
    return vec_resultado;
}

vector_t Escalar(vector_t *v, float k){
    vector_t vec = inicializar_vector(k*(v->x),k*(v->y),k*(v->z));
    return vec;
}

vector_t Resta(vector_t *v1, vector_t *v2){
    vector_t aux = Escalar(v2,-1);
    return Suma(v1,&aux);
}

float Producto_Interno(vector_t *v1, vector_t *v2){
    return (v1->x)*(v2->x) + (v2->y)*(v1->y) + (v1->z)*(v2->z);
}

vector_t Producto_Externo(vector_t *v1,vector_t *v2){
    vector_t vec_resultante;
    float x,y,z;
    x = (v1->y)*(v2->z) - (v1->z)*(v2->y);
    y = (v1->x)*(v2->z) - (v1->z)*(v2->x);
    z = (v1->x)*(v2->y) - (v2->x)*(v1->y);
    vec_resultante = inicializar_vector(x,y,z);
    return vec_resultante;
}


