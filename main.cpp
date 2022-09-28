#include <Arduino.h>
#include <pines.h>
#include <SPI.h>
#include <LoRa.h>

const long frecuencia = 868E6;    // 868 MHz
long intervalo = 1000;
long tiempo = 0;
volatile bool despierta = false;

void despertar();

void setup() {

  // Configuramos el monitor serial a 115200 baudios
  Serial2.begin(115200);
  while (!Serial2);

  // Configuramos el módulo LoRa a 868MHz
  Serial2.println("Inicio configuración LoRa Receiver ");
  LoRa.setPins(RFM95_SS, RFM95_RST, RFM95_DIO1);
  if (!LoRa.begin(frecuencia)) {
    Serial2.println("Inicialización de LoRa ha fallado.");
    while (1);
  }

  // Configuramos los pines del temporizador.
  pinMode(TPL5010_WAKE, INPUT);       // Pin "WAKE" como entrada
  pinMode(TPL5010_DONE, OUTPUT);      // Pin "DONE" como salida
  digitalWrite(TPL5010_DONE, LOW);    // Ponemos pin "DONE" a cero
  pinMode(LED_BUILTIN, OUTPUT);       // Pin "LED" como salida

  // Configuramos la interrupción de control del temporizador  
  attachInterrupt(RFM95_DIO0, despertar, FALLING);

  // Enviamos señal DONE (Hecho) para evitar el reseteo.
  digitalWrite(TPL5010_DONE, HIGH);
  delay(1);
  digitalWrite(TPL5010_DONE, LOW);  
}

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
  
    // received a packet
    Serial2.print("Paquete recibido: '");

    // read packet
    while (LoRa.available()) {
      Serial2.print((char)LoRa.read());
    }

    // print RSSI of packet (indica el nivel de engergía con que llega el paquete)
    Serial2.print("' with RSSI ");
    Serial2.println(LoRa.packetRssi());

    // Cambia el estado del LED (lo hace parpadear)
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  // Incrementa el contador y muestra el paso actual
  if(millis() - tiempo >= intervalo){                 // millis() devuelve los milisegundos desde que se arrancó el programa
    tiempo += intervalo;
    Serial2.print("Paso "); 
    Serial2.println(tiempo / intervalo);
  }

  // Manda un pulso al pin "DONE" tras activarse la interrupción (evita el reseteo)
  if(despierta){
    digitalWrite(TPL5010_DONE, HIGH);    
    despierta = false;                                // Desactiva la variable "despierta"
    Serial2.println("Evitando el reseteo...");
    digitalWrite(TPL5010_DONE, LOW);
  }
}

// Desactiva la variable "despierta"
void despertar(){
  despierta = true;
}