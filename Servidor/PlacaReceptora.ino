#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("Servidor iniciado com SUCESSO");
  }
  else {
    Serial.println("FALHA ao iniciar, tentando novamente...");
    ESP.restart();
  }
}

// config AP SSID
void configDeviceAP() {
  const char *SSID = "servidor_1";
  bool result = WiFi.softAP(SSID, "servidor_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("Verifique as configurações, falha ao tentar comunicar-se.");
  } else {
    Serial.println("Conenctado com: " + String(SSID));
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  
  configDeviceAP();
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
 
  InitESPNow();
  
  esp_now_register_recv_cb(OnDataRecv);
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Sinal recebido recebido de: "); Serial.println(macStr);
  Serial.print("Ultimo sinal recebido: "); Serial.println(*data);
  Serial.println("");
}

void loop() {  
}
