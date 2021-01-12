/*
 * File:   main.c
 * Author: Blake Burgess
 *
 * Created on December 31, 2020, 11:06 PM
 */

#include <xc.h>

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR pin function select (RA5/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOD Reset enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Code Protection bits (Program memory code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ  37000

void init() {
    PCONbits.OSCF = 0;      // 37 KHz mode (in combination with FOSC = INTOSCIO config)
    
    PORTB = 0;
    
    TRISBbits.TRISB1 = 1;   // In
    TRISBbits.TRISB2 = 1;   // In
    TRISBbits.TRISB3 = 0;   // Out
}

unsigned stepCounter = 0;

void toggle() {
    PORTBbits.RB3 = !PORTBbits.RB3;
}

void main() {
    init();
    
    unsigned counter = PORTBbits.RB1 | (PORTBbits.RB2 << 1);
    
    for (unsigned i = 0; i < counter; i++)
    {
        __delay_ms(250);
        toggle();
        __delay_ms(250);
        toggle();
    }
    
    SLEEP();
}

