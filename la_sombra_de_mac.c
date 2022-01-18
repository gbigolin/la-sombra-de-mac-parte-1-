#include "la_sombra_de_mac.h"
#include <stdio.h>
#include <stdlib.h>

#define BLOO "\U0001f47b"
#define TERRENO "\U0001f7e6"
#define MAC "\U0001f466"
#define VIDA "\U0001f497"
#define LLAVE "\U0001f511"
#define INTERRUPTOR "\U0001f533"
#define ROMBO "\U0001f536"
#define COLUMNAS "\u21AE"
#define FILAS "\u2195"

#define ARRIBA 'W'
#define ABAJO 'S'
#define IZQUIERDA 'A'
#define DERECHA 'D'

const int VIDAS = 3;
const int PUNTAJE = 0;

/*
 * Post: Deveuleve true si las coordenadas son iguales, sino false.
 */
bool coordenadas_iguales(coordenada_t a, coordenada_t b)
{
    return ((a.col == b.col) && (a.fila == b.fila));
}

/*
 * Post: Deja al personaje en un estado valido para iniciar el juego.
 */
void inicializar_personaje(personaje_t* ref_personaje, coordenada_t arranque_personaje)
{
    ref_personaje->vida = VIDAS;
    ref_personaje->puntos = PUNTAJE;
    ref_personaje->interruptor_apretado = false;
    ref_personaje->tiene_llave = false;
    ref_personaje->posicion.fila = arranque_personaje.fila;
    ref_personaje->posicion.col = arranque_personaje.col;
}

/*
 * Post: Deja al personaje en un estado valido para iniciar el juego
 */
void inicializar_sombra(sombra_t* ref_sombra, coordenada_t arranque_sombra)
{
    ref_sombra->esta_viva = true;
    ref_sombra->posicion.fila = arranque_sombra.fila;
    ref_sombra->posicion.col = arranque_sombra.col;
}

/*
 * Pre: Recibe el ingreso del usuario.
 * Post: Devuelve true si el movimiento recibido concuerda con la convención
 * propuesta, sino false.
 */
bool es_movimiento_valido(char movimiento)
{
    if ((movimiento == ABAJO) ||
        (movimiento == ARRIBA) ||
        (movimiento == DERECHA) ||
        (movimiento == IZQUIERDA)) {
        return true;
    }
    return false;
}

/* 
 * Post: Guarda el movimiento. 
 */ 
 
void pedir_movimiento(char* ref_movimiento)
{
    printf("Ingrese proximo movimiento: ");
    scanf(" %c", ref_movimiento);
    if(!es_movimiento_valido(*ref_movimiento)){
        printf("Movimiento invalido\n");
        pedir_movimiento(ref_movimiento);
    }
}


/*
* Post: Devuelve true si la posición está dentro de las dimensiones dadas, sino false.
*/
bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho)
{
    if ((posicion.fila < max_alto) &&
        (posicion.fila >=0) &&
        (posicion.col < max_ancho) &&
        (posicion.col >=0)) {
        return true;
    }
    return false;
}


void realizar_movimiento(coordenada_t* coordenada, int diff_fila, int diff_col){
    coordenada->fila += diff_fila;
    coordenada->col += diff_col; 

    if(!esta_dentro_rango(*coordenada,MAX_FILAS, MAX_COLUMNAS)){
        realizar_movimiento(coordenada,-diff_fila,-diff_col);
    }

}

/*
* Post: Modifica la coordenada según los valores ingresados, mueve el peronaje y la sombra en la direccion recibida. 

* El personaje se mueve de la forma:
* -> W: Si el personaje debe moverse para la arriba. 
* -> A: Si el personaje debe moverse para la izquierda.
* -> S: Si el personaje debe moverse para la abajo.
* -> D: Si el personaje debe moverse para la derecha.
*
*   La sombra se mueve de igual forma para el eje vertical, pero
* para el eje horizontal se moverá de forma inversa:
* -> A: Si la sombra debe moverse para la derecha.
* -> D: Si la sombra debe moverse para la izquierda.
*/
void mover_personaje (personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento){

    switch (movimiento)
        {
        case IZQUIERDA:
            realizar_movimiento(&ref_personaje->posicion,0,-1);
            realizar_movimiento(&ref_sombra->posicion,0,1);
            break;

        case DERECHA:
            realizar_movimiento(&ref_personaje->posicion,0,1);
            realizar_movimiento(&ref_sombra->posicion,0,-1);
            break;

        case ABAJO:
            realizar_movimiento(&ref_sombra->posicion,1,0);
            realizar_movimiento(&ref_personaje->posicion,1,0);
            break;

        case ARRIBA:
            realizar_movimiento(&ref_personaje->posicion,-1,0);
            realizar_movimiento(&ref_sombra->posicion,-1,0);
            break;
        }  

}

coordenada_t coordenada_aleatoria(int max_alto, int max_ancho)
{
    coordenada_t coordenada;

    coordenada.fila =  rand() % max_alto;
    coordenada.col =  rand() % max_ancho;
    return coordenada;
}

/*
* Post: Devuelve la posición del elemento del vector, que coincida con la    *coordenada pasada 'posicion', si no se encuentra ningún elemento, se devolverá *-1. 
*/
int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion)
{
   
   int posicion_b = -1;
   int i = 0;
   bool encontre_elemento = false; 

    while (i< tope && encontre_elemento == false ){
        if(elementos[i].posicion.fila==posicion.fila && elementos[i].posicion.col==posicion.col){ 
            posicion_b= i;
            encontre_elemento = true;
        }
        i++;
    }return posicion_b;
}   


void imprimir_estadisticas(juego_t juego){
    printf("%s Estadísticas de Mac:\n", ROMBO);
    printf("%s Fila: %i",FILAS,juego.personaje.posicion.fila);
    printf("  %s Columna: %i",COLUMNAS,juego.personaje.posicion.col);
    printf("  %s Vidas:%i",VIDA,juego.personaje.vida);
    printf("  Puntos:%i",juego.personaje.puntos);
    printf("  %s llave:%i",LLAVE,juego.personaje.tiene_llave);
    printf("  %s interruptor:%i\n",INTERRUPTOR,juego.personaje.interruptor_apretado);
    printf(" \n");

    printf("%s Estadísticas de Bloo:\n", ROMBO);
    printf("%s Fila: %i",FILAS,juego.sombra.posicion.fila);
    printf("  %s Columna: %i ",COLUMNAS,juego.sombra.posicion.col);
    printf("  %s Vida:%i\n",VIDA, juego.sombra.esta_viva);
    printf(" \n\n");
        
    }


void imprimir_terreno(juego_t juego){

    int fila, columna;
    for (fila = 0; fila < MAX_FILAS; fila++) {
        printf("* ");
    }
    printf("*\n");
    for (fila = 0; fila < MAX_FILAS; fila++) {
        printf("*");
        for (columna = 0; columna < MAX_COLUMNAS; columna++) {
            if ((fila == juego.personaje.posicion.fila) &&
                (columna == juego.personaje.posicion.col)) {
                // imprimo personaje
                printf("%s",MAC);
            } else if((fila == juego.sombra.posicion.fila) &&
                       (columna == juego.sombra.posicion.col)) {
                // imprimo sombra
                printf("%s",BLOO);
            } else {
                // imprimo posicion vacia
                printf("%s",TERRENO);
            }
        }
        printf("*\n");
    } 
    for (fila = 0; fila < MAX_FILAS; fila++) {
        printf("* ");
    }
    printf("*\n");
    
    imprimir_estadisticas(juego);

}



    