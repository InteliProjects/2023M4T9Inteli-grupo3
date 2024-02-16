#include "ConfigMQTT.h"
#include "InterfaceLCD.h"   
#include <string>
ConfigMQTT::ConfigMQTT(WiFiServer server, const char* ssid, const char* password, const char* token, const char* deviceLabel,  uint8_t LCD_ADDRESS) 
  : ubidots(token), 
    lcd(LCD_ADDRESS) {
    this->ssid          = ssid;
    this->password      = password;
    this->token         = token;
    this->deviceLabel   = deviceLabel;
    this->server        = server;
}

void ConfigMQTT::conectar() {
  lcd.iniciar();
  lcd.escrever("Conectando-se a ",ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.escrever("WiFi nao conectada", "tentando novamente.");
  }
  lcd.escrever("","");
  lcd.escrever("WiFi conectada.","");
  String localIP = WiFi.localIP().toString();
  lcd.escrever("Endereco de IP: ", localIP);
  server.begin();
  ubidots.connectToWifi(ssid, password);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();
}

void ConfigMQTT::executar() {
    if (!ubidots.connected()) {
        ubidots.reconnect();
    }
    ubidots.loop();
}

void ConfigMQTT:: publicar(const char* varMassa, const char* varTemp, std::pair<float, float> dados) {
    if (labs(static_cast<long>(millis()) - timer) > PUBLISH_FREQUENCY) {
        ubidots.add(varMassa, dados.first);
        ubidots.add(varTemp, dados.second);
        ubidots.publish(deviceLabel);
        timer = millis();
    }
}
void ConfigMQTT::callback(char *topic, byte *payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}