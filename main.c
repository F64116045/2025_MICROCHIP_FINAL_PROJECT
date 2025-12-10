#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// using namespace std;

char str[20];
int last_number = 0;
int current_number = 0;
float user_input_value = 1;
int timer_multiplex = 10;
int current_timer_multiplex = 10;
int i = 0;
int j = 0;
void main(void) 
{
    SYSTEM_Initialize() ;
    current_timer_multiplex = 10;
    TRISD = 0;

    last_number = 0;
    current_number = 0;
    LATD = (current_number % 16) << 4;
    sprintf(str, "%u", current_number);
    for(int i = 0;i<strlen(str);i++){
        UART_Write(str[i]);
    }

    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
    IPR1bits.TMR2IP = 0;
    PR2 = 98;
    T2CON = 0b01111111;
    
    while(1) {
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.RCIF)
    {
        if(RCSTAbits.OERR)
        {
            CREN = 0;
            Nop();
            CREN = 1;
            return;
        }
        
        
        if(RCREG != '\r' && RCREG != '\n'){
            UART_Write(RCREG);
            str[j] = RCREG;
            j++;
        }
        else{
            UART_Write('\r');
            UART_Write('\n');
            str[j] = '\0';
            j = 0;
            sscanf(str, "%f", &user_input_value); 
            timer_multiplex =(int)(user_input_value * 10); 
            current_timer_multiplex = timer_multiplex;

        }
        PIR1bits.RCIF = 0;
        return;
    }
    
}

// void interrupt low_priority Lo_ISR(void)
void __interrupt(low_priority)  Lo_ISR(void)
{
    if(current_timer_multiplex == 1)
    {
        i++;
        LATD = ( i % 16 ) << 4 ;
        current_timer_multiplex = timer_multiplex;
    }
    else {
        current_timer_multiplex --;
    }

    PIR1bits.TMR2IF = 0;
    return;
}
