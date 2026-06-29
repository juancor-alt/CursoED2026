#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CLIENTES 100
#define MAX_ASIENTOS 50

typedef struct {
    int documento;
    int cantidadEntradas;
    int sillas[MAX_ASIENTOS];
    int deseaProductos;
    int totalPedido;
} Cliente;

typedef struct {
    Cliente datos[MAX_CLIENTES];
    int frente;
    int fin;
    int tamano;
} ColaClientes;

typedef struct {
    int sillas[MAX_CLIENTES];
    int valores[MAX_CLIENTES];
    int tope;
} PilaPedidos;

void inicializarCola(ColaClientes *cola) {
    cola->frente = 0;
    cola->fin = -1;
    cola->tamano = 0;
}

bool colaVacia(ColaClientes *cola) {
    return cola->tamano == 0;
}

bool colaLlena(ColaClientes *cola) {
    return cola->tamano == MAX_CLIENTES;
}

void encolar(ColaClientes *cola, Cliente cliente) {
    if (colaLlena(cola)) {
        printf("La cola esta llena. No se pueden agregar mas clientes.\n");
        return;
    }

    cola->fin = (cola->fin + 1) % MAX_CLIENTES;
    cola->datos[cola->fin] = cliente;
    cola->tamano++;
}

Cliente desencolar(ColaClientes *cola) {
    Cliente clienteVacio = {0, 0, 0, 0, 0};
    if (colaVacia(cola)) {
        return clienteVacio;
    }

    Cliente cliente = cola->datos[cola->frente];
    cola->frente = (cola->frente + 1) % MAX_CLIENTES;
    cola->tamano--;
    return cliente;
}

void inicializarPila(PilaPedidos *pila) {
    pila->tope = -1;
}

bool pilaVacia(PilaPedidos *pila) {
    return pila->tope == -1;
}

bool pilaLlena(PilaPedidos *pila) {
    return pila->tope == MAX_CLIENTES - 1;
}

void empilar(PilaPedidos *pila, int silla, int valor) {
    if (pilaLlena(pila)) {
        printf("La pila de pedidos esta llena.\n");
        return;
    }

    pila->tope++;
    pila->sillas[pila->tope] = silla;
    pila->valores[pila->tope] = valor;
}

void desempilar(PilaPedidos *pila, int *silla, int *valor) {
    if (pilaVacia(pila)) {
        *silla = 0;
        *valor = 0;
        return;
    }

    *silla = pila->sillas[pila->tope];
    *valor = pila->valores[pila->tope];
    pila->tope--;
}

int asignarSillasConsecutivas(bool asientos[], int totalAsientos, int cantidad, int sillasAsignadas[]) {
    int silasEncontradas = 0;
    
    for (int i = 0; i < totalAsientos && silasEncontradas < cantidad; i++) {
        if (asientos[i]) {
            asientos[i] = false;
            sillasAsignadas[silasEncontradas] = i + 1;
            silasEncontradas++;
        }
    }
    
    return silasEncontradas;
}

void atenderCliente(ColaClientes *cola, PilaPedidos *pila, bool asientos[], int totalAsientos) {
    if (colaVacia(cola)) {
        printf("No hay clientes en la cola para atender.\n");
        return;
    }

    Cliente cliente = desencolar(cola);
    printf("\nAtendiendo cliente con documento: %d\n", cliente.documento);

    printf("Ingrese cantidad de entradas: ");
    scanf("%d", &cliente.cantidadEntradas);

    // Asignar sillas consecutivas
    int silasAsignadas = asignarSillasConsecutivas(asientos, totalAsientos, cliente.cantidadEntradas, cliente.sillas);

    if (silasAsignadas < cliente.cantidadEntradas) {
        printf("Advertencia: Solo hay %d sillas disponibles. Se asignaron %d de %d entradas solicitadas.\n", 
               silasAsignadas, silasAsignadas, cliente.cantidadEntradas);
        cliente.cantidadEntradas = silasAsignadas;
    }

    if (silasAsignadas > 0) {
        printf("\n========== SILLAS ASIGNADAS ==========\n");
        for (int i = 0; i < silasAsignadas; i++) {
            printf("Entrada %d --- Silla: %d\n", i + 1, cliente.sillas[i]);
        }
        printf("=====================================\n");
    } else {
        printf("No hay sillas disponibles para este cliente.\n");
        return;
    }

    printf("Desea comprar productos de confiteria? (1=Si / 0=No): ");
    scanf("%d", &cliente.deseaProductos);

    if (cliente.deseaProductos == 1) {
        printf("Ingrese el valor total del pedido: ");
        scanf("%d", &cliente.totalPedido);
        // Agregar pedido para cada silla del cliente
        for (int i = 0; i < silasAsignadas; i++) {
            empilar(pila, cliente.sillas[i], cliente.totalPedido);
        }
        printf("Pedido registrado para las sillas: ");
        for (int i = 0; i < silasAsignadas; i++) {
            printf("%d", cliente.sillas[i]);
            if (i < silasAsignadas - 1) printf(", ");
        }
        printf(".\n");
    } else {
        cliente.totalPedido = 0;
        printf("El cliente no realizo pedido de confiteria.\n");
    }

    printf("Venta finalizada para el cliente %d.\n", cliente.documento);
}

void iniciarPelicula(PilaPedidos *pila) {
    printf("\nLa pelicula ha iniciado. Se iniciara la entrega de pedidos.\n");

    while (!pilaVacia(pila)) {
        int silla = 0;
        int valor = 0;
        desempilar(pila, &silla, &valor);
        printf("Entregando pedido a la silla %d por valor de $%d.\n", silla, valor);
    }

    printf("Se entregaron todos los pedidos.\n");
}

int main() {
    ColaClientes cola;
    PilaPedidos pila;
    bool asientos[MAX_ASIENTOS];
    int opcion;

    inicializarCola(&cola);
    inicializarPila(&pila);

    for (int i = 0; i < MAX_ASIENTOS; i++) {
        asientos[i] = true;
    }

    do {
        printf("\n===== SISTEMA DE VENTA DE ENTRADAS Y PEDIDOS =====\n");
        printf("1. Registrar cliente en la cola\n");
        printf("2. Atender siguiente cliente\n");
        printf("3. Iniciar pelicula y entregar pedidos\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                if (colaLlena(&cola)) {
                    printf("La cola esta llena.\n");
                    break;
                }

                Cliente nuevoCliente;
                printf("Ingrese documento del cliente: ");
                scanf("%d", &nuevoCliente.documento);
                nuevoCliente.cantidadEntradas = 0;
                for (int i = 0; i < MAX_ASIENTOS; i++) {
                    nuevoCliente.sillas[i] = 0;
                }
                nuevoCliente.deseaProductos = 0;
                nuevoCliente.totalPedido = 0;

                encolar(&cola, nuevoCliente);
                printf("Cliente registrado en la cola.\n");
                break;
            }
            case 2:
                atenderCliente(&cola, &pila, asientos, MAX_ASIENTOS);
                break;
            case 3:
                iniciarPelicula(&pila);
                break;
            case 4:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}
