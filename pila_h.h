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

struct producto{
    char *nombre;
    char *tipo;
    float costo;
    int fecha_lanzamiento;
    float version; 
};

typedef struct producto Producto; 
typedef struct pila Pila;

Pila *nuevaPila();
Nodo *nuevo_nodo(Pila *pila, char data[]);
int push(Pila *pila, char  cadena[]);
int es_vacia(Pila *p);
int pop(Pila *pila);
void imprimir_pila(Pila *pila);
int comprobar_parentesis(char *texto);
char * tope(Pila *pila);
int nueva_etiqueta(Pila * stack_etiquetas, char texto[],int inicio, int fin);


#endif // PILA_H_H_INCLUDED
