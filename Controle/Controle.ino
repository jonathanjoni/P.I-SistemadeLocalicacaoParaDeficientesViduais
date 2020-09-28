
#include <esp_now.h>
#include <WiFi.h>

esp_now_peer_info_t servidor;
#define CHANNEL 3
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

int channel = 0;

void ProcuraPeloServidor() {
  
  int8_t resultadoDaProcuraPeloServidor = WiFi.scanNetworks();
  bool achouServidor = 0;
  memset(&servidor, 0, sizeof(servidor));

  Serial.println("");
  if (resultadoDaProcuraPeloServidor == 0) {
    Serial.println("Servidor Fora do Ar Verifique");
  } else {
    Serial.print("Found "); Serial.println(" devices ");
    
    
    for (int i = 0; i < resultadoDaProcuraPeloServidor; ++i) {
      
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(SSID);
        Serial.print(" (");
        Serial.print(RSSI);
        Serial.print(")");
        Serial.println("");
      }
      
      ledcAttachPin(15, channel);
      ledcAttachPin(14, channel);
      
      delay(15);
      
      if (SSID.indexOf("servidor") == 0) {
        
        Serial.println("servidor Encontrado.");
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
                  
        if(RSSI <= -1 && RSSI >= -60){
         Serial.print("Você chegou.");
        
        for(int i = 0; i < 2; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
             delay(2000);
          ledcWriteTone(channel, 0);
          ledcWriteTone(channel, LOW);
             delay(15);
         }               
      }
        if(RSSI <= -61 && RSSI >= -64){
         Serial.print(" Você está a 1 metro.");

        for(int i = 0; i < 1; i++ ){
         ledcWriteTone(channel, 250);
         ledcWriteTone(channel, HIGH);
            delay(250);
         ledcWriteTone(channel, 0);
         ledcWriteTone(channel, LOW);
            delay(250); 
        }      
      }
      else if(RSSI <= -65 && RSSI >= -69){
        Serial.print(" Você está a 2 metros ");
        
      for(int i = 0; i < 2; i++ ){ 
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(250);
         ledcWriteTone(channel, 0);
         ledcWriteTone(channel, LOW);
            delay(250); 
          }           
      }
        else if(RSSI <= -70 && RSSI >= -77){
        Serial.print(" Você está a 3 metros ");
        
        for(int i = 0; i < 3; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(250);
          ledcWriteTone(channel, 0);
          ledcWriteTone(channel, LOW);
            delay(250);
           }
      }
        else if(RSSI <= -78 && RSSI >= -84){
        Serial.print(" Você está a 4 metros ");

        for(int i = 0; i < 4; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(250);
          ledcWriteTone(channel, 0);
          ledcWriteTone(channel, LOW);
            delay(250);
        }
      }
        else if(RSSI <= -85 && RSSI >= -86){
        Serial.print(" Você está a 5 metros ");

        for(int i = 0; i < 5; i++ ){
           ledcWriteTone(channel, 250);
           ledcWriteTone(channel, HIGH);
            delay(250);
            ledcWriteTone(channel, 0);
            ledcWriteTone(channel, LOW);
            delay(250);
        }
      }
        else if(RSSI == -87){
        Serial.print(" Você está a 6 metros ");

        for(int i = 0; i < 6; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(250);
          ledcWriteTone(channel, 0);
          ledcWriteTone(channel, LOW);
            delay(250);
        }
      }
        else if(RSSI <= -87 && RSSI >= -92){
        Serial.print("Você está a 7 metros ");
        
        for(int i = 0; i < 7; i++ ){
          ledcWriteTone(channel, HIGH);
            delay(250);
          ledcWriteTone(channel, 0);
          ledcWriteTone(channel, LOW);
            delay(250);
        }
      }
        else if(RSSI <= -83 && RSSI >= -94){
        Serial.print(" Você está a 8 metros ");
        
        for(int i = 0; i < 8; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
              delay(250);
          ledcWriteTone(channel, 0);
          ledcWriteTone(channel, LOW);
              delay(250);
        }
      }
        else if(RSSI == -95){
        Serial.print(" Você está a 9 metros ");
        
        for(int i = 0; i < 9; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(250);
         ledcWriteTone(channel, 0);
         ledcWriteTone(channel, LOW);
            delay(250);
        }
      }
        else if(RSSI == -96){
        Serial.print(" Você está a 10 metros");

        for(int i = 0; i < 10; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(250);
         ledcWriteTone(channel, 0);
         ledcWriteTone(channel, LOW);
            delay(250);
        }
      }
      else if(RSSI < -96){
       Serial.print("Você está Fora do alcance de 10 metros");
       
      for(int i = 0; i < 3; i++ ){
          ledcWriteTone(channel, 250);
          ledcWriteTone(channel, HIGH);
            delay(125);
          ledcWriteTone(channel, 500);
          ledcWriteTone(channel, LOW);
            delay(125);
        }
      }
        servidor.channel = CHANNEL; // pick a channel
        servidor.encrypt = 0; // no encryption

        achouServidor = 1;     
      }
    }
  }
  if (achouServidor) {
    Serial.println("Servidor Encontrado, processando..");
  } else {
    Serial.println("Servidor NÃO Encontrado, Tentando conectar-se novamente...");
    ledcWriteTone(channel, 0);
          delay(1000); //Adicionar beep de 5s
  }
  // limpa a RAM
  WiFi.scanDelete();
}

uint8_t data = 0;
void sendData() {
  data++;
  const uint8_t *peer_addr = servidor.peer_addr;
  Serial.print("Sending: "); Serial.println(data);
  esp_err_t result = esp_now_send(peer_addr, &data, sizeof(data));
  Serial.print("Send Status: ");
  if (result == ESP_OK) {
    Serial.println("Success");
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    Serial.println("ESPNOW not Init.");   
  }
}

//recebe a chamada do servidor
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
  mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: "); Serial.println(macStr);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() { 
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  
  Serial.println("ESPNow/Basic/Master Example");
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());
  
  esp_now_register_send_cb(OnDataSent);
}

void loop() {
  ProcuraPeloServidor();

  if (servidor.channel == CHANNEL) {     
   
   sendData();   
   delay(15); 
}
}
