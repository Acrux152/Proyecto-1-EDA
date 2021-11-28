#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pila_h.h"
#include "carrito_h.h"



int main(){
    char muestra[2000];
    int aux_bool;
    Pila * stack_etiquetas = nuevaPila();
    Pila * stack_data = nuevaPila();
    Videojuego* juego;
    //muestra = "<Libro>dib<Libro>";
    //muestra = "<LiBRo><titulo>Cien anios de soledad</titulo><autor><nombre>Gabriel</NOMBRE><apellidos>Garcia Marquez</apellidos></autor><Edicion><anio>2000</anio><editorial>Sepan Cuantos</editorial></Edicion></Libro>";

    FILE *f_sp;

    f_sp=fopen("Catalogo.txt","rt");

    if(f_sp==NULL){
        printf("No existe el archivo datos.txt\n");
        system("pause");
        return -1;
    }

    fgets(muestra, 1999, f_sp);
    muestra[1999]='\0';
    
    
    Pila * stack = nuevaPila();
    aux_bool = comprobar_parentesis(muestra, stack_etiquetas, stack_data);
    
    if(aux_bool==0){
        printf("La linea esta mal parentezida\n");
    }else{
        printf("La linea tiene las etiquetas bien\n");
    }

    juego=guardar_datos(stack_data);
    imprimir_juego(juego);

    system("pause");
    return 0;
}