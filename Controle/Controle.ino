
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
    Serial.print("");
    
    
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
        
        Serial.print("servidores encontrados: "); Serial.println(SSID); Serial.print(" Valor do Sinal RSSI: "); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
                  
        if(RSSI <= -1 && RSSI >= -60){
         Serial.println("Você chegou.");
        
        for(int i = 0; i < 2; i++ ){
          ledcWriteTone(channel, 250);      
             delay(2000);
          ledcWriteTone(channel, 0);
             delay(15);
         }               
      }
        if(RSSI <= -61 && RSSI >= -67){
         Serial.println(" Você está a 1 metro.");

        for(int i = 0; i < 1; i++ ){
         ledcWriteTone(channel, 250);      
            delay(250);
         ledcWriteTone(channel, 0);      
            delay(250); 
        }      
      }
      else if(RSSI <= -68 && RSSI >= -73){
        Serial.println(" Você está a 2 metros ");
        
      for(int i = 0; i < 2; i++ ){ 
          ledcWriteTone(channel, 250);
            delay(250);
         ledcWriteTone(channel, 0);
         
            delay(250); 
          }           
      }
        else if(RSSI <= -74 && RSSI >= -77){
        Serial.println(" Você está a 3 metros ");
        
        for(int i = 0; i < 3; i++ ){
          ledcWriteTone(channel, 250); 
            delay(250);
          ledcWriteTone(channel, 0);
            delay(250);
           }
      }
        else if(RSSI <= -78 && RSSI >= -83){
        Serial.println(" Você está a 4 metros ");

        for(int i = 0; i < 4; i++ ){
          ledcWriteTone(channel, 250);
           delay(250);
          ledcWriteTone(channel, 0);   
            delay(250);
        }
      }
        else if(RSSI <= -82 && RSSI >= -86){
        Serial.println(" Você está a 5 metros ");

        for(int i = 0; i < 5; i++ ){
           ledcWriteTone(channel, 250);
            delay(250);
            ledcWriteTone(channel, 0);     
            delay(250);
        }
      }
        else if(RSSI == -87){
        Serial.println(" Você está a 6 metros ");

        for(int i = 0; i < 6; i++ ){
          ledcWriteTone(channel, 250);
            delay(250);
          ledcWriteTone(channel, 0);
            delay(250);
        }
      }
        else if(RSSI <= -87 && RSSI >= -92){
        Serial.println("Você está a 7 metros ");
        
        for(int i = 0; i < 7; i++ ){
          
            delay(250);
          ledcWriteTone(channel, 0);
          
            delay(250);
        }
      }
        else if(RSSI <= -83 && RSSI >= -94){
        Serial.println(" Você está a 8 metros ");
        
        for(int i = 0; i < 8; i++ ){
          ledcWriteTone(channel, 250);
              delay(250);
          ledcWriteTone(channel, 0);
              delay(250);
        }
      }
        else if(RSSI == -95){
        Serial.println(" Você está a 9 metros ");
        
        for(int i = 0; i < 9; i++ ){
          ledcWriteTone(channel, 250);
          
            delay(250);
         ledcWriteTone(channel, 0);
        
            delay(250);
        }
      }
        else if(RSSI == -96){
        Serial.println(" Você está a 10 metros");

        for(int i = 0; i < 10; i++ ){
          ledcWriteTone(channel, 250);
         
            delay(250);
         ledcWriteTone(channel, 0);
       
            delay(250);
        }
      }
      else if(RSSI < -96){
       Serial.println("Você está Fora do alcance de 10 metros");
       
      for(int i = 0; i < 3; i++ ){
          ledcWriteTone(channel, 250);
         
            delay(125);
          ledcWriteTone(channel, 500);
        
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
          delay(100); 
          // limpa a RAM
  WiFi.scanDelete();
  }
  
}

uint8_t data = 0;
void sendData() {
  data++;
  const uint8_t *peer_addr = servidor.peer_addr;
  
  esp_err_t result = esp_now_send(peer_addr, &data, sizeof(data));
  
  if (result == ESP_OK) {
    Serial.println("Success");
  } else  {
    Serial.println("");   
  }
}

//recebe a chamada do servidor
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",R
 // mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  
}

void setup() { 
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  
  
  esp_now_register_send_cb(OnDataSent);
}

void loop() {
  ProcuraPeloServidor();

  if (servidor.channel == CHANNEL) {     
   
   sendData();   
   delay(15); 
}
}
