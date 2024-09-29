// Punto 2
/* realizar una función que reciba un carácter numérico (char) y retorne un número entero (int)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void deCharAInt(char c);

void contar_numeros(const char* input);
int es_decimal(const char* token);
int es_octal(const char* token);
int es_hexadecimal(const char* token);

int automata(const char*);    // Declaración de automata
int esHexadecimal(char c);      // Declaración de esHexadecimal
int esDigito(char c);           // Declaración de esDigito

int evaluar_expresion(const char* expresion);
int operar(int num1, int num2, char operador);
int precedencia(char operador);
void charAInt(char charNumero, int *numeroEntero);



const int estados[][28]={
    {2, 2,  7, 7,  1 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 7, 7,7,7,7,7,7,7,7,7,7 , 7 , 7 , 7},
    {7, 7,  3, 3,  6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 7 , 7 , 7 , 7,7,7,7, 7,7,7,7, 7,7,7, 7 , 7},
    {7, 7 , 7, 7 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 7,7,7,7, 7,7,7,7, 7,7,7,7, 7 , 7},
    {7, 7 , 7, 7 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4,4 , 4,4 , 4,4 , 4,4 , 4,4 , 4 , 7 , 7},
    {7, 7 , 7, 7 , 4 , 4 , 4, 4, 4,	4, 4, 4, 4,	4,	4,	4,4,	4,4,	4,4,	4,4,	4,4,	4,	0,	7},
    {7,7,	7,	7,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	7,7,7,7, 7,7,7,7, 7,7,7, 7	,0,	7},
    {7,7,	7,	7,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,7,7,7, 7,7,7,7, 7,7,7, 7	,0,	7},
    {7,7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,7,7,7, 7,7,7,7, 7,7,7, 7,	7,	7}
};


const int finales[] = {4,5,6};
const int cant_finales=3;

const char alfabeto[]={'+','-', '*', '/', 'X','x','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F','#', ' '};
const int cant_alfabeto = 28;


int main(int argc, char **args) {

    if (argc < 2) {
        printf("Uso: %s <expresion>\n", args[0]);
        return 1;
    }

    char *entrada = args[1];

    // Contar números en la entrada
    contar_numeros(entrada);

    // Evaluar la expresión y mostrar el resultado
    int resultado = evaluar_expresion(entrada);

/*
    if(automata(segundoArgumento) && segundoArgumento[0] != '\0'){
        printf("Cadena Valida");
        contar_numeros(segundoArgumento);
    }
*/

    if(resultado != -1 ){
        printf("Resultado: %d\n", resultado);
    }
    else if (strchr(entrada, '#')){
        printf("No es una operacion\n");
    }
    else{
        printf("Cadena No Valida\n");
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

        //saltar los espacios
        if (c == ' '){
            continue;
        }

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
            printf("%s es una operacion\n", token);
        }

        // Obtener el siguiente token
        token = strtok(NULL, "#");
    }
    
    free(cadena); // Liberar la memoria usada por strdup

    // Mostrar los resultados
    printf("\nResumen:\n");
    printf("Decimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n\n", hexadecimales);
}

int es_decimal(const char* token) {
/*
    size_t i = 0;
    
    // Permitir un signo inicial
    if (token[0] == '-' || token[0] == '+') {
        i++;
    }

    return esDigito(token + i);
    */

    // Verificar que todos los caracteres restantes sean dígitos
    for (size_t i = 0; token[i] != '\0'; i++) {
        if (!esDigito(token[i])) {  // Accede al carácter en lugar de un puntero
            return 0;   // No es un número decimal
        }
    }
    return 1;    // Es un número decimal
    
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
    if (token[0] != '0' || token[1] != 'x' && token[1] != 'X') {
        return 0; // No tiene el formato de número hexadecimal
    }
    
    // Verificar que todos los caracteres restantes sean válidos en hexadecimal (0-9, a-f, A-F)
    for (size_t i = 2; token[i] != '\0'; i++) {
        if (!esHexadecimal(token[i])) {
            return 0;
        }
    }
    return 1;
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

    return c >= '0' && c <= '9'; 
    
    /*
    if (c >= '0' && c <= '9') {
        return 1;
    }
    // Si no está en el rango, no es un dígito
    return 0;
    */
}


// Punto 3

void charAInt(char charNumero, int *numeroEntero) {
    // Convertir el carácter a un número entero y actualizar el valor al que apunta el puntero
    *numeroEntero = charNumero - '0';
}

// Función principal para procesar la cadena y calcular el resultado
int evaluar_expresion(const char* expresion) {
    // Pilas para los números y los operadores
    int numeros[100];
    char operadores[100];
    int top_num = -1, top_op = -1;
    int i = 0;

    while (expresion[i] != '\0') {
        // Si es un espacio, lo saltamos
        if (expresion[i] == ' ') {
            i++;
            continue;
        }

        // Si es un número, lo leemos y convertimos a entero
        if (esDigito(expresion[i])) {
            int num = 0;
            while (esDigito(expresion[i])) {
                num = num * 10 + (expresion[i] - '0');
                i++;
            }
            numeros[++top_num] = num;  // Lo agregamos a la pila de números
        } 
        // Si es un operador
        else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/') {
            // Mientras la precedencia del operador en la cima de la pila sea mayor o igual al actual
            while (top_op != -1 && precedencia(operadores[top_op]) >= precedencia(expresion[i])) {
                int num2 = numeros[top_num--];
                int num1 = numeros[top_num--];
                char op = operadores[top_op--];
                numeros[++top_num] = operar(num1, num2, op);  // Evaluar y almacenar el resultado
            }
            operadores[++top_op] = expresion[i];  // Agregar el operador a la pila
            i++;
        } else{
            return -1; //Caracter inválido encontrado
        }
    }

    // Evaluar los operadores restantes en la pila
    while (top_op != -1) {
        int num2 = numeros[top_num--];
        int num1 = numeros[top_num--];
        char op = operadores[top_op--];
        numeros[++top_num] = operar(num1, num2, op);
    }

    return numeros[top_num];  // El resultado final está en la cima de la pila de números
}

int operar(int num1, int num2, char operador) {
    switch (operador) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        default: return 0;
    }
}

int precedencia(char operador) {
    if (operador == '*' || operador == '/') {
        return 2;
    } else if (operador == '+' || operador == '-') {
        return 1;
    }
    return 0;
}