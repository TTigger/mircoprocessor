//
// TMR_Capture_SR04 : usi[ng Timer Capture to read Ultrasound Ranger SR-04
//
// EVB : Nu-LB-NUC140 (need to manually switch RSTCAPSEL)
// MCU : NUC140VE3CN
// Sensor: SR-04

// SR-04 connection
// Trig connected to PB8
// Echo connected to TC2/PB2 (TC0_PB15, TC1_PE5, TC2_PB2, TC3_PB3)

#include "stdio.h"
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"

unsigned char bmp16x16[32] =
    {
        0x00, 0x00, 0x40, 0xE0, 0xE0, 0xE0, 0xE0, 0x70, 0x7C, 0xFE, 0xF8, 0x80, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x7F, 0x3E, 0x1E, 0x07, 0x07, 0x07, 0x03, 0x03, 0x02, 0x00};

char Text[16];

void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK);
    ADC_POWER_ON(ADC);
}

int32_t main(void)
{
    uint32_t x, y, z;
    SYS_Init();
    Init_ADC();
    init_LCD();
    clear_LCD();

    PD14 = 0;

    /*
while(1){
x = 64;
y = 32;
draw_Bmp16x16(x,y,FG_COLOR,BG_COLOR,bmp16x16);
CLK_SysTickDelay(500000);
draw_Bmp16x16(x, y, BG_COLOR, BG_COLOR, bmp16x16);
clear_LCD();
}
*/

    //clear_LCD();

    //print_Line(0, "VR");

    // x 3300 3315
    // y 3370 3380

    while (1)
    {
        ADC_START_CONV(ADC);
        x = ADC_GET_CONVERSION_DATA(ADC, 0);
        //sprintf(Text,"T = %5d", x);
        //print_Line(1, Text);

        y = ADC_GET_CONVERSION_DATA(ADC, 1);
        //sprintf(Text,"T = %5d", y);
        //print_Line(2, Text);

        z = PB0;
        //sprintf(Text,"T = %5d", z);
        //print_Line(3, Text);

        //55 25

        /*
if(x>=3300 && x<=3330 && y>=3360 && y<= 3400){ //y<=3380
x = x / 60;
y = y / 135;
}else{
x = (x) / 37; //64
y = (y) / 90; //128
}
*/
        x = x / 60;  //55
        y = y / 135; //25

        if (x > 55)
        {
            x = x * 1.6;
        }
        if (y > 25)
        {
            y = y * 1.6;
        }

        draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, bmp16x16);
        CLK_SysTickDelay(500000);
        draw_Bmp16x16(x, y, BG_COLOR, BG_COLOR, bmp16x16);
        clear_LCD();
    }
}