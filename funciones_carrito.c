#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pila_h.h"
#include "carrito_h.h"

//Función que comprueba si una linea de texto está bien parentesida o no. Si está bien regresa 1. Si NO está bien parentizada regresa 0.
int comprobar_parentesis(char *texto, Pila * stack_etiquetas, Pila * stack_data){
    Pila * stack_parentesis = nuevaPila();
    Pila * stack_etiquetas_temp = nuevaPila();

    int i, aux, contador_inicio, contador_final, bool_data;
    int tam_texto = strlen(texto);

    bool_data=-1;

    for(i=0; i<tam_texto; i++){
        switch(texto[i]){
            case '<':
                if(bool_data==1){
                    contador_final=i-1;
                    push(stack_data, nuevo_texto(texto, contador_inicio, contador_final+1));
                }
                aux=push(stack_parentesis, "<");
                contador_inicio=i+1;
                break;
            case '>':
                if ((es_vacia(stack_parentesis)) || (strcmp(tope(stack_parentesis), "<")!=0)){
                    return 0;
                }
                aux=pop(stack_parentesis);
                contador_final=i;
                aux=nueva_etiqueta(stack_etiquetas_temp,stack_etiquetas, texto, contador_inicio, contador_final);
                
                if(aux==0)
                    return 0;
                
                bool_data=-1;
                if(texto[i+1] != '<'){
                    contador_inicio=i+1;
                    bool_data=1;
                }
                break;
            case '/':
                if(texto[i-1] != '<'){
                    return 0;
                }
        }
    }
    if (!es_vacia(stack_parentesis) || !es_vacia(stack_etiquetas_temp)){
        return 0;
    }
    if( comprobar_etiquetas(stack_etiquetas) != 1)
        return 0;
    return 1;
}

int nueva_etiqueta(Pila * stack_etiquetas, Pila * stack_etiquetas_main, char texto[],int inicio, int fin){
    char *etiqueta;

    etiqueta = nuevo_texto(texto, inicio, fin);
    strlwr(etiqueta);
    if(etiqueta[0]=='/'){
        strncpy(etiqueta, etiqueta + (1*sizeof(char)), strlen(etiqueta)-1);
        etiqueta[strlen(etiqueta)-1]='\0';
        if (es_vacia(stack_etiquetas) || strcmp(tope(stack_etiquetas), etiqueta) !=0){
            return 0;
        }  
        pop(stack_etiquetas);
        return 1;    
    }
    push(stack_etiquetas, etiqueta);
    
    etiqueta = nuevo_texto(texto, inicio, fin);
    strupr(etiqueta);
    push(stack_etiquetas_main, etiqueta); 
    return 1;
}

char * nuevo_texto(char texto[],int inicio, int fin){
    char *etiqueta;
    
    etiqueta = malloc(sizeof(char) * (1+fin-inicio));

    strncpy(etiqueta, texto + (inicio*sizeof(char)), fin-inicio);
    etiqueta[fin-inicio]='\0';

    return etiqueta;
}

Videojuego * guardar_datos(Pila *stack_data){
    Videojuego *juego=malloc(sizeof(Videojuego));
    Nodo *n;
    int i=1;

    n=stack_data->inicio;

    juego->nombre=malloc(strlen(n->data)*sizeof(char));
    strcpy(juego->nombre, n->data);
    n=n->siguiente;

    juego->genero=malloc(strlen(n->data)*sizeof(char));
    strcpy(juego->genero, n->data);
    n=n->siguiente;

    juego->precios=malloc(sizeof(Precios));
    juego->precios->usd=atof(n->data);
    n=n->siguiente;
    juego->precios->mxn=atof(n->data);
    n=n->siguiente;
    juego->precios->jpy=atof(n->data);
    n=n->siguiente;
    juego->precios->eur=atof(n->data);
    n=n->siguiente;

    juego->fecha_lanzamiento=malloc(sizeof(Fecha));
    juego->fecha_lanzamiento->anio=atoi(n->data);
    n=n->siguiente;
    juego->fecha_lanzamiento->mes=atoi(n->data);
    n=n->siguiente;
    juego->fecha_lanzamiento->dia=atoi(n->data);
    n=n->siguiente;

    juego->modos=malloc(strlen(n->data)*sizeof(char));
    strcpy(juego->modos, n->data);

    return juego;
}

int comprobar_etiquetas(Pila *stack_etiquetas){
    char aux[12];
    int i;
    Nodo *n;
    n=stack_etiquetas->inicio;

    if (stack_etiquetas->tos != 12){
        printf("Faltan o sobran etiquetas\n");
        return 0;
    }
    for(i=1; i<=12; i++){
        strcpy(aux, regresar_etiqueta(i));
        if(strcmp(aux, n->data) != 0){
            printf("Alguna etiqueta esta mal escrita.\n");
            return 0;
        }
        n=n->siguiente;
    }
    return 1;
}

char *regresar_etiqueta(int indice){
    switch(indice){
        case 1:
            return "VIDEOJUEGO";
            break;
        case 2:
            return "GENERO";
            break;
        case 3:
            return "PRECIO";
            break;
        case 4:
            return "USD";
            break;
        case 5:
            return "MXN";
            break;
        case 6:
            return "JPY";
            break;
        case 7:
            return "EUR";
            break;
        case 8:
            return "LANZAMIENTO";
            break;
        case 9:
            return "ANIO";
            break;
        case 10:
            return "MES";
            break;
        case 11:
            return "DIA";
            break;
        case 12:
            return "MODO";
            break;
        default:
            return "NULL";    
    }
}

void imprimir_juego(Videojuego* juego){
    printf("Nombre:%s\n", juego->nombre);
    printf("Genero:%s\n", juego->genero);
    printf("Precio:\nUSD %f\t MXN %f\t JPY %f\t EUR %f\t\n", juego->precios->usd, juego->precios->mxn, juego->precios->jpy, juego->precios->eur);
    printf("Lanzamiento: %d/%d/%d\n", juego->fecha_lanzamiento->dia, juego->fecha_lanzamiento->mes, juego->fecha_lanzamiento->anio);
    printf("Modos: %s\n", juego->modos);

}