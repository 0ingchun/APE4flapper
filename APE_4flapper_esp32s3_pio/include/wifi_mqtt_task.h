#pragma once

#include <Arduino.h>
#include <WiFi.h>

#include "HTTPClient.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"


void wifi_mqtt_task(void *p_wifi_mqtt_task);

void WiFi_Connect();

void reconnect_mqtt();
