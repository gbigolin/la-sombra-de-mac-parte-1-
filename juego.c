
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "la_sombra_de_mac.h"


int main(void) 
{
    // Creo juego
    juego_t juego;

    //Variables auxiliares
    char movimiento;


    // Inicializo random
    srand ((unsigned)time(NULL));

    // Inicializo personaje y sombra
    inicializar_personaje(&juego.personaje, coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS-1));
    inicializar_sombra(&juego.sombra, coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS-1));

    //Imprimo terreno inicial
    imprimir_terreno(juego);

    printf("Bienvenido!\n");
    
    // Hago lazo infinito con el juego
    while(true){
        pedir_movimiento(&movimiento);
        mover_personaje(&juego.personaje, &juego.sombra, movimiento);
            // Actualizo el terreno
        imprimir_terreno(juego);
    }  
    return 0;
}

