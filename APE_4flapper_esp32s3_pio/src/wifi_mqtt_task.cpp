#include <wifi_mqtt_task.h>

char buffer[18];
char character = ','; //终止字符
int numdata = 0;

const char* ssid = "0ingchun";
const char* password = "35086020";
const char* mqtt_server = "192.168.2.200";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(500) //50
char msg[MSG_BUFFER_SIZE];
int value = 0;

String clientId = "ESP32Client-APE-Node" + String(random(0xffff), HEX), clientUser = "userape", clientPasswd = "88888888";


void wifi_mqtt_task(void *p_wifi_mqtt_task)
{
    while (1)
    {
        Serial.printf("mqtt \r\n");
        vTaskDelay(1000);
    }
}


// void WiFi_Connect()
// {
//     Serial.print("Connecting.. ");
// 	WiFi.begin(ssid, password);
// 	while (WiFi.status() != WL_CONNECTED)
// 	{ //这里是阻塞程序，直到连接成功
// 		delay(300);
// 		Serial.print(".");
// 	}
//     //WiFi.setAutoReconnect(true); //设置当断开连接的时候自动重连
//     //WiFi.persistent(true); //该方法设置将WiFi参数保存于Flash
//     Serial.println("WiFi connected");
// 	Serial.println("IP address: ");
// 	Serial.println(WiFi.localIP());
// }

// void reconnect_mqtt() {
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Create a random client ID
//     // String clientId = "ESP8266Client-lcdStation", clientUser = "user8266", clientPasswd = "88888888";
//     // String(random(0xffff), HEX)

//     // Attempt to connect
//     if (client.connect(clientId.c_str(), clientUser.c_str(), clientPasswd.c_str())) {

//         //ESP.wdtFeed();

//       Serial.println("connected");
//       // Once connected, publish an announcement...
//       client.publish("outTopic", "hello world");
//       // ... and resubscribe
//       client.subscribe("inTopic");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       // Wait 5 seconds before retrying
//       delay(100);
//     }
//   }
// }