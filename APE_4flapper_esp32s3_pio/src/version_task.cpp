#include <version_task.h>

void version_task(void *p_version_task)
{
    while (1)
    {
        Serial.printf("version \r\n");
        vTaskDelay(1000);
    }
}