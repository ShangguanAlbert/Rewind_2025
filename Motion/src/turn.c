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

void Tai1_6_zhuan(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Deg_IN();
    for (int x = 50; x < 105; x++) {
        run(x * 0.95, -x * 0.98);
        delay_ms(8); //
    }
    for (int x = 50; x > 105; x--) {
        run(x * 0.95, -x * 0.98);
        delay_ms(8);
    }
    pid_Turn(960);
    stop();
    Front_down();
}