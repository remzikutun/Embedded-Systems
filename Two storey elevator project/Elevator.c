#include <pic16f84.h>
#include <builtins.h>
#include <stdbool.h>

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)
#define _XTAL_FREQ 4000000

#define F1_BUTTON PORTAbits.RA0
#define F2_BUTTON PORTAbits.RA1
#define F1_SENSOR PORTAbits.RA2
#define F2_SENSOR PORTAbits.RA3
#define D_CSENSOR PORTAbits.RA4
#define M_UP PORTBbits.RB0
#define M_DOWN PORTBbits.RB1
#define F1_BLED PORTBbits.RB2
#define F2_BLED PORTBbits.RB3
#define M_DOOROPEN PORTBbits.RB4
#define M_DOORCLOSE PORTBbits.RB5

void main(void)
{
    TRISB = 0b00000000;
    TRISA = 0b00011111;
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    
    bool doorflag = 0;
    bool doorflag2 = 0;
    while(1)
    {
        if (F1_BUTTON == 1 && F2_SENSOR == 1 && (M_DOORCLOSE != 1 && M_DOOROPEN != 1))
        {
            M_DOWN = 1;
            F1_BLED = 1;
            doorflag = 1;
        }
        if ((F1_SENSOR == 1 && F1_BUTTON == 1) && (M_DOWN != 1 && M_UP != 1) && D_CSENSOR != 1)
        {
            F1_BLED = 1;
            M_DOOROPEN = 1;
            __delay_ms(1000);
            F1_BLED = 0;
            M_DOOROPEN = 0;
            __delay_ms(3000);
            M_DOORCLOSE = 1;
            __delay_ms(1000);
            M_DOORCLOSE = 0;
        }
        if (F2_BUTTON == 1 && F1_SENSOR == 1 && (M_DOORCLOSE != 1 && M_DOOROPEN != 1))
        {
            M_UP = 1;
            F2_BLED = 1;
            doorflag2 = 1;
        }
        if ((F2_SENSOR == 1 && F2_BUTTON == 1) && (M_DOWN != 1 && M_UP != 1) && D_CSENSOR != 1)
        {
            F2_BLED = 1;
            M_DOOROPEN = 1;
            __delay_ms(1000);
            F2_BLED = 0;
            M_DOOROPEN = 0;
            __delay_ms(3000);
            M_DOORCLOSE = 1;
            __delay_ms(1000);
            M_DOORCLOSE = 0;
        }
        if (doorflag == 1 && F1_SENSOR == 1)
        {
            M_DOWN = 0;
            F1_BLED = 0;
            __delay_ms(1000);
            M_DOOROPEN = 1;
            __delay_ms(1000);
            M_DOOROPEN = 0;
            __delay_ms(3000);
            M_DOORCLOSE = 1;
            __delay_ms(1000);
            M_DOORCLOSE = 0;
            doorflag = 0;
        }
        if (doorflag2 == 1 && F2_SENSOR == 1)
        {
            M_UP = 0;
            F2_BLED = 0;
            __delay_ms(1000);
            M_DOOROPEN = 1;
            __delay_ms(1000);
            M_DOOROPEN = 0;
            __delay_ms(3000);
            M_DOORCLOSE = 1;
            __delay_ms(1000);
            M_DOORCLOSE = 0;
            doorflag2 = 0;
        }
        if (D_CSENSOR == 1 && M_UP != 1 && M_DOWN != 1)
        {
            M_DOOROPEN = 1;
            __delay_ms(1000);
            M_DOOROPEN = 0;
            __delay_ms(3000);
            M_DOORCLOSE = 1;
            __delay_ms(1000);
            M_DOORCLOSE = 0;
        }
    }
}
