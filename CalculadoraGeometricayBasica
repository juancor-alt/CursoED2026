#include <stdio.h>
#include <math.h>


float areaCirculo(float radio) {
    return M_PI * radio * radio;
}

float areaCuadrado(float lado) {
    return lado * lado;
}


float volumenEsfera(float radio) {
    return (4.0/3.0) * M_PI * pow(radio, 3);
}

float volumenCubo(float lado) {
    return lado * lado * lado;
}


int main() {
    float radio, lado;

    printf("Ingrese el radio del circulo: ");
    scanf("%f", &radio);
    printf("Area del circulo: %.2f\n\n", areaCirculo(radio));

    printf("Ingrese el lado del cuadrado: ");
    scanf("%f", &lado);
    printf("Area del cuadrado: %.2f\n\n", areaCuadrado(lado));


    printf("Ingrese el radio de la esfera: ");
    scanf("%f", &radio);
    printf("Volumen de la esfera: %.2f\n\n", volumenEsfera(radio));


    printf("Ingrese el lado del cubo: ");
    scanf("%f", &lado);
    printf("Volumen del cubo: %.2f\n\n", volumenCubo(lado));

    return 0;
}
