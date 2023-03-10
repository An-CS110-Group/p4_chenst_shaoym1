#include "assembly.h"
#include "generateMap.c"
#include "lcd/lcd.h"
#include "utils.h"
#include <string.h>

void Inp_init(void) {
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    RCU_CFG0 |= (0b10 << 14) | (1 << 28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;
}

void IO_init(void) {
    Inp_init();// inport init
    Adc_init();// A/D init
    Lcd_Init();// LCD init
}



int main(void) {
    IO_init();// init OLED
    // YOUR CODE HERE
    LCD_Clear(BLACK);
    //    LCD_Fill(0, 53, 160, 60, WHITE60);
    LCD_ShowString(20, 20, "qwe", MAGENTA);

    //    while (1) {
    //        LCD_Fill(0, 53, 160, 60, WHITE60);
    //        delay_1ms(100);
    //        LCD_Fill(0, 53, 160, 60, BLACK);
    //        delay_1ms(100);
    //    }
}
