#include "heltec.h"

#define BAND    915E6  

String packSize = "--";
String packet ;

/* Protótipo da função */
void LoRaDataPrint();
void cbk(int packetSize);


void LoRaDataPrint(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 1 , "Recebendo "+ packSize + " bytes");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(15, 16, "Temperatura");
  Heltec.display->drawString(33, 38, packet);
  Heltec.display->drawString(78, 38, "°C");
  Heltec.display->display();
}


void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) {
    packet += (char) LoRa.read(); //Atribui um caractere por vez a váriavel packet 
  }
  LoRaDataPrint();
}

void setup()
{
  pinMode(LED,OUTPUT); //inicializa o LED
  
  Serial.begin(9600);
  Heltec.begin(true /*Habilita o Display*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Habilita debug Serial*/, true /*Habilita o PABOOST*/, BAND /*Frequência BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawString(10, 5, "Iniciado com Sucesso!");
  Heltec.display->drawString(10, 30, "Aguardando os dados...");
  Heltec.display->display();
  Serial.println("Iniciado com Sucesso!");
  Serial.println("Aguardando os dados...");
  delay(1000);
  
  LoRa.receive(); // Habilita o rádio LoRa para receber dados
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) { //Verifica se há dados chegando via LoRa
    cbk(packetSize);
    digitalWrite(LED, HIGH);   // Liga o LED
    delay(500);                // Espera 500 milissegundos
    digitalWrite(LED, LOW);    // Desliiga o LED
    delay(500);                // Espera 500 milissegundos
    Serial.print("Recebendo a temperatura: ");
    Serial.print(packet); //Imprime no monitor serial a temperatura
    Serial.println("°C");
  }
  delay(10);
}
