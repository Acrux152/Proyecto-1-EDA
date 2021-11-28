#ifndef PILA_H_H_INCLUDED
#define PILA_H_H_INCLUDED

typedef struct nodo Nodo;

struct nodo{
    char *data;
    Nodo *siguiente;
};

struct pila{
    int tos;
    Nodo * inicio;
    Nodo *fin;
};

typedef struct pila Pila;

Pila *nuevaPila();
Nodo *nuevo_nodo(Pila *pila, char data[]);
int push(Pila *pila, char  cadena[]);
int es_vacia(Pila *p);
int pop(Pila *pila);
void imprimir_pila(Pila *pila);
char * tope(Pila *pila);
int buscar(Pila *pila, char texto[]);


#endif // PILA_H_H_INCLUDED
