#include "turn.h"
#include "trace.h"
#include "bsp_adc.h"
#include "posture.h"
#include "bsp_SysTick.h"
#include "bsp_compass.h"
#include "reset.h"
#include "pid_turn.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "basic.h"

void TurnRight_155_Longline(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(1) > white[1] || Huidu_va(0) > white[0]) {
            break;
        }
    }
    Left_Speed_Up(50, 115, 3);
    Right_Speed_Down(50, -90, 4);
    while (1) {
        run(85, -65);
        if (Huidu_va(4) > white[4] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}


void Tai1_6_zhuan(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Deg_IN();
    for (int x = 55; x < 110; x++) {
        run(x * 1.0, -x * 0.92);
        Delay_ms(8); //
    }
    pid_Turn(500);
    Stop(50);
    Front_down();
}