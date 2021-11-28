#ifndef CARRITO_H_INCLUDED
#define CARRITO_H_INCLUDED

struct precios{
    float usd;
    float mxn;
    float jpy;
    float eur;
};

typedef struct precios Precios;

struct fecha{
    int anio;
    int mes;
    int dia;
};

typedef struct fecha Fecha;

struct videojuego{
    char *nombre;
    char *genero;
    Precios * precios;
    Fecha * fecha_lanzamiento;
    char* modos;
};

typedef struct videojuego Videojuego; 

int comprobar_parentesis(char *texto, Pila * stack_etiquetas, Pila * stack_data);
int nueva_etiqueta(Pila * stack_etiquetas, Pila * stack_etiquetas_main, char texto[],int inicio, int fin);
void llenar_datos(char texto[]);
char * nuevo_texto(char texto[],int inicio, int fin);
char *regresar_etiqueta(int indice);
int comprobar_etiquetas(Pila *stack_etiquetas);
Videojuego * guardar_datos(Pila *stack_data);
void imprimir_juego(Videojuego* juego);


#endif // CARRITO_H_INCLUDED