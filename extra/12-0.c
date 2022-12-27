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
#include "Seven_Segment.h"

int x_count = 0;
int heart = 4;
int point = 0;
int dog = -1;

void OpenSevenSegment(void)
{
    GPIO_SetMode(PC, BIT4, GPIO_PMD_OUTPUT);
    GPIO_SetMode(PC, BIT5, GPIO_PMD_OUTPUT);
    GPIO_SetMode(PC, BIT6, GPIO_PMD_OUTPUT);
    GPIO_SetMode(PC, BIT7, GPIO_PMD_OUTPUT);
    PC4 = 0;
    PC5 = 0;
    PC6 = 0;
    PC7 = 0;
    GPIO_SetMode(PE, BIT0, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT1, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT2, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT3, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT4, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT5, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT6, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT7, GPIO_PMD_QUASI);
    PE0 = 0;
    PE1 = 0;
    PE2 = 0;
    PE3 = 0;
    PE4 = 0;
    PE5 = 0;
    PE6 = 0;
    PE7 = 0;
}

int i = 0;
void Show(int x)
{
    for (i = 0; i < 2; i++)
    {
        switch (i)
        {
        case 0:
            PC4 = 1;
            PC5 = 0;
            break;
        case 1:
            PC4 = 0;
            PC5 = 1;
            break;
        }
        switch (x % 10)
        {
        case 0:
            PE0 = 0;
            PE4 = 0;
            PE3 = 0;
            PE2 = 0;
            PE6 = 0;
            PE5 = 0;

            PE1 = 1;
            PE7 = 1;
            break;
        case 1:
            PE0 = 0;
            PE4 = 0;

            PE1 = 1;
            PE2 = 1;
            PE3 = 1;
            PE5 = 1;
            PE6 = 1;
            PE7 = 1;
            break;
        case 2:
            PE3 = 0;
            PE4 = 0;
            PE7 = 0;
            PE6 = 0;
            PE5 = 0;

            PE0 = 1;
            PE1 = 1;
            PE2 = 1;
            PE8 = 1;
            break;
        case 3:
            PE3 = 0;
            PE4 = 0;
            PE7 = 0;
            PE0 = 0;
            PE5 = 0;

            PE1 = 1;
            PE2 = 1;
            PE6 = 1;
            PE8 = 1;
            break;
        case 4:
            PE2 = 0;
            PE7 = 0;
            PE4 = 0;
            PE0 = 0;

            PE1 = 1;
            PE3 = 1;
            PE5 = 1;
            PE6 = 1;
            break;
        case 5:
            PE3 = 0;
            PE2 = 0;
            PE7 = 0;
            PE0 = 0;
            PE5 = 0;

            PE1 = 1;
            PE4 = 1;
            PE6 = 1;
            break;
        case 6:
            PE3 = 0;
            PE2 = 0;
            PE6 = 0;
            PE5 = 0;
            PE0 = 0;
            PE7 = 0;

            PE1 = 1;
            PE4 = 1;
            break;
        case 7:
            PE2 = 0;
            PE3 = 0;
            PE4 = 0;
            PE0 = 0;

            PE1 = 1;
            PE5 = 1;
            PE6 = 1;
            PE7 = 1;
            break;
        case 8:
            PE0 = 0;
            PE2 = 0;
            PE3 = 0;
            PE4 = 0;
            PE5 = 0;
            PE6 = 0;
            PE7 = 0;

            PE1 = 1;
            break;
        case 9:
            PE0 = 0;
            PE2 = 0;
            PE3 = 0;
            PE4 = 0;
            PE5 = 0;
            PE7 = 0;

            PE1 = 1;
            PE6 = 1;
            break;
        }
        CLK_SysTickDelay(300);
        x /= 10;
    }
}

//draw_Bmp16x16(x,y,FG_COLOR,BG_COLOR,bmp16x16);
//CLK_SysTickDelay(100000);
//draw_Bmp16x16(x,y, BG_COLOR, BG_COLOR, bmp16x16);

unsigned char bmp16x16_1[32] = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
    0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF};

unsigned char bmp16x16[32] =
    {
        0x00, 0x00, 0x40, 0xE0, 0xE0, 0xE0, 0xE0, 0x70, 0x7C, 0xFE, 0xF8, 0x80, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x7F, 0x3E, 0x1E, 0x07, 0x07, 0x07, 0x03, 0x03, 0x02, 0x00};

char Text[16];

void show(int i)
{
    switch (i)
    {
    case 0:
        PC12 = 1;
        break;
    case 1:
        PC13 = 1;
        break;
    case 2:
        PC14 = 1;
        break;
    case 3:
        PC15 = 1;
        break;
    case 4:
        PC12 = 0;
        PC13 = 0;
        PC14 = 0;
        PC15 = 0;
        break;
    }
}

void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK);
    ADC_POWER_ON(ADC);
}

int forseven = 0;
int jump()
{
    int y = 48;

    while (1)
    {
        if (y <= 4)
        {
            break;
        }
        y = y - 1;
        x_count++;
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        draw_Bmp16x16(12, y, FG_COLOR, BG_COLOR, bmp16x16);
        draw_Bmp16x16(128 - (x_count % 128), 48, FG_COLOR, BG_COLOR, bmp16x16_1);
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        dog -= 1;
        if (128 - (x_count % 128) == 1 && dog < 0)
            point++;
        if (y > 35 && 128 - (x_count % 128) < 28 && 128 - (x_count % 128) > 15 && dog < 0)
        {
            dog = 16;
            heart--;
            show(heart);
        }
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        clear_LCD();
    }

    while (1)
    {
        if (y >= 48)
        {
            break;
        }
        y = y + 1;
        x_count++;
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        draw_Bmp16x16(12, y, FG_COLOR, BG_COLOR, bmp16x16);
        draw_Bmp16x16(128 - (x_count % 128), 48, FG_COLOR, BG_COLOR, bmp16x16_1);
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        dog -= 1;
        if (128 - (x_count % 128) == 1 && dog < 0)
            point++;
        if (y > 28 && 128 - (x_count % 128) < 32 && 128 - (x_count % 128) > 10 && dog < 0)
        {
            dog = 16;
            heart--;
            show(heart);
        }
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        clear_LCD();
    }
}

//x 0 - 127
//y 0 - 48
//y 32 x 17

int32_t main(void)
{
    uint32_t x, y, z;
    SYS_Init();
    Init_ADC();
    init_LCD();
    clear_LCD();
    OpenSevenSegment();

    PD14 = 0;

    //print_Line(0, "VR");
    draw_Bmp16x16(90, 48, FG_COLOR, BG_COLOR, bmp16x16_1);
    show(heart);

    while (1)
    {
        x_count++;
        ADC_START_CONV(ADC);

        x = ADC_GET_CONVERSION_DATA(ADC, 0);
        y = ADC_GET_CONVERSION_DATA(ADC, 1);
        z = PB0;

        for (forseven = 0; forseven < 5; forseven++)
            Show(point);
        draw_Bmp16x16(12, 48, FG_COLOR, BG_COLOR, bmp16x16);

        if (z == 0)
        {
            jump();
        }
        draw_Bmp16x16(128 - (x_count % 128), 48, FG_COLOR, BG_COLOR, bmp16x16_1);
        for (forseven = 0; forseven < 5; forseven++)
            Show(point);

        dog -= 1;
        if (y > 35 && 128 - (x_count % 128) < 28 && 128 - (x_count % 128) > 15 && dog < 0)
        {
            dog = 16;
            heart--;
            show(heart);
        }
        if ((128 - (x_count % 128) == 1) && (dog > 0))
            point++;

        for (forseven = 0; forseven < 5; forseven++)
            Show(point);

        if (heart <= 0)
        {
            show(0);
            break;
        }
        clear_LCD();
    }
}