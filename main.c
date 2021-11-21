#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pila_h.h"



int main(){
    char *muestra;
    int aux_bool;

    //muestra = "<Libro>dib</Libro>";
    muestra = "<LiBRo><titulo>Cien años de soledad</titulo><autor><nombre>Gabriel</NOMBRE><apellidos>Garcia Marquez</apellidos></autor><Edicion><anio>2000</anio><editorial>Sepan Cuantos</editorial></Edicion></Libro>";
    Pila * stack = nuevaPila();
    aux_bool = comprobar_parentesis(muestra);
    
    if(aux_bool==0){
        printf("La linea esta mal parentezida\n");
    }else{
        printf("La linea tiene las etiquetas bien\n");
    }

    system("pause");
    return 0;
}
