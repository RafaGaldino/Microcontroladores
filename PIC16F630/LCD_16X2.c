/*
 * File:   main.c
 * Author: Rafael G. Andrade
 * Created on 7 de Dezembro de 2020, 21:07
 */

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA3/MCLR pin function select (RA3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000
#define RS          PORTAbits.RA0
#define enable      PORTAbits.RA1
#define D4          PORTAbits.RA2
#define D5          PORTCbits.RC0
#define D6          PORTCbits.RC1
#define D7          PORTCbits.RC2
#define clean_code  0x01 // Config. Tela ("limpa" tela do display)
#define row1_code   0x80 // Vai para linha 1.
#define row2_code   0xC0 // Vai para linha 2.

void LCD_init(void);
void LCD_char(char letter);
void LCD_command(int code);
void putch(char data);

void main(void) {
    OSCCAL = 0xff;
    OPTION_REG = 0x00;
    CMCON = 0x07;
    WPUA = 0x00;
    TRISA = 0x00;
    TRISC = 0x00;
    PORTA = 0x00;
    PORTC = 0x00;
    
    LCD_init();
    
    while(1){
        LCD_command(row1_code);
        printf("Rafael Galdino");
        LCD_command(row2_code);
        printf("Andrade");
        __delay_ms(1500);
        LCD_command(clean_code);
        __delay_ms(1000);
        printf(":)");
        __delay_ms(1500);
        LCD_command(clean_code);
        __delay_ms(15);
        printf(";)");
        __delay_ms(500);
        LCD_command(clean_code);
        __delay_ms(1000);
        
    }
   
    return;
}

void LCD_init(void){
    LCD_command(0x03);
    LCD_command(0x02);
    //Config. Funções (N° de bits, N° de colunas, N° de linhas e matriz de pixels) 
    LCD_command(0x28);  
    //Config. Display(On/Off e Cursor)
    LCD_command(0x0C);  
    //Config. Cursor (Sentido deslocamento)
    LCD_command(0x06);
    LCD_command(clean_code);
    __delay_ms(20);
}

void LCD_command(int code){
    RS = 0; //coloca LCD no modo comando
    __delay_ms(50);
    D4 = (code >> 4)& 0x01;
    D5 = (code >> 5)& 0x01;
    D6 = (code >> 6)& 0x01; 
    D7 = (code >> 7)& 0x01;
    enable = 1;
    __delay_us(1);
    enable = 0;
    D4 = (code >> 0)& 0x01;
    D5 = (code >> 1)& 0x01; 
    D6 = (code >> 2)& 0x01; 
    D7 = (code >> 3)& 0x01;
    enable = 1;
    __delay_us(1);
    enable = 0;
}

void LCD_char(char letter){
    RS = 1; //coloca LCD no modo dado
    __delay_ms(50);
    D4 = (letter >> 4)& 0x01;
    D5 = (letter >> 5)& 0x01;
    D6 = (letter >> 6)& 0x01; 
    D7 = (letter >> 7)& 0x01;
    enable = 1;
    __delay_us(1);
    enable = 0;
    D4 = (letter >> 0)& 0x01;
    D5 = (letter >> 1)& 0x01; 
    D6 = (letter >> 2)& 0x01; 
    D7 = (letter >> 3)& 0x01;
    enable = 1;
    __delay_us(1);
    enable = 0;
}

void putch(char data) {
    LCD_char(data);
}
