
#include "vectores.h"

int main(){
    vector_t v1,v2,vec;
    double n;
    int a;
    v1 = inicializar_vector(1,-5,13);   
    v2 = inicializar_vector(-5,7,-1);
    printf("V1 =");
    v1.imprimir(&v1);
    printf("\n");
    printf("V2 =");
    v2.imprimir(&v2);
    printf("\n");
    n = v1.norma(&v1);
    printf("||");
    v1.imprimir(&v1);
    printf("|| =");
    printf(" %f\n", n);
    vec = v1.Adicion(&v1,&v2);
    v1.imprimir(&v1);
    printf(" +");
    v2.imprimir(&v2);
    printf(" =");
    vec.imprimir(&vec);
    printf("\n");
    vec = v1.Resta(&v1,&v2);
    v1.imprimir(&v1);
    printf(" -");
    v1.imprimir(&v2);
    printf(" =");
    vec.imprimir(&vec);
    printf("\n");
    a = v1.producto_interno(&v1, &v2);
    v1.imprimir(&v1);
    printf(" . ");
    v2.imprimir(&v2);
    printf(" = %d", a);
    printf("\n");
    vec = v1.producto_X(&v1, &v2);
    v1.imprimir(&v1);
    printf(" x ");
    v2.imprimir(&v2);
    printf(" =");
    vec.imprimir(&vec);
    printf("\n");
   
  

    return 0;
}