// Punto 2
/* realizar una función que reciba un carácter numérico (char) y retorne un número entero (int)*/

#include <stdio.h>

const estados[][28]={
    {2, 2,  7, 7,  1 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 7, 7,7,7,7,7,7,7,7,7,7 , 7 , 7 , 7},
    {7, 7,  3, 3,  6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 7 , 7 , 7 , 7,7,7,7, 7,7,7,7, 7,7,7, 7 , 7},
    {7, 7 , 7, 7 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 7,7,7,7, 7,7,7,7, 7,7,7,7, 7 , 7},
    {7, 7 , 7, 7 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4,4 , 4,4 , 4,4 , 4,4 , 4,4 , 4 , 7 , 7},
    {7, 7 , 7, 7 , 4 , 4 , 4, 4, 4,	4, 4, 4, 4,	4,	4,	4,4,	4,4,	4,4,	4,4,	4,4,	4,	0,	7},
    {7,7,	7,	7,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	7,7,7,7, 7,7,7,7, 7,7,7, 7	,0,	7},
    {7,7,	7,	7,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,7,7,7, 7,7,7,7, 7,7,7, 7	,0,	7},
    {7,7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,7,7,7, 7,7,7,7, 7,7,7, 7,	7,	7}
};

const finales[] = {4,5,6};
const cant_finales=3;

const alfabeto[]={'+','-','X','x','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f',
'A','B','C','D','E','F','#'};
const cant_alfabeto = 27;
int main(int argc, char **args) {
    printf("Hello world\n");
    char *segundoArgumento = args[1];
<
    if(automata(segundoArgumento) && segundoArgumento[0] != '\0'){
        printf("Cadena Valida");
    }
    else{
        printf("Cadena No Valida");
    }


    return 0;
}

size_t posicion_alfabeto(char);

int automata(const char *input) {
    size_t estado = 0;
    char c;
    
    // Iterar sobre cada carácter del string
    for (size_t i = 0; input[i] != '\0'; i++) {
        c = input[i];
        if(posicion_alfabeto(c) == 27) return 0;
        estado = estados[estado][posicion_alfabeto(c)];
        if(estado == 7)return 0; 
    }
    return 1;
}

size_t posicion_alfabeto(char c){
    size_t i;
    for(i = 0; i< cant_alfabeto;i++){
        if(alfabeto[i] == c)
        {return i;}
    }
      return i;
}


int charToInt(char c){
    
    if(c < '0' || c > '9'){
        printf("El caracter ingresado no es numerico\n");
        return 1;
    }

    char d = c - '0';
    printf("El numero entero es: %d\n", d);
}
