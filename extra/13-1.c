/
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
#include #include #include "LCD.h"
#include "Seven_Segment.h"

    uint8_t ledState = 0;
uint32_t keyin = 0;
uint32_t i = 5;
uint32_t j = 0;
char Text[16];
int delayTime;

void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK);
    ADC_POWER_ON(ADC);
}

void TMR1_IRQHandler(void)
{
    PD14 = PB0 == 0 ? ~PD14 : PD14;
    TIMER_ClearIntFlag(TIMER1); // Clear Timer1 time-out interrupt flag
}

void Init_Timer1(void)
{
    TIMER_Open(TIMER1, TMR1_OPERATING_MODE, 5);
    TIMER_EnableInt(TIMER1);
    NVIC_EnableIRQ(TMR1_IRQn);
    TIMER_Start(TIMER1);
}

int main(void)
{
    SYS_Init();
    Init_ADC();
    init_LCD();
    clear_LCD();
    OpenSevenSegment();

    PD14 = 0;
    print_Line(0, "timer");
    Init_Timer1();

    while (1)
    {
        ADC_START_CONV(ADC);
        delayTime = (ADC_GET_CONVERSION_DATA(ADC, 0) + 1) * 30;
        CloseSevenSegment();
        i = delayTime / 30000;
        ShowSevenSegment(0, i);
        PC12 = PC13 = PC14 = PC15 = 1;
        PC12 = 0;
        CLK_SysTickDelay(delayTime);
        PC12 = 1;
        PC13 = 0;
        CLK_SysTickDelay(delayTime);
        PC13 = 1;
        PC14 = 0;
        CLK_SysTickDelay(delayTime);
        PC14 = 1;
        PC15 = 0;
        CLK_SysTickDelay(delayTime);
        PC15 = 1;
        PC14 = 0;
        CLK_SysTickDelay(delayTime);
        PC14 = 1;
        PC13 = 0;
        CLK_SysTickDelay(delayTime);
        PC13 = 1;
    }
}