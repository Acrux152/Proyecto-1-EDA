#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pila_h.h"

Pila *nuevaPila(){
    Pila *nueva;
    nueva = malloc(sizeof(Pila));
    nueva->tos = -1;
    nueva->inicio = NULL;
    nueva->fin = NULL;

    return nueva;
}

Nodo *nuevo_nodo(Pila *pila, char data[]){
    if ((pila == NULL) || (data == NULL)){
        printf("Apuntador no valido\n");
        return NULL;
    }
        
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->data = malloc(strlen(data)+1);
    strcpy(nuevo->data, data);
    nuevo->siguiente=NULL;
    return nuevo;
}

int push(Pila *pila, char  cadena[]){
    Nodo * nodo_temp;
    nodo_temp = nuevo_nodo(pila, cadena);

    if (nodo_temp == NULL){
        printf("Error al crear el nodo\n");
        return 0;
    }
    
    if(es_vacia(pila)){
        pila->inicio = nodo_temp;
        pila->fin = nodo_temp;
        pila->tos=1;
    }else{
        pila->fin->siguiente = nodo_temp;
        pila->fin = nodo_temp;
        pila->tos++;
    }

    return 1;
}

int es_vacia(Pila *p){
    if (p->tos<1){
        return 1;
    }
    return 0;
}

int pop(Pila *pila){
    Nodo *temp;

    if(es_vacia(pila)){
        return 0;
    }
    if(pila->inicio == pila->fin){
        free(pila->fin->data);
        free(pila->fin);
        pila->inicio=NULL;
        pila->fin=NULL;
        pila->tos=-1;
        return 1;
    }

    temp = pila->inicio;
    while(temp->siguiente != pila->fin){
        temp=temp->siguiente; 
    }
    free(pila->fin->data);
    free(pila->fin);
    pila->fin = temp;
    temp->siguiente=NULL;
    pila->tos--;
    
    return 1;
}

void imprimir_pila(Pila *pila){
    if(es_vacia(pila)){
        printf("Pila vacia\n");
        return;
    }

    Nodo *temp = pila->inicio;
    while(temp->siguiente != NULL){
        //printf("[%p->%p\n]", temp, temp->siguiente);
        printf("%s\n", temp->data); 
        temp=temp->siguiente;
    }
    printf("%s\n", pila->fin->data);
}

char * tope(Pila *pila){
    return pila->fin->data;
}

int buscar(Pila *pila, char texto[]){
    int i=1;
    Nodo *n;
    n=pila->inicio;

    while(i!= pila->tos+1){
        if(strcmp(texto, n->data) == 0)
            return i;
        n=n->siguiente;
        i++;
    }
    return -1;
}

/*

void liberarPila(Pila *pila){
    if(pila==NULL)
        return;
    free(pila->v);
    free(pila);
}


void llenar_datos(char texto[]){
    int i, contador_inicio, contador_final;
    char etiqueta[40];

    contador_inicio=-1;
    for (i=0; i<strlen(texto)-1; i++){
        switch(texto[i]){
            case '>':
                if(texto[i+1] != '<'){
                    contador_inicio = i+1; 
                }
                break;
            case '<':
                if(contador_inicio != -1){
                    contador_final= i-1;
                    strncpy(etiqueta, texto + (contador_inicio*sizeof(char)), 1+contador_final-contador_inicio);
                    etiqueta[1+contador_final- contador_inicio]='\0';
                    printf("%s\n", etiqueta);
                    contador_inicio=-1;
                }
                break;
        }
    }
}

*/