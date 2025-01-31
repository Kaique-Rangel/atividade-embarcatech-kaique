#include <LEDsELM.h>
#include <GeneralPinELM.h>
#include <math.h>
#include <stdio.h>

//Prints de debug para os endereços configurados do PIO e das cores
void PrintRGB(RGB color)
{
    printf("---RGB---\n");
    printf("Red: %lf\n", color.Red);
    printf("Green: %lf\n", color.Green);
    printf("Blue: %lf\n", color.Blue);
    printf("---------\n");
}

void PrintPIO(refs pio)
{
    printf("---PIO refs---\n");
    printf("PIO Addr: %d\n", pio.Ref);
    printf("Offset inst: %d\n", pio.Offset);
    printf("State Machine no: %d\n", pio.StateMachine);
    printf("FIFO empty: %d\n", pio_sm_is_rx_fifo_empty(pio.Ref, pio.StateMachine));
    printf("FIFO full: %d\n", pio_sm_is_rx_fifo_full(pio.Ref, pio.StateMachine));
    printf("---------\n");
}

// Retorna os vetores com as figuras a serem desenhadas na matriz de LEDs
double *Drawing(int frame)
{
    // Desenho X
    static double firstFrameX[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double secondFrameX[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double thirdFrameX[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double fourthFrameX[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double fifthFrameX[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0};

    static double sixthFrameX[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0};

    // Desenho da Cuz
    static double firstFrameCruz[] = {
        1.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 0.0, 1.0, 0.0, 1.0};

    static double secondFrameCruz[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double thirdFrameCruz[] = {
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 0.0, 0.0};

    static double fourthFrameCruz[] = {
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0};

    static double fifthFrameCruz[] = {
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 0.0, 0.0};

    static double sixthFrameCruz[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double seventhFrameCruz[] = {
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0};

// Letra M corrigida
static double firstFrameM[] = {
    1.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 1.0
};

static double secondFrameM[] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

static double thirdFrameM[] = {
    1.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 1.0
};

static double fourthFrameM[] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

static double fifthFrameM[] = {
    1.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 1.0
};
    // Frames de Quadrados
    static double firstFrameQ[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double secondFrameQ[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0};

    static double thirdFrameQ[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double fourthFrameQ[] = {
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0};

    static double fifthFrameQ[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0};

    static double sixthFrameQ[] = {
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 0.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0};

    // Frame 1: Estrela na parte superior
    static double frame1[] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0};

    // Frame 2: Estrela na parte superior
    static double frame2[] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0};

// Frame 3: Estrela no centro
    static double frame3[] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0};

// Frame 4: Estrela na parte inferior
    static double frame4[] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0};

        
    // Desenho padrão
    static double defaultArray[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    switch (frame)
    {
    case 21:
        return firstFrameX;
        break;
    case 22:
        return secondFrameX;
        break;
    case 23:
        return thirdFrameX;
        break;
    case 24:
        return fourthFrameX;
        break;
    case 25:
        return fifthFrameX;
        break;
    case 26:
        return sixthFrameX;
        break;
    case 47:
        return frame1;
        break;
    case 48:
        return frame2; 
        break;
    case 49:
        return frame3;
        break;
    case 50:
        return frame4;
        break;
    case 30:
        return firstFrameCruz;
        break;
    case 31:
        return secondFrameCruz;
        break;
    case 32:
        return thirdFrameCruz;
        break;
    case 33:
        return fourthFrameCruz;
        break;
    case 34:
        return fifthFrameCruz;
        break;
    case 35:
        return sixthFrameCruz;
        break;
    case 36:
        return seventhFrameCruz;
        break;
    case 10:
        return firstFrameM;
        break;
    case 11:
        return secondFrameM;
        break;
    case 12:
        return thirdFrameM;
        break;
    case 13:
        return fourthFrameM;
        break;
    case 14:
        return fifthFrameM;
        break;
    case 15:
        return firstFrameQ;
        break;
    case 16:
        return secondFrameQ;
        break;
    case 17:
        return thirdFrameQ;
        break;
    case 18:
        return fourthFrameQ;
        break;
    case 19:
        return fifthFrameQ;
        break;
    case 20:
        return sixthFrameQ;
        break;
    default:
        return defaultArray;
    }
}

// Retorna as cores dos LEDs a serem utilizadas
uint32_t RGBMatrix(RGB color)
{
    unsigned char R, G, B;
    R = color.Red * 255;
    G = color.Green * 255;
    B = color.Blue * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void PrintBinary(int num)
{
    printf("\n");
    int i;
    for (i = 31; i >= 0; i--)
    {
        (num & (1 << i)) ? printf("1") : printf("0");
    }
    printf("\n");
}


//Desenha uma figura na matriz
void Draw(double *drawing, uint32_t led, refs pio, RGB *color)
{
    //    PrintPIO(pio);
    //    PrintRGB(color);
    RGB finalColor;

    for (int16_t i = 0; i < NPIXELS; i++)
    {
        // printf("Elemento %d\n", i);

        if (drawing[i])
        {
            finalColor.Red = color[0].Red;
            finalColor.Green = color[0].Green;
            finalColor.Blue = color[0].Blue;
        }
        else
        {
            finalColor.Red = color[1].Red;
            finalColor.Green = color[1].Green;
            finalColor.Blue = color[1].Blue;
        }
        led = RGBMatrix(finalColor);
        pio_sm_put_blocking(pio.Ref, pio.StateMachine, led);
        // printf("LED %d: %d\n", i, led);
        //  PrintRGB(color);
        //  printf("LED: %d\n", led);
        //  PrintPIO(pio);
        //  PrintBinary(led);
        //  printf("LED %d: %d\nR: %d, G: %d, B: %d\n ", i, led, color.Red, color.Green, color.Blue);
    }
}

//Desenha uma animação, uma sequência de figuras
void DrawFrames(double *drawing, uint32_t led, refs pio, RGB *color, int delay, int *position)
{
    gpio_put(BUZZERPIN, 1);
    for (int i = position[0]; i <= position[1]; i++)
    {
        drawing = Drawing(i);
        Draw(drawing, led, pio, color);
        sleep_ms(delay);
    }
    gpio_put(BUZZERPIN, 0);
    for (int i = position[1]; i >= position[0]; i--)
    {
        drawing = Drawing(i);
        Draw(drawing, led, pio, color);
        sleep_ms(delay);
    }

    drawing = Drawing(0);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);
}

// Apaga os LEDs
void TurnLedsOff(uint32_t led, refs pio)
{
    RGB turnedOff[2] = {{.Red = 0.0, .Green = 0.0, .Blue = 0.0}, {.Red = 0.0, .Green = 0.0, .Blue = 0.0}};
    double *drawing = Drawing(0);
    Draw(drawing, led, pio, turnedOff);
}
