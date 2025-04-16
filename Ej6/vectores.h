#ifndef VECTORES_H
#define VECTORES_H


#include <math.h>
#include <stdio.h>

#define SUMA 1
#define RESTA -1


typedef struct vector_s{
    float x;
    float y;
    float z;
    void (*imprimir)(struct vector_s *v);
    double (*norma)(struct vector_s *v);
    struct vector_s (*Adicion)(struct vector_s *v1,struct vector_s *v2);
    float (*producto_interno)(struct vector_s *v1,struct vector_s *v2);
    struct vector_s (*producto_X)(struct vector_s *v1, struct vector_s *v2);     
}vector_t;

/* prototipos */
vector_t inicializar_vector(float x, float y, float z);
/* prototipos */

#endif 