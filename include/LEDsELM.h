#ifndef LEDSELM_H
#define LEDSELM_H

#include "GeneralPinELM.h"

// tamanho do vetor de LEDs
#define NPIXELS 25

// Funções de manipulação dos LEDs
void PrintRGB(RGB);
void PrintPIO(refs);
double* Drawing(int);
void Draw(double*, uint32_t, refs, RGB*);
void DrawFrames(double*, uint32_t, refs, RGB*, int, int*);
void TurnLedsOff(uint32_t led, refs pio);

#endif