
#include "vectores.h"

int main(){
    vector_t v1,v2,vec;
    double n;
    int a;
    v1 = inicializar_vector(1,-5,13);   
    v2 = inicializar_vector(-5,7,-1);
    printf("V1 =");
    imprimir_vector(&v1);
    printf("\n");
    printf("V2 =");
    imprimir_vector(&v2);
    printf("\n");
    n = v1.norma(v1.x,v1.y,v1.z);
    printf("||");
    imprimir_vector(&v1);
    printf("|| =");
    printf(" %f\n", n);
    vec = Adicion(&v1, SUMA,&v2);
    imprimir_vector(&v1);
    printf(" +");
    imprimir_vector(&v2);
    printf(" =");
    imprimir_vector(&vec);
    printf("\n");
    vec = Adicion(&v1, RESTA,&v2);
    imprimir_vector(&v1);
    printf(" -");
    imprimir_vector(&v2);
    printf(" =");
    imprimir_vector(&vec);
    printf("\n");
    a = Producto_Interno(&v1,&v2);imprimir_vector(&v1);
    printf(" . ");
    imprimir_vector(&v2);
    printf(" = %d",a);
    printf("\n");
    vec = Producto_Externo(&v1,&v2);
    imprimir_vector(&v1);
    printf(" x ");
    imprimir_vector(&v2);
    printf(" =");
    imprimir_vector(&vec);
    printf("\n");
   
  

    return 0;
}