#ifndef CONFIGMQTT_H
#define CONFIGMQTT_H

#include "InterfaceLCD.h"
#include "WiFi.h"
#include "UbidotsEsp32Mqtt.h"

class ConfigMQTT {
public:
    ConfigMQTT(WiFiServer server, const char* ssid, const char* password, const char* token, const char* deviceLabel, uint8_t LCD_ADDRESS);
    void conectar();
    void executar();
    void publicar(const char* varMassa, const char* varTemp, std::pair<float, float> dados);

private:
    const int PUBLISH_FREQUENCY = 2500;
    const char* ssid;
    const char* password;
    const char* token;
    const char* deviceLabel;
    unsigned long timer;
    Ubidots ubidots;
    WiFiServer server;
    InterfaceLCD lcd;
    uint8_t LCD_ADDRESS;

    static void callback(char* topic, byte* payload, unsigned int length);
};

#endif