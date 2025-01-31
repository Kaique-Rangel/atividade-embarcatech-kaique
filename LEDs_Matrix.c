#include <stdio.h>
#include "pico/stdlib.h"
#include <KeyBoardELM.h>
#include <GeneralPinELM.h>
#include <LEDsELM.h>
#include "hardware/clocks.h"
#include "pico/bootrom.h"

int main()
{
    // printf("COMEÇOU\n");
    const int ROWS[NROWS] = {ROWINIT + 3, ROWINIT + 2, ROWINIT + 1, ROWINIT};
    const int COLUMNS[NCOLUMNS] = {COLINIT + 3, COLINIT + 2, COLINIT + 1, COLINIT};
    const char(*KEYMAP)[NCOLUMNS];

    refs pio;

    double *drawing = Drawing(0);

    // printf("ANTES DE INICIAR\n");
    pio = InitPIO();
    //PrintPIO(pio);

    // printf("Programa iniciado!\n");
    // printf("Desenho iniciado: \n");
    // for (int i = 0; i < NPIXELS; i++)
    //     printf("%lf ", drawing[i]);

    InitKeyboard(ROWS, COLUMNS);
    // printf("DEPOIS DE INICIAR\n");

    SetOutput(BUZZERPIN);

    KEYMAP = KeyMap();

    char key;
    uint32_t led = 0;
    RGB color[2] = {
        {.Red = 0.0, .Green = 1.0, .Blue = 0.0}, 
        {.Red = 1.0, .Green = 1.0, .Blue = 1.0}};

    //PrintRGB(color[1]);

    int position[2] = {0,0};
    Draw(drawing, led, pio, color);

    while (true)
    {
        key = ReadMap(KEYMAP, ROWS, COLUMNS);
        if (key == '1')
        {
            position[0] = 21;
            position[1] = 26;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '3')
        {
            color[0].Red = 0.3;
            color[0].Blue = 0.9;
            color[0].Green = 0.3;
    
            position[0] = 15;
            position[1] = 20;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '4')
        {
            color[0].Red = 1.0;
            color[0].Blue = 0.0;
            color[0].Green = 0.0;
    
            position[0] = 10;
            position[1] = 14;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '5')
        {
            color[0].Red = 0.5;
            color[0].Blue = 0.7;
            color[0].Green = 0.3;
    
            position[0] = 30;
            position[1] = 36;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '6')
        {
            color[0].Red = 1.0;
            color[0].Blue = 1.0;
            color[0].Green = 0.6;

            position[0] = 47;
            position[1] = 50;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == 'A')
        {
            RGB none = {.Red = 0.0, .Blue = 0.0, .Green = 0.0};
            color[0] = none;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == 'B')
        {
            RGB blue = {.Red = 0.0, .Blue = 1.0, .Green = 0.0};
            color[0] = blue;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == 'C')
        {
            RGB red = {.Red = 0.8, .Blue = 0.0, .Green = 0.0};
            color[0] = red;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == 'D')
        {
            RGB green = {.Red = 0.0, .Blue = 0.0, .Green = 0.5};
            color[0] = green;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == '#')
        {
            RGB green = {.Red = 0.2, .Blue = 0.2, .Green = 0.2};
            color[0] = green;
            color[1] = color[0];
            Draw(drawing, led, pio, color);
        }
        else if (key == '*'){
            TurnLedsOff(led, pio);
            break;
        }
        sleep_ms(100);
    }
    printf("Recolocando em Bootsel!");
    reset_usb_boot(0,0);
    return 0;
}
