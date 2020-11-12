/*
 * File:   main.c
 * Author: Rafael G. Andrade
 * YouTube: https://youtu.be/rTK-vIT7luQ
 * Created on 10 de Novembro de 2020, 00:08
 */

// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = OFF      // Master Clear Enable (GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD)

#include <xc.h>
#define _XTAL_FREQ 4000000
#define NUM_OVERFLOW 80

void main(void) {
    unsigned char previous = 1;
    unsigned char blink = 0;
    unsigned char count = NUM_OVERFLOW;
    OPTION = 0b10010111;
    TRISGPIO = 0x08;
    GPIO = 0x00;
    TMR0 = 0x00;
    
    while(1){
        if(GPIObits.GP3 == 0 && previous == 1){
            blink = !blink;
            if(GPIObits.GP1 == 0 && GPIObits.GP2 == 0){
                GPIO = 0x03;
            }
        }
        previous = GPIObits.GP3;
        
        if(blink){
            if(TMR0 == 0xff){
                TMR0 = 0x00;
                count--;
                if(count == 0){
                    count = NUM_OVERFLOW;
                    if(GPIObits.GP0 == 0){
                        GPIO = 0x03;
                    }else{
                        GPIO = 0x04;
                    }
                }
            }
        }else{
            GPIO = 0x00;
        }
        __delay_ms(1);
    }
    return;
}
