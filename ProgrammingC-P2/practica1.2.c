/***********************************************
*
* @Proposito: Practica 1.2
* @Autor/es: Yannick Suchy Viñolo
* @Fecha creacion: 07/06/2024
* @Fecha ultima modificacion: 07/06/2024
*
************************************************/

//definir las distintas librerias que se van a utilizar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definir las constantes que se van a utilizar y sus valores
#define MAX_VEHICLES 8
#define MAX_OPERATIONS 10
#define MAX_CHAR 200

//definir las estructuras que se van a utilizar
//Estrctura para los datos del parking
typedef struct {
    int hora_entrada;
    int minutos_entrada;
    int hora_salida;
    int minutos_salida;
    int total_entrada;
    int total_salida;
    float precio;
} Parking;

//Estructura para los datos de los vehiculos
typedef struct {
    char type[2];
    char matricula[MAX_CHAR];
    int inParking;
    Parking parking[MAX_OPERATIONS];
    int count_operations;
    int registrado;
} Vehicle;

//Estructura para los datos de los tipos de vehiculos
typedef struct {
    int B_reducido;
    int B_punta;
    int B_normal;
    int C_reducido;
    int C_punta;
    int C_normal;
    int T_reducido;
    int T_punta;
    int T_normal;
} Tipo;

/***********************************************
*
* @Finalidad: regresar la palabra de una cadena de palabras
* @Parametros:  char input[]    = cadena de caracteres
                char word[]     = palabra que se va a almacenar
                int pos         = numero de la posicion en la cadena
                char sep        = caracter que nos dice el separador
* @Retorno: nos devuelve la posicion de la cadena
*
************************************************/

int parseString(char word[], char command[], int pos, char sep) {
    
    //Variables que se van a utilizar
    int i = 0;

    //Bucle que recorre la cadena de caracteres
    while (word[pos] != sep && word[pos] != '\0') {
        command[i] = word[pos];
        i++;
        pos++;
    }

    command[i] = '\0';

    //condicion que nos dice si el separador es el final de la cadena
    if (word[pos] != '\0') {
        pos++;
    }

    return pos;
}

/***********************************************
*
* @Finalidad: convertir un numero de una cadena de caracteres a un entero
* @Parametros:  char num[]  = cadena de caracteres
* @Retorno: nos devuelve el numero en forma de entero
*
************************************************/

int myAtoi(char num[]) {
    
    //Variables que se van a utilizar
    int num1 = 0, i = 0;

    //Bucle while que nos convierte una cadena de caracteres a un entero
    while (num[i] != '\0') {
        num1 = num1 * 10 + num[i] - '0';
        i++;
    }
    return num1;
}

/***********************************************
*
* @Finalidad: convertir una cadena de caracteres a un tipo de vehiculo
* @Parametros: char tariffs[] = cadena de caracteres
* @Retorno: nos devuelve el tipo de vehiculo
*
************************************************/

Tipo parseVehicleData(char tariffs[]) {
    
    //Variables que se van a utilizar
    Tipo tipo = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    char vehicle[20], values[20];
    int pos = 0, valPos;
    char num[10];
    int val1, val2, val3;

    //Bucle while que nos convierte una cadena de caracteres a un tipo de vehiculo
    while (tariffs[pos] != '\0') {
        pos = parseString(tariffs, vehicle, pos, ':');
        valPos = 0;
        valPos = parseString(tariffs, values, pos, '#');
        pos = parseString(values, num, 0, '/');
        val1 = myAtoi(num);
        pos = parseString(values, num, pos, '/');
        val2 = myAtoi(num);
        pos = parseString(values, num, pos, '/');
        val3 = myAtoi(num);

        //condicion que nos dice si el vehiculo es una moto, coche o camion
        if (strcmp(vehicle, "BIKES") == 0) {
            tipo.B_reducido = val1;
            tipo.B_normal = val2;
            tipo.B_punta = val3;
        } else if (strcmp(vehicle, "CARS") == 0) {
            tipo.C_reducido = val1;
            tipo.C_normal = val2;
            tipo.C_punta = val3;
        } else if (strcmp(vehicle, "TRUCKS") == 0) {
            tipo.T_reducido = val1;
            tipo.T_normal = val2;
            tipo.T_punta = val3;
        }

        pos = valPos;
    }

    return tipo;
}

/***********************************************
*
* @Finalidad: convertir las horas y minutos a minutos
* @Parametros:  int horas      = horas
                int minutos    = minutos
* @Retorno: nos devuelve los minutos
*
************************************************/

int horaAMinutos(int horas, int minutos) {
    
    //Variables que se van a utilizar
    int calculo = 0;

    //calculo que nos convierte las horas y minutos a minutos
    calculo = horas * 60 + minutos;

    return calculo;
}

/***********************************************
*
* @Finalidad: calcular el precio de un vehiculo
* @Parametros:  Vehicle vehicle[] = estructura de los vehiculos
                Tipo tipo        = estructura de los tipos de vehiculos
                int k            = numero de vehiculo
                int op           = numero de operacion
* @Retorno: nos devuelve el precio
*
************************************************/

float calcularPrecio(Vehicle vehicle[], Tipo tipo, int k, int op) {
    
    //Variables que se van a utilizar
    int total = 0;
    float precio = 0;

    //calculo del precio total
    total = vehicle[k].parking[op].total_salida - vehicle[k].parking[op].total_entrada;

    //condicion que nos dice si el vehiculo es una moto, coche o camion
    if (strcmp(vehicle[k].type, "B") == 0) {
        //condicion que nos dice si el vehiculo es de tarifa reducida, punta o normal
        if ((vehicle[k].parking[op].total_entrada >= 0 && vehicle[k].parking[op].total_entrada <= 479) || (vehicle[k].parking[op].total_entrada >= 1260 && vehicle[k].parking[op].total_entrada <= 1439)) {
            precio = total * tipo.B_reducido;
        } else if ((vehicle[k].parking[op].total_entrada >= 600 && vehicle[k].parking[op].total_entrada <= 779) || (vehicle[k].parking[op].total_entrada >= 960 && vehicle[k].parking[op].total_entrada <= 1199)) {
            precio = total * tipo.B_punta;
        } else {
            precio = total * tipo.B_normal;
        }
    } else if (strcmp(vehicle[k].type, "C") == 0) {
        //condicion que nos dice si el vehiculo es de tarifa reducida, punta o normal
        if ((vehicle[k].parking[op].total_entrada >= 0 && vehicle[k].parking[op].total_entrada <= 479) || (vehicle[k].parking[op].total_entrada >= 1260 && vehicle[k].parking[op].total_entrada <= 1439)) {
            precio = total * tipo.C_reducido;
        } else if ((vehicle[k].parking[op].total_entrada >= 600 && vehicle[k].parking[op].total_entrada <= 779) || (vehicle[k].parking[op].total_entrada >= 960 && vehicle[k].parking[op].total_entrada <= 1199)) {
            precio = total * tipo.C_punta;
        } else {
            precio = total * tipo.C_normal;
        }
    } else if (strcmp(vehicle[k].type, "T") == 0) {
        //condicion que nos dice si el vehiculo es de tarifa reducida, punta o normal
        if ((vehicle[k].parking[op].total_entrada >= 0 && vehicle[k].parking[op].total_entrada <= 479) || (vehicle[k].parking[op].total_entrada >= 1260 && vehicle[k].parking[op].total_entrada <= 1439)) {
            precio = total * tipo.T_reducido;
        } else if ((vehicle[k].parking[op].total_entrada >= 600 && vehicle[k].parking[op].total_entrada <= 779) || (vehicle[k].parking[op].total_entrada >= 960 && vehicle[k].parking[op].total_entrada <= 1199)) {
            precio = total * tipo.T_punta;
        } else {
            precio = total * tipo.T_normal;
        }
    }

    //calculo del precio final
    precio = precio * 0.01;

    return precio;
}

/***********************************************
*
* @Finalidad: mostrar la ocupacion del parking
* @Parametros: int bikes          = numero de motos
                int trucks         = numero de camiones
                int cars           = numero de coches
                Vehicle vehicle[]  = estructura de los vehiculos
                int count2          = numero de vehiculos
* @Retorno: no devuelve nada
*
************************************************/

void showOccupation(int bikes, int trucks, int cars, Vehicle vehicle[], int count2) {
    
    //Variables que se van a utilizar
    int x1 = 1, x2 = 1, x3 = 1;
    int j = 0;

    printf("Vehicles currently in the parking:\n");
    printf("BIKES:");

    //bucle for para recorrer las motos
    for (j = 0; j < count2; j++) {
        if ((strcmp(vehicle[j].type, "B") == 0) && vehicle[j].inParking == 1) {
            if (x1 < bikes) {
                printf(" %s -", vehicle[j].matricula);
                x1++;
            } else {
                x1 = j;
            }
        }
    }

    //condicion que nos dice si hay motos en el parking
    if (bikes >= 1) {
        printf(" %s", vehicle[x1].matricula);
    } else {
        printf(" No bikes");
    }

    printf("\nCARS:");

    //bucle for para recorrer los coches
    for (j = 0; j < count2; j++) {
        if ((strcmp(vehicle[j].type, "C") == 0) && vehicle[j].inParking == 1) {
            if (x2 < cars) {
                printf(" %s -", vehicle[j].matricula);
                x2++;
            } else {
                x2 = j;
            }
        }
    }

    //condicion que nos dice si hay coches en el parking
    if (cars >= 1) {
        printf(" %s", vehicle[x2].matricula);
    } else {
        printf(" No cars");
    }

    printf("\nTRUCKS:");

    //bucle for para recorrer los camiones
    for (j = 0; j < count2; j++) {
        if ((strcmp(vehicle[j].type, "T") == 0) && vehicle[j].inParking == 1) {
            if (x3 < trucks) {
                printf(" %s -", vehicle[j].matricula);
                x3++;
            } else {
                x3 = j;
            }
        }
    }

    //condicion que nos dice si hay camiones en el parking
    if (trucks >= 1) {
        printf(" %s", vehicle[x3].matricula);
    } else {
        printf(" No trucks");
    }

    printf("\n\n");
}

/***********************************************
*
* @Finalidad: mostrar los detalles de un vehiculo
* @Parametros: Vehicle vehicle[] = estructura de los vehiculos
                int k             = numero de vehiculo
* @Retorno: no devuelve nada
*
************************************************/

void printDetails(Vehicle vehicle[], int k) {
    
    //Variables que se van a utilizar
    int op = 0, i = 0;
    float max = 0;

    op = vehicle[k].count_operations;
    printf("Plate: %s\n", vehicle[k].matricula);
    //Condicion que nos dice que tipo de vehiculo es
    if (strcmp(vehicle[k].type, "B") == 0) {
        printf("Type of vehicle: BIKE\n");
    } else if (strcmp(vehicle[k].type, "C") == 0) {
        printf("Type of vehicle: CAR\n");
    } else if (strcmp(vehicle[k].type, "T") == 0) {
        printf("Type of vehicle: TRUCK\n");
    }
    printf("Operations:\n");
    //Bucle for para recorrer las operaciones
    for (i = 0; i < op; i++) {
        printf("\t%d:%02d\t%d:%02d\t(%.2f euros)\n", vehicle[k].parking[i].hora_entrada, vehicle[k].parking[i].minutos_entrada, vehicle[k].parking[i].hora_salida, vehicle[k].parking[i].minutos_salida, vehicle[k].parking[i].precio);
        max += vehicle[k].parking[i].precio;
    }
    //Condicion que nos dice si el vehiculo esta en el parking y hay que añadir una operacion mas(solo la hora de entrada)
    if (vehicle[k].inParking == 1) {
        printf("\t%d:%02d\t**:**\t(**.** euros)\n", vehicle[k].parking[op].hora_entrada, vehicle[k].parking[op].minutos_entrada);
    }
    printf("Total paid: %.2f euros\n", max);
    printf("\n");
}

/***********************************************
*
* @Finalidad: validar la hora y los minutos
* @Parametros: int hora = hora
                int min  = minutos
* @Retorno: nos devuelve si la hora y los minutos son correctos
*
************************************************/

int validateTime(int hora, int min) {
    
    //Variables que se van a utilizar
    int found = 0;
    
    //Condicion que nos dice si la hora y los minutos son correctos
    if (hora >= 0 && hora <= 23 && min >= 0 && min <= 59) {
        found = 1;
    }

    return found;
}

/***********************************************
*
* @Finalidad: comprobar si un vehiculo esta en el parking
* @Parametros: Vehicle vehicle[] = estructura de los vehiculos
                int count         = numero de vehiculos
                char matricula[]  = matricula del vehiculo
* @Retorno: nos devuelve si el vehiculo esta en el parking
*
************************************************/

int isVehicleInParking(Vehicle vehicle[], int count, char matricula[]) {
    
    //Variables que se van a utilizar
    int found = 0;

    //Bucle for para recorrer los vehiculos
    for (int i = 0; i < count; i++) {
        if (strcmp(vehicle[i].matricula, matricula) == 0 && vehicle[i].inParking == 1) {
            found = 1;
        }
    }
    return found;
}

int main() {

    //Variables que se van a utilizar
    Tipo tipo;
    Vehicle vehicle[20] = {0};
    //Variables tipo string
    char tariffs[MAX_CHAR], input[MAX_CHAR], command[MAX_CHAR], command2[MAX_CHAR], hora[MAX_CHAR], min[MAX_CHAR], aux_type[MAX_CHAR], matricula_aux[MAX_CHAR];
    //Variables tipo char
    char trash;
    //Variables tipo int
    int pos = 0, count = 0, count2 = 0, i = 0, op = 0, j = 0, k = 0, flag = 0, found = 0, bikes = 0, trucks = 0, cars = 0;
    //Variables tipo int auxiliares
    int hora_aux = 0, min_aux = 0,  aux = 0, total1_aux = 0, total2_aux = 0;

    //Mostrar mensaje de bienvenida
    printf("Welcome to Parking LS!\n");
    printf("Enter tariffs: ");
    scanf("%s", tariffs);
    scanf("%c", &trash);
    printf("\n");

    //Llamada a la funcion parseVehicleData
    tipo = parseVehicleData(tariffs);

    //Bucle do while que nos permite introducir los comandos
    do {
        //Mostrar mensaje para introducir los comandos
        printf("Parking LS> ");
        fgets(input, MAX_CHAR, stdin);

        input[strlen(input) - 1] = '\0';

        pos = 0;
        pos = parseString(input, command, pos, ' ');
        //Condicion que nos dice si el comando es enter
        if (strcmp(command, "enter") == 0) {
            pos = parseString(input, aux_type, pos, ' ');
            //Condicion que nos dice si el comando es enter y el tipo de vehiculo es correcto
            if ((strcmp(aux_type, "B") != 0 && strcmp(aux_type, "C") != 0 && strcmp(aux_type, "T") != 0) || strlen(input) < 20) {
                printf("(ERROR) Wrong command\n");
                printf("\n");
            } else {
                //Leemos los datos de la matricula y la hora
                hora_aux = 0;
                min_aux = 0;
                pos = parseString(input, matricula_aux, pos, ' ');
                pos = parseString(input, hora, pos, ':');
                pos = parseString(input, min, pos, '\0');
                hora_aux = myAtoi(hora);
                min_aux = myAtoi(min);
                //Condicion que nos dice si la hora y los minutos son correctos
                if (validateTime(hora_aux, min_aux)) {
                    //Condicion que nos dice si el vehiculo cabe en el parking
                    if (count < MAX_VEHICLES) {
                        aux = 0;
                        //Bucle for para recorrer los vehiculos
                        for (i = 0; i < count2; i++) {
                            //Condicion que nos dice si el vehiculo esta en el parking
                            if (strcmp(matricula_aux, vehicle[i].matricula) == 0 && vehicle[i].inParking == 1) {
                                aux = 1;
                                //Condicion que nos dice si el vehiculo esta registrado
                            } else if (strcmp(matricula_aux, vehicle[i].matricula) == 0 && vehicle[i].inParking == 0 && vehicle[i].registrado == 1) {
                                aux = 2;
                                k = i;
                            }
                        }
                        //Condicion que nos guarda un vehiculo nuevo en el parking
                        if (aux == 0) {
                            op = vehicle[count2].count_operations;
                            strcpy(vehicle[count2].type, aux_type);
                            strcpy(vehicle[count2].matricula, matricula_aux);
                            vehicle[count2].inParking = 1;
                            vehicle[count2].registrado = 1;
                            vehicle[count2].parking[op].hora_entrada = hora_aux;
                            vehicle[count2].parking[op].minutos_entrada = min_aux;
                            vehicle[count2].parking[op].total_entrada = horaAMinutos(vehicle[count2].parking[op].hora_entrada, vehicle[count2].parking[op].minutos_entrada);
                            count++;
                            count2++;
                            printf("\n");
                            //Condicion que nos guarda un vehiculo que ya estaba registrado en el parking
                        } else if (aux == 2) {
                            op = vehicle[k].count_operations;
                            vehicle[k].inParking = 1;
                            vehicle[k].parking[op].hora_entrada = hora_aux;
                            vehicle[k].parking[op].minutos_entrada = min_aux;
                            vehicle[k].parking[op].total_entrada = horaAMinutos(vehicle[k].parking[op].hora_entrada, vehicle[k].parking[op].minutos_entrada);
                            count++;
                            printf("\n");
                            //Condicion que nos dice si el vehiculo ya esta en el parking
                        } else if (aux == 1) {
                            printf("(ERROR) This vehicle is already in the parking!\n");
                            printf("\n");
                        }
                        //Condicion que nos dice si el parking esta lleno
                    } else {
                        printf("(ERROR) No more vehicles are accepted\n");
                        printf("\n");
                    }
                    //Condicion que nos dice si la hora y los minutos son incorrectos
                } else {
                    printf("(ERROR) Wrong time format\n");
                    printf("\n");
                }
            }
            //Condicion que nos dice si el comando es exit
        } else if (strcmp(command, "exit") == 0) {
            k = 0;
            //Condicion que nos dice si el comando es exit incorrecto
            if (strlen(input) < 17) {
                printf("(ERROR) Wrong command\n");
                printf("\n");
            } else {
                //Leemos los datos de la matricula y la hora
                hora_aux = 0;
                min_aux = 0;
                pos = parseString(input, matricula_aux, pos, ' ');
                pos = parseString(input, hora, pos, ':');
                pos = parseString(input, min, pos, '\0');
                hora_aux = myAtoi(hora);
                min_aux = myAtoi(min);
                //Condicion que nos dice si la hora y los minutos son correctos
                if (validateTime(hora_aux, min_aux)) {
                    found = 0;
                    //Bucle for para recorrer los vehiculos
                    for (i = 0; i < count2; i++) {
                        //Condicion que nos dice si el vehiculo esta en el parking
                        if (strcmp(matricula_aux, vehicle[i].matricula) == 0 && vehicle[i].inParking == 1) {
                            found = 1;
                            k = i;
                        }
                    }
                    //Condicion que nos dice si el vehiculo esta en el parking
                    if (found == 1) {
                        op = vehicle[k].count_operations;
                        total1_aux = vehicle[k].parking[op].total_entrada;
                        total2_aux = horaAMinutos(hora_aux, min_aux);
                        //Condicion que nos dice si la hora de salida es correcta y coherente
                        if (total1_aux > total2_aux) {
                            printf("(ERROR) Incoherent exit time\n");
                            printf("\n");
                            //Condicion que nos dice si la hora de salida es correcta
                        } else {
                            //Nos guardamos los datos de la hora de salida
                            vehicle[k].parking[op].hora_salida = hora_aux;
                            vehicle[k].parking[op].minutos_salida = min_aux;
                            vehicle[k].parking[op].total_salida = total2_aux;
                            vehicle[k].inParking = 0;
                            //Calculamos el precio y lo mostramos
                            vehicle[k].parking[op].precio = calcularPrecio(vehicle, tipo, k, op);
                            printf("Operation closed: %.2f euros\n", vehicle[k].parking[op].precio);
                            printf("\n");
                            vehicle[k].count_operations++;
                            count--;
                        }
                        //Condicion que nos dice si el vehiculo no esta en el parking
                    } else {
                        printf("(ERROR) This vehicle is not in the parking\n");
                        printf("\n");
                    }
                    //Condicion que nos dice si la hora y los minutos son incorrectos
                } else {
                    printf("(ERROR) Wrong time format\n");
                    printf("\n");
                }
            }
            //Condicion que nos dice si el comando es show
        } else if (strcmp(command, "show") == 0) {
            pos = parseString(input, command2, pos, ' ');
            //Condicion que nos dice si el comando es show occupation
            if (strcmp(command2, "occupation") == 0) {
                if (strlen(input) == 15) {
                    bikes = 0;
                    cars = 0;
                    trucks = 0;

                    //Bucle for para recorrer los vehiculos
                    for (j = 0; j < count2; j++) {
                        //Condicion que nos dice si el vehiculo es una moto
                        if (strcmp(vehicle[j].type, "B") == 0 && vehicle[j].inParking == 1) {
                            bikes++;
                            //Condicion que nos dice si el vehiculo es un coche
                        } else if (strcmp(vehicle[j].type, "C") == 0 && vehicle[j].inParking == 1) {
                            cars++;
                            //Condicion que nos dice si el vehiculo es un camion
                        } else if (strcmp(vehicle[j].type, "T") == 0 && vehicle[j].inParking == 1) {
                            trucks++;
                        }
                    }
                    //Llamada a la funcion showOccupation
                    showOccupation(bikes, trucks, cars, vehicle, count2);
                    //Condicion que nos dice si el comando es incorrecto
                } else {
                    printf("(ERROR) Wrong command\n");
                    printf("\n");
                }
                //Condicion que nos dice si el comando es show detail
            } else if (strcmp(command2, "detail") == 0) {
                if (strlen(input) == 19) {
                    pos = parseString(input, matricula_aux, pos, '\0');
                    found = 0;
                    //Bucle for para recorrer los vehiculos
                    for (i = 0; i < count2; i++) {
                        //Condicion que nos dice si el vehiculo esta en el parking
                        if (strcmp(matricula_aux, vehicle[i].matricula) == 0) {
                            found = 1;
                            k = i;
                        }
                    }
                    //Condicion que nos dice si el vehiculo esta en el parking
                    if (found == 1) {
                        //Llamada a la funcion printDetails
                        printDetails(vehicle, k);
                        //Condicion que nos dice si el vehiculo no esta en el parking
                    } else {
                        printf("(ERROR) This vehicle never used the parking\n");
                        printf("\n");
                    }
                    //Condicion que nos dice si el comando es incorrecto
                } else {
                    printf("(ERROR) Wrong command\n");
                    printf("\n");
                }
                //Condicion que nos dice si el comando es incorrecto
            } else {
                printf("(ERROR) Wrong command\n");
                printf("\n");
            }
            //Condicion que nos dice si el comando es quit
        } else if (strcmp(command, "quit") == 0) {
            //Mostramos un mensaje de despedida
            printf("See you later!");
            flag = 1;
            //Condicion que nos dice si el comando es incorrecto
        } else {
            printf("(ERROR) Wrong command\n");
            printf("\n");
        }
    } while (flag == 0);

    return 0;
}
