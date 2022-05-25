#include "assembly.h"
<<<<<<< HEAD
#include "generateMap.h"
#include "lcd/lcd.h"
#include "utils.h"
#include "lcd/img.h"
#include <string.h>

void Inp_init(void) { gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8); }
=======
#include "generateMap.c"
#include "lcd/lcd.h"
#include "utils.h"
#include <string.h>

void Inp_init(void) {
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}
>>>>>>> 688555eea9b5e137ef481ea81a4362f733d5faaa

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

<<<<<<< HEAD
=======


>>>>>>> 688555eea9b5e137ef481ea81a4362f733d5faaa
int main(void) {
    IO_init();// init OLED
    // YOUR CODE HERE
    LCD_Clear(BLACK);
    //    LCD_Fill(0, 53, 160, 60, WHITE60);
<<<<<<< HEAD
    LCD_ShowPic(0, 0, 11, 19, cactus1);
    LCD_ShowPic(20, 0, 31, 19, cactus2);
=======
    LCD_ShowString(20, 20, "qwe", MAGENTA);
>>>>>>> 688555eea9b5e137ef481ea81a4362f733d5faaa

    //    while (1) {
    //        LCD_Fill(0, 53, 160, 60, WHITE60);
    //        delay_1ms(100);
    //        LCD_Fill(0, 53, 160, 60, BLACK);
    //        delay_1ms(100);
    //    }
}
