#include <stdio.h>
#include "pico/stdlib.h"
#include <KeyBoardELM.h>
#include <GeneralPinELM.h>
#include <LEDsELM.h>
#include "hardware/clocks.h"
#include "pico/bootrom.h"

#define MAX_HISTORY 10  // Defina o número máximo de animações anteriores que podemos armazenar

int currentAnimation = 0;   // Variável para controlar a animação atual
int animationHistory[MAX_HISTORY];  // Pilha de animações anteriores
int historyIndex = -1;  // Índice da pilha

// Função para alternar a animação
void SwitchAnimation() {
    if (historyIndex < MAX_HISTORY - 1) {
        animationHistory[++historyIndex] = currentAnimation;  // Empilha a animação atual
    } else {
        // Se a pilha estiver cheia, desloca as animações para baixo
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            animationHistory[i] = animationHistory[i + 1];
        }
        animationHistory[MAX_HISTORY - 1] = currentAnimation;  // Empilha a animação atual
    }
    currentAnimation = (currentAnimation + 1) % 10;  // Altera entre 0 a 9 animações
}

// Função para voltar à animação anterior
void GoToPreviousAnimation() {
    if (historyIndex >= 0) {
        currentAnimation = animationHistory[historyIndex--];  // Desempilha a animação anterior
    }
}

// Função para desenhar a animação com base na escolha
void DrawSelectedAnimation(refs pio, RGB *color) {
    double *drawing = Drawing(0);  // Inicializa o desenho
    uint32_t led = 0;  // Inicializa o LED

    // Inicializa a variável position antes de usá-la
    int position[2] = {0, 0};  // {linha, coluna}

    // Baseado no valor de currentAnimation, mostramos a animação
    switch (currentAnimation) {
        case 0:
            position[0] = 21;  // Linha
            position[1] = 26;  // Coluna
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 1:
            color[0].Red = 0.3;
            color[0].Blue = 0.9;
            color[0].Green = 0.3;
            position[0] = 15;
            position[1] = 20;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 2:
            color[0].Red = 1.0;
            color[0].Blue = 0.0;
            color[0].Green = 0.0;
            position[0] = 10;
            position[1] = 14;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 3:
            color[0].Red = 0.5;
            color[0].Blue = 0.7;
            color[0].Green = 0.3;
            position[0] = 30;
            position[1] = 36;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 4:
            color[0].Red = 1.0;
            color[0].Blue = 1.0;
            color[0].Green = 0.6;
            position[0] = 47;
            position[1] = 50;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 5:
            color[0].Red = 0.9;
            color[0].Blue = 0.2;
            color[0].Green = 0.8;
            position[0] = 51;
            position[1] = 56;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 6:
            color[0].Red = 0.1;
            color[0].Blue = 0.9;
            color[0].Green = 0.3;
            position[0] = 60;
            position[1] = 65;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 7:
            color[0].Red = 0.7;
            color[0].Blue = 0.1;
            color[0].Green = 0.8;
            position[0] = 65;
            position[1] = 70;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 8:
            color[0].Red = 0.5;
            color[0].Blue = 0.8;
            color[0].Green = 0.2;
            position[0] = 75;
            position[1] = 80;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        case 9:
            color[0].Red = 0.8;
            color[0].Blue = 0.3;
            color[0].Green = 0.4;
            position[0] = 80;
            position[1] = 85;
            DrawFrames(drawing, led, pio, color, 800, position);
            break;
        default:
            break;
    }
}

int main() {
    const int ROWS[NROWS] = {ROWINIT + 3, ROWINIT + 2, ROWINIT + 1, ROWINIT};
    const int COLUMNS[NCOLUMNS] = {COLINIT + 3, COLINIT + 2, COLINIT + 1, COLINIT};
    const char(*KEYMAP)[NCOLUMNS];

    refs pio;
    double *drawing = Drawing(0);
    pio = InitPIO();
    
    InitKeyboard(ROWS, COLUMNS);  // Inicializa o teclado
    SetOutput(BUZZERPIN);         // Inicializa o buzzer

    KEYMAP = KeyMap();  // Mapeia as teclas

    char key;
    uint32_t led = 0;
    RGB color[2] = {
        {.Red = 0.0, .Green = 1.0, .Blue = 0.0},
        {.Red = 1.0, .Green = 1.0, .Blue = 1.0}
    };

    int position[2] = {0, 0};  // Inicializa as coordenadas de position
    Draw(drawing, led, pio, color);

    while (true) {
        key = ReadMap(KEYMAP, ROWS, COLUMNS);  // Lê o teclado

        if (key == 'A') {
            SwitchAnimation();  // Altera a animação
            DrawSelectedAnimation(pio, color);  // Desenha a animação selecionada
        }
        else if (key == 'B') {
            GoToPreviousAnimation();  // Volta à animação anterior
            DrawSelectedAnimation(pio, color);  // Desenha a animação restaurada
        }
        else if (key == 'C') {
            RGB red = {.Red = 0.8, .Blue = 0.0, .Green = 0.0};
            color[0] = red;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == 'D') {
            RGB green = {.Red = 0.0, .Blue = 0.0, .Green = 0.5};
            color[0] = green;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == '#') {
            RGB green = {.Red = 0.2, .Blue = 0.2, .Green = 0.2};
            color[0] = green;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == '*') {
            TurnLedsOff(led, pio);  // Desliga os LEDs
            break;  // Encerra o programa
        }

        sleep_ms(100);  // Aguarda um pouco para evitar leituras rápidas
    }

    // Após sair do loop, reinicia o Raspberry Pi
    printf("Recolocando em Bootsel!\n");
    reset_usb_boot(0, 0);

    return 0;
}
