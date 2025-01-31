#include <GeneralPinELM.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"

// Iniciam o monitor serial e o PIO 
refs InitConf(){
    refs pio;

    pio.Ref = pio0;
    stdio_init_all();
    if (set_sys_clock_khz(128000, false))
        printf("Clock configurado para %ld\n", clock_get_hz(clk_sys));
    pio.Offset = pio_add_program(pio.Ref, &pio_matrix_program);
    pio.StateMachine = pio_claim_unused_sm(pio.Ref, true);
    //PrintPIO(pio);
    return pio;
}

refs InitPIO(){
    refs pio = InitConf();
    pio_matrix_program_init(pio.Ref, pio.StateMachine, pio.Offset, LEDMPIN);
    return pio;
}

// Iniciam e dão a direção dos pinos
void SetInput(int PIN){
    gpio_init(PIN);
    gpio_set_dir(PIN, false);
    gpio_pull_down(PIN);
}

void SetOutput(int PIN){
    gpio_init(PIN);
    gpio_set_dir(PIN, true);
    gpio_put(PIN, 0);
}





void SetInterruption(int PIN){
    //SetInput(PIN);
    gpio_init(PIN);
    gpio_set_dir(PIN, false);
    gpio_pull_down(PIN);
    printf("Interrupção configurada!\n");
    gpio_set_irq_enabled_with_callback(PIN, GPIO_IRQ_EDGE_RISE, 1, &HandleInterruption);
}

void HandleInterruption(){
    printf("Interrupção ativada!\n"); // indica que a interrupção foi ativada
    reset_usb_boot(0,0);
}
