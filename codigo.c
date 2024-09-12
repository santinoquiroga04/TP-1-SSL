// Punto 2
/* realizar una función que reciba un carácter numérico (char) y retorne un número entero (int)*/

#include <stdio.h>

int main()
{
    char c;
    printf("Ingrese un caracter numerico: ");
    scanf("%c", &c);

    if(c < '0' || c > '9'){
        printf("El caracter ingresado no es numerico\n");
        return 1;
    }

    char d = c - '0';
    printf("El numero entero es: %d\n", d);
    return 0;
}
