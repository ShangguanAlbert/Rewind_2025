#include "bsp_lcd.h"
#include "bsp_key.h"
#include "bsp_adc.h"
#include "bsp_compass.h"
#include "bsp_sensor.h"
#include "bsp_qr.h"

uint8_t page = 1;
extern uint8_t prog_num_hope;
extern uint8_t res[];
extern int8_t openmv[2];
extern float JD;

void Show_SensorPage_All(void)
{
    LCD_SetDirection(Direction_H_Flip);
    LCD_ShowNumMode(Fill_Space);
    while (1) {
        while (1) {
            Sensor_Test_Page1();
            if (KeyDown == 0 && page == 1) {
                page = 2;
                delay_ms(300);
                LCD_Clear();
                break;
            }
        }
        while (1) {
            Sensor_Test_Page2();
            if (KeyUp == 0 && page == 2) {
                page = 1;
                delay_ms(300);
                LCD_Clear();
                break;
            }
        }
    }
}

void Sensor_Test_Page1(void)
{
    page = 1;
    LCD_SetAsciiFont(&ASCII_Font24);
    LCD_DisplayString(50, 0, "Front Huidu");
    LCD_DrawLine(0, 25, 240, 25);
    LCD_SetAsciiFont(&ASCII_Font20);
    LCD_DisplayString(5, 35, "FH0:");
    LCD_DisplayNumber(70, 35, Huidu_va(0), 4);
    LCD_DisplayString(5, 60, "FH1:");
    LCD_DisplayNumber(70, 60, Huidu_va(1), 4);
    LCD_DisplayString(5, 85, "FH2:");
    LCD_DisplayNumber(70, 85, Huidu_va(2), 4);
    LCD_DisplayString(5, 110, "FH3:");
    LCD_DisplayNumber(70, 110, Huidu_va(3), 4);
    LCD_DisplayString(5, 135, "FH4:");
    LCD_DisplayNumber(70, 135, Huidu_va(4), 4);
    LCD_DisplayString(5, 160, "FH5:");
    LCD_DisplayNumber(70, 160, Huidu_va(5), 4);
    LCD_DisplayString(5, 185, "FH6:");
    LCD_DisplayNumber(70, 185, Huidu_va(6), 4);
    LCD_DisplayString(5, 210, "FH7:");
    LCD_DisplayNumber(70, 210, Huidu_va(7), 4);

    LCD_DrawLine_V(120, 25, 220);

    LCD_DisplayString(130, 35, "FH8:");
    LCD_DisplayNumber(190, 35, Huidu_va(8), 4);
    LCD_DisplayString(130, 60, "FH9:");
    LCD_DisplayNumber(190, 60, Huidu_va(9), 4);
    LCD_DisplayString(130, 85, "FH10:");
    LCD_DisplayNumber(190, 85, Huidu_va(10), 4);
    LCD_DisplayString(130, 110, "FH11:");
    LCD_DisplayNumber(190, 110, Huidu_va(11), 4);

    LCD_DrawLine(120, 135, 240, 135);

    LCD_DisplayString(135, 140, "-Compass-");
    LCD_DisplayNumber(155, 160, compass_b(), 4);

    LCD_DrawLine(120, 185, 240, 185);

    LCD_DisplayString(150, 190, "-color-");

    if (openmv[2] == 1) {
        LCD_DisplayString(160, 215, "red");
    } else if (openmv[2] == 2) {
        LCD_DisplayString(160, 215, "green");
    } else if (openmv[2] == 3) {
        LCD_DisplayString(160, 215, "blue");
    } else if (openmv[2] == 0) {
        LCD_DisplayString(160, 215, "None");
    }
}

void Sensor_Test_Page2(void)
{
    page = 2;
    LCD_SetAsciiFont(&ASCII_Font24);
    LCD_DisplayString(50, 0, "Digital Sensor");
    LCD_DrawLine(0, 25, 240, 25);
    LCD_SetAsciiFont(&ASCII_Font20);
    LCD_DisplayString(5, 35, "hwl:");
    LCD_DisplayNumber(100, 35, hwl, 1);
    LCD_DisplayString(5, 60, "hwr:");
    LCD_DisplayNumber(100, 60, hwr, 1);
    LCD_DisplayString(5, 85, "hdxl:");
    LCD_DisplayNumber(100, 85, hdxl, 1);
    LCD_DisplayString(5, 110, "hdxr:");
    LCD_DisplayNumber(100, 110, hdxr, 1);
    LCD_DisplayString(5, 160, "sebl");
    LCD_DisplayNumber(100, 160, sebl, 1);
    LCD_DisplayString(5, 185, "sebr");
    LCD_DisplayNumber(100, 185, sebr, 1);

    LCD_DisplayString(5, 135, "bpt:");
    // LCD_DisplayNumber(100, 135, code_info, 8);
    // LCD_DisplayString(5, 160, "bpt:");
    // LCD_DisplayNumber(100, 160, (int)(res[1]), 1);
    // LCD_DisplayString(5, 185, "bpt:");
    // LCD_DisplayNumber(100, 185, (int)(res[2]), 1);
    // LCD_DisplayString(5, 210, "bhwr:");
    // LCD_DisplayNumber(100, 210, bhwr, 1);

    // LCD_DrawLine_V(120, 25, 220);
}
uint8_t Function_Mode(void)
{
    LCD_SetDirection(Direction_H_Flip);
    uint8_t Enter_Key_Press = 0;
    uint8_t num             = prog_num_hope;
    LCD_SetColor(0xFFFFFF);
    LCD_DrawLine(0, 1, 240, 1);
    LCD_SetAsciiFont(&ASCII_Font20);
    LCD_DisplayString(5, 5, "HZNU REWIND 2025");
    LCD_DrawLine(0, 28, 240, 28);
    LCD_SetAsciiFont(&ASCII_Font20);
    LCD_DisplayString(5, 35, "1.Program-01");
    LCD_DisplayString(5, 60, "2.Program-02");
    LCD_DisplayString(5, 85, "3.Program-03");
    LCD_DisplayString(5, 110, "4.Program-04");
    LCD_DisplayString(5, 135, "5.Program-05");
    LCD_DisplayString(5, 160, "6.Program-06");
    LCD_DisplayString(5, 185, "7.Program-07");
    LCD_DisplayString(5, 210, "8.SensorTest");
    LCD_DrawRect(1, 1, 238, 238);
    LCD_DisplayString(135, 110, "PROG:");
    LCD_DrawLine_V(130, 28, 210);
    while (Enter_Key_Press == 0) {
        switch (KEY_Scan(0)) {
            case 1:
                num--;
                if (num == 0) { num = 8; }
                break;
            case 3:
                num++;
                if (num == 9) { num = 1; }
                break;
            case 2:
                Enter_Key_Press = 1;
                break;
        }
        LCD_SetAsciiFont(&ASCII_Font32);
        LCD_DisplayNumber(190, 104, num, 1);
    }
    LCD_SetAsciiFont(&ASCII_Font24);
    LCD_DisplayString(135, 150, "Ready!");
    delay_ms(800);
    LCD_Clear();
    LCD_SetAsciiFont(&ASCII_Font24);
    return num;
}
