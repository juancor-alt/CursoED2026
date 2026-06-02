#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float areaCirculo(float radio) {
    return M_PI * radio * radio;
}

float areaCuadrado(float lado) {
    return lado * lado;
}

float volumenEsfera(float radio) {
    return (4.0f/3.0f) * M_PI * powf(radio, 3.0f);
}

float volumenCubo(float lado) {
    return lado * lado * lado;
}

int main(void) {
    float radio, lado;

    printf("Ingrese el radio del circulo: ");
    if (scanf("%f", &radio) == 1) {
        printf("Area del circulo: %.2f\n\n", areaCirculo(radio));
    }

    printf("Ingrese el lado del cuadrado: ");
    if (scanf("%f", &lado) == 1) {
        printf("Area del cuadrado: %.2f\n\n", areaCuadrado(lado));
    }

    printf("Ingrese el radio de la esfera: ");
    if (scanf("%f", &radio) == 1) {
        printf("Volumen de la esfera: %.2f\n\n", volumenEsfera(radio));
    }

    printf("Ingrese el lado del cubo: ");
    if (scanf("%f", &lado) == 1) {
        printf("Volumen del cubo: %.2f\n\n", volumenCubo(lado));
    }

    return 0;
}
