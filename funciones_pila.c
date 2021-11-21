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

//Función que comprueba si una linea de texto está bien parentesida o no. Si está bien regresa 1. Si NO está bien parentizada regresa 0.
int comprobar_parentesis(char *texto){
    Pila * stack_parentesis = nuevaPila();
    Pila * stack_leido = nuevaPila();
    Pila * stack_data = nuevaPila();

    int i, aux, contador_inicio, contador_final;
    int tam_texto = strlen(texto);

    for(i=0; i<tam_texto; i++){
        switch(texto[i]){
            case '<':
                aux=push(stack_parentesis, "<");
                contador_inicio=i+1;
                break;
            case '>':
                if ((es_vacia(stack_parentesis)) || (strcmp(tope(stack_parentesis), "<")!=0)){
                    return 0;
                }
                aux=pop(stack_parentesis);
                contador_final=i;
                aux=nueva_etiqueta(stack_leido, texto, contador_inicio, contador_final);
                if(aux==0)
                    return 0;
                break;
            case '/':
                if(texto[i-1] != '<'){
                    return 0;
                }
        }
    }
    if (!es_vacia(stack_parentesis) || !es_vacia(stack_leido)){
        return 0;
    }
    return 1;
}

int nueva_etiqueta(Pila * stack_etiquetas, char texto[],int inicio, int fin){
    char *etiqueta;
    
    etiqueta = malloc(sizeof(char) * (1+fin-inicio));

    strncpy(etiqueta, texto + (inicio*sizeof(char)), fin-inicio);
    etiqueta[fin-inicio]='\0';
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
    return 1;
}

char * tope(Pila *pila){
    return pila->fin->data;
}

/*

void liberarPila(Pila *pila){
    if(pila==NULL)
        return;
    free(pila->v);
    free(pila);
}
*/