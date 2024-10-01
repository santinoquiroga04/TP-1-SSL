#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void charAInt(char charNumero, int *numeroEntero);
int esDigito(char c);  // Prototipo de la función esDigito
int esHexadecimal(char c);  // Prototipo de la función esHexadecimal
void contar_numeros(const char* input);
int es_decimal(const char* token);
int es_octal(const char* token);
int es_hexadecimal(const char* token);
int es_operacion_valida(const char *cadena) ;

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
    // punto 1
    if(automata(segundoArgumento) && segundoArgumento[0] != '\0'){
        printf("Cadena Valida para punto 1");
        contar_numeros(segundoArgumento);
    }
    else{
        printf("Cadena No Valida para punto 1\n");
    }

    //punto 3
    if (es_operacion_valida(segundoArgumento)) {
        printf("La cadena es una operacion valida.\n");
        printf("Resultado para punto 3: %d\n", evaluar_expresion(segundoArgumento));  
    } else {
        printf("La cadena no es una operacion valida.\n");
    }

    return 0;
}

size_t posicion_alfabeto(char);

int automata(const char *input) {
    size_t estado = 0;
    char c;
    
    // Iterar sobre cada carácter del stringS
    size_t i;
    for ( i = 0; input[i] != '\0'; i++) {
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
    for (i; token[i] != '\0'; i++) {
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
//punto 2
void charAInt(char charNumero, int *numeroEntero) {
    // Convertir el carácter a un número entero y actualizar el valor al que apunta el puntero
    *numeroEntero = charNumero - '0';
}

// Punto 3


void charAInt(char charNumero, int *numeroEntero);
int operar(int num1, int num2, char operador);
int precedencia(char operador);

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

int es_operacion_valida(const char *cadena) {
       int i = 0;
    int ultimo_era_digito = 0;  // Para saber si el último carácter era un dígito
    int tiene_operador = 0;     // Para asegurarnos de que haya al menos un operador
    int puede_ser_signo = 1;    // Permitir que el primer caracter sea un signo

    // Recorrer la cadena caricter por carácter
    while (cadena[i] != '\0') {
        char c = cadena[i];

        // Si el carácter es un espacio, lo ignoramos
        if (c == ' ') {
            i++;
            continue;
        }

        // Verificar si es un digito
        if (esDigito(c)) {
            ultimo_era_digito = 1;  // Marcar que hemos encontrado un digito
            puede_ser_signo = 0;    // Una vez encontrado un digito, el siguiente no puede ser un signo
        } 
        // Verificar si es un operador valido (+, -, *, /)
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            tiene_operador = 1;  // Hemos encontrado un operador

            // Verificar si el operador es `*` o `/`, ya que no pueden estar al principio ni después de otro operador
            if (c == '*' || c == '/') {
                if (!ultimo_era_digito) {
                    printf("Error: operador '%c' no puede seguir a otro operador o estar al principio para el punto 3.\n", c);
                    return 0;
                }
            }

            // Si es un operador `+` o `-`, puede estar al principio o después de un operador
            if ((c == '+' || c == '-') && puede_ser_signo) {
                ultimo_era_digito = 0;  // El signo puede estar al principio o después de un operador
                puede_ser_signo = 0;    // ya procesamoos el primer signo
            } 
            // Si no es el primer carácter, validar la secuencia de operadorescv
            else if (!ultimo_era_digito) {
                printf("Error: operador '%c' no puede seguir a otro operador para el punto 3.\n", c);
                return 0;
            }

            // Despues de un operador, esperamos un dígito o un signo
            ultimo_era_digito = 0;
            puede_ser_signo = 1;
        } 
        // Si no es ni un dígito ni un operador, es inválido
        else {
            printf("Error: caracter invalido '%c' encontrado en la cadena para el punto 3.\n", c);
            return 0;
        }

        i++;
    }

    // Al final de la cadena, el ultimo carácter debe ser un dígito
    if (!ultimo_era_digito) {
        printf("Error: la cadena no puede terminar con un operador para el punto 3.\n");
        return 0;
    }

    // Si no hay operadores, no es una operación válida
    if (!tiene_operador) {
        printf("Error: la cadena no contiene operadores para el punto 3.\n");
        return 0;
    }

    // Si pasa todas las validaciones, la cadena es valida
    return 1;
}