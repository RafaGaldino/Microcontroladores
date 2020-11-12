/*
 * File:   main.c
 * Author: Rafael G. Andrade
 * Created on 4 de Novembro de 2020, 16:32
 * YouTube: https://youtu.be/xZzauoAKpJo
 */

// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = OFF      // Master Clear Enable (GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD)

#include <xc.h>
#define _XTAL_FREQ 4000000
#define OVERFLOW 2

void main(void) {
    unsigned char previous = 1;
    unsigned char code = 0;
    unsigned char count = OVERFLOW;
    OPTION = 0b10010111;
    TRISGPIO = 0x08;
    GPIO = 0x00;
    TMR0 = 0x00;
    
    while(1){
        if(GPIObits.GP3 == 0 && previous == 1){
            code++;
            if(code > 7) code = 0;
        }
        previous = GPIObits.GP3;
        
        switch(code){
            case 1:
                GPIO = 0x01;
                break;
            case 2:
                GPIO = 0x02;
                break;
            case 3:
                GPIO = 0x04;
                break;
            case 4:
                GPIO = 0x03;
                break;
            case 5:
                GPIO = 0x06;
                break;
            case 6:
                GPIO = 0x05;
                break;
            case 7:
                if(TMR0 == 0xff){
                    TMR0 = 0x00;
                    count--;
                    if(count == 0){
                        count = OVERFLOW;
                        if(GPIObits.GP0 == 0){
                            GPIO = 0x01;
                        }else{
                            GPIO = 0x00;
                        }  
                    }
                }
                break;
            default:
                GPIO = 0x00;
        }
        __delay_ms(1);
    }
    return;
}
