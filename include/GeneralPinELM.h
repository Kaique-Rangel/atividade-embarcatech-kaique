#ifndef GENERALPINELM_H
#define GENERALPINELM_H

// definição dos pinos a serem utilizados
#define LEDMPIN 7
#define BUZZERPIN 21
#define BUTTONPIN 22

//definição dos parâmetros pertinentes à manipulação do teclado matricial
#define COLINIT 8
#define ROWINIT 12

#define NROWS 4
#define NCOLUMNS 4

#include "hardware/pio.h"

//Structs para manipulação da PIO e das cores dos LEDs
typedef struct PIORefs {
    PIO Ref;
    uint Offset;
    uint StateMachine;
} refs;

typedef struct RGB {
    double Red;
    double Green;
    double Blue;
} RGB;

// Funções de configuração
refs InitConf();
refs InitPIO();
void SetInput(int);
void SetOutput(int);
void SetInterruption(int);
void HandleInterruption();

#endif