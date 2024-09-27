// Punto 2
/* realizar una función que reciba un carácter numérico (char) y retorne un número entero (int)*/

#include <stdio.h>
void deCharAInt(char c);

void contar_numeros(const char* input);
int es_decimal(const char* token);
int es_octal(const char* token);
int es_hexadecimal(const char* token);

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
    char *segundoArgumento = args[1];

    if(automata(segundoArgumento) && segundoArgumento[0] != '\0'){
        printf("Cadena Valida");
        contar_numeros(segundoArgumento);


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

void contar_numeros(const char* input) {
    int decimales = 0, octales = 0, hexadecimales = 0;
    
    // Usar strtok para dividir la cadena en partes usando '#' como delimitador
    char* cadena = strdup(input);  // Copiamos la cadena para no modificar el original
    char* token = strtok(cadena, "#");
    
    while (token != NULL) {
        // Verificar si el token es un número decimal, octal o hexadecimal
        if (es_hexadecimal(token)) {
            hexadecimales++;
        } else if (es_octal(token)) {
            octales++;
        } else if (es_decimal(token)) {
            decimales++;
        } else {
            printf("%s es inválido\n", token);
        }

        // Obtener el siguiente token
        token = strtok(NULL, "#");
    }
    
    free(cadena); // Liberar la memoria usada por strdup

    // Mostrar los resultados
    printf("\nResumen:\n");
    printf("Decimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexadecimales);
}

int es_decimal(const char* token) {
    size_t i = 0;
    
    // Permitir un signo inicial
    if (token[0] == '-' || token[0] == '+') {
        i++;
    }

    // Verificar que todos los caracteres restantes sean dígitos
    for (; token[i] != '\0'; i++) {
        if (!esDigito(token[i])) {
            return 0;
        }
    }
    return 1;
}

int es_octal(const char* token) {
    // Un número octal comienza con '0'
    if (token[0] != '0') return 0;
    
    // Verificar que todos los caracteres restantes sean dígitos octales (0-7)
    for (size_t i = 1; token[i] != '\0'; i++) {
        if (token[i] < '0' || token[i] > '7') {
            return 0;
        }
    }
    return 1;
}

int es_hexadecimal(const char* token) {
    // Un número hexadecimal comienza con "0x" o "0X"
    if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
        // Verificar que todos los caracteres restantes sean válidos en hexadecimal (0-9, a-f, A-F)
        for (size_t i = 2; token[i] != '\0'; i++) {
            if (!esHexadecimal(token[i])) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
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

int esHexadecimal(char c) {
    // Verifica si es un número entre '0' y '9'
    if (c >= '0' && c <= '9') {
        return 1;
    }
    // Verifica si es una letra mayúscula entre 'A' y 'F'
    if (c >= 'A' && c <= 'F') {
        return 1;
    }
    // Verifica si es una letra minúscula entre 'a' y 'f'
    if (c >= 'a' && c <= 'f') {
        return 1;
    }
    // Si no cumple ninguna de las condiciones, no es un dígito hexadecimal
    return 0;
}

int esDigito(char c) {
    // Verifica si el carácter está entre '0' y '9'
    if (c >= '0' && c <= '9') {
        return 1;
    }
    // Si no está en el rango, no es un dígito
    return 0;
}
