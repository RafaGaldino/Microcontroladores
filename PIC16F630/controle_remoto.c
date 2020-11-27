/*
 * File:   main.c
 * Author: Rafael G. Andrade
 * Created on 25 de Novembro de 2020, 19:00
 */

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA3/MCLR pin function select (RA3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>

#define _XTAL_FREQ 4000000
#define IR_RECEIVER PORTAbits.RA0
#define COOLER PORTAbits.RA2
#define GREEN_LED PORTCbits.RC5
#define BLUE_LED PORTCbits.RC4 
#define RED_LED PORTCbits.RC3

void main(void) {
    OPTION_REG = 0b11011000;
    OSCCAL = 0xfc;
    TRISA = 0x01;
    WPUA = 0x00;
    PORTA = 0x00;
    CMCON = 0x47;
    TRISC = 0x00;  
    PORTC = 0x00;
    
    while(1){
        
        while(IR_RECEIVER);
        
        if(IR_RECEIVER == 0){
            code++;
            if(code > 7) code = 0;
            switch(code){
                case 1:
                    GREEN_LED = 1;
                    BLUE_LED = 0;
                    RED_LED = 0;
                    COOLER = 0;
                    break;
                case 2:
                    GREEN_LED = 0;
                    BLUE_LED = 1;
                    RED_LED = 0;
                    COOLER = 0;
                    break;
                case 3:
                    GREEN_LED = 0;
                    BLUE_LED = 0;
                    RED_LED = 1;
                    COOLER = 0;
                    break;
                case 4:
                    GREEN_LED = 1;
                    BLUE_LED = 1;
                    RED_LED = 0;
                    COOLER = 0;
                    break;
                case 5:
                    GREEN_LED = 0;
                    BLUE_LED = 1;
                    RED_LED = 1;
                    COOLER = 0;
                    break;
                case 6:
                    GREEN_LED = 1;
                    BLUE_LED = 0;
                    RED_LED = 1;
                    COOLER = 0;
                    break;
                case 7:
                    GREEN_LED = 0;
                    BLUE_LED = 0;
                    RED_LED = 0;
                    COOLER = 1;
                    break;   
                default:
                    GREEN_LED = 0;
                    BLUE_LED = 0;
                    RED_LED = 0;
                    COOLER = 0;     
            }
            __delay_ms(500);
        }
    }
    return;
}
