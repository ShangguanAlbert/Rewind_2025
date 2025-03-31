#include "reset.h"

/**
 * @brief 指定车辆通过延时确定时间达到目标速度,绿地巡线
 * @param time_last 延时时间 1000为1秒.
 * @param goal_speed 目标速度,不超过200.
 */
void Reset(int time_last, int goal_speed)
{
    t7_i = 0;
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    do {
        if (goal_speed > 90) {
            high_run(goal_speed);
        } else {
            slow_run(goal_speed);
        }
    } while (t7_i < time_last);
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
    t7_i = 0;
}
