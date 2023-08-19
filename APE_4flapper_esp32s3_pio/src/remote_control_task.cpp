#include <remote_control_task.h>

void remote_control_task(void *p_remote_control_task)
{
    while (1)
    {
        Serial.printf("remote_control \r\n");
        vTaskDelay(1000);
    }
}