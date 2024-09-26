// Punto 2
/* realizar una función que reciba un carácter numérico (char) y retorne un número entero (int)*/

#include <stdio.h>
void deCharAInt(char c);

int main()
{
    char c;
    printf("Ingrese un caracter numerico: ");
    scanf("%c", &c);

    deCharAInt(c);
}

void deCharAInt(char c){
    if(c < '0' || c > '9'){
        printf("El caracter ingresado no es numerico\n");
        return;
    }

    char d = c - '0';
    printf("El numero entero es: %d\n", d);
    return;
}
