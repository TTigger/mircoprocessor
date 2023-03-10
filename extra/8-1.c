//
// UART0_RX : UART0 RX recieve and display Text
//
// Board : Nu-LB-NUC140
// MCU : NUC140VE3CN (LQFP100)
// UART0 : baudrate=115200, databit=8, stopbit=1, paritybit=0, flowcontrol=None

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"

void Init_UART(void)
{
    UART_Open(UART0, 9600); // set UART0 baud rate
}

int32_t main()
{
    char TX_Buffer[16];
    char RX_Buffer[16];
    uint32_t keyin = 0;

    SYS_Init();
    init_LCD();
    clear_LCD();
    Init_UART();

    PD14 = 0;
    print_Line(0, "test TX and RX:");

    sprintf(TX_Buffer, "");

    while (1) //send
    {
        keyin = ScanKey();
        if (keyin != 0)
        {
            sprintf(TX_Buffer, "%d", keyin);
            print_Line(1, TX_Buffer);
            UART_Write(UART0, TX_Buffer, 1);
            CLK_SysTickDelay(1000000);
        }
    }

    /*
while(1) //receive
{
UART_Read(UART0, RX_Buffer, 1);
print_Line(2, RX_Buffer);
CLK_SysTickDelay(1000000);

if(RX_Buffer[0] == '1'){
PC12=1;PC13=1;PC14=1;PC15=0;
}else if(RX_Buffer[0] == '2'){
PC12=1;PC13=1;PC14=0;PC15=1;
}else if(RX_Buffer[0] == '3'){
PC12=1;PC13=1;PC15=0;PC14=0;
}else if(RX_Buffer[0] == '4'){
PC12=1;PC14=1;PC15=1;PC13=0;
}else if(RX_Buffer[0] == '5'){
PC12=1;PC14=1;PC13=0;PC15=0;
}else if(RX_Buffer[0] == '6'){
PC13=0;PC14=0;PC12=1;PC15=1;
}else if(RX_Buffer[0] == '7'){
PC13=0;PC14=0;PC15=0;PC12=1;
}else if(RX_Buffer[0] == '8'){
PC12=0;PC13=1;PC14=1;PC15=1;
}else if(RX_Buffer[0] == '9'){
PC12=0;PC15=0;PC13=1;PC14=1;
}
}
*/
}