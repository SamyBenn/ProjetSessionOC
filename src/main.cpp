#include <Arduino.h>
float tempAct=0;
// variables et constantes pour dht22
const unsigned int DHTPIN = 15; // GPIO utilisee par le DTH
#define DHTTYPE DHT22           // Modele du DHT
#include "MyDHT.h"
MyDHT *dht;

// variables et constantes pour led
#define LedRed 27   // GPIO utilisee par la led rouge
#define LedYellow 14   // GPIO utilisee par la led jaune
#define LedGreen 12   // GPIO utilisee par la led verte
bool ledOn = false; // pour garder en memoire l'etat de la led
void setup() {
  Serial.begin(9600);
  // initialisation de la pin de la led et s'assurer qu'elle est fermee au demarrage
  pinMode(LedRed, OUTPUT);
  pinMode(LedYellow, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  digitalWrite(LedRed, LOW);
  digitalWrite(LedYellow, LOW);
  digitalWrite(LedGreen, LOW);


  // initialisation de l'objet senseur de temperature
  dht = new MyDHT(DHTPIN, DHTTYPE);
}

void loop() {
  tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp
  dht->printTemp();      // afficher la temperature dans la console

  if(tempAct < 20){
    digitalWrite(LedRed, LOW);
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedGreen, HIGH);
  }else{if(tempAct < 30){
    digitalWrite(LedRed, LOW);
    digitalWrite(LedYellow, HIGH);
    digitalWrite(LedGreen, LOW);
  }else{
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedGreen, LOW);
  }}
  delay(2000);
}