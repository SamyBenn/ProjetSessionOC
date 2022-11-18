#include <iostream>
#include <string>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "myFunctions.cpp"
using namespace std;
#include <HTTPClient.h>
#include <WiFiManager.h>
#define WEBSERVER_H
#include "MyDHT.h"
#include "MyServer.h"


float tempAct=0;
// variables et constantes pour dht22
const unsigned int DHTPIN = 15; // GPIO utilisee par le DTH
#define DHTTYPE DHT22           // Modele du DHT
MyDHT *dht;

// variables et constantes pour led
#define LedRed 27   // GPIO utilisee par la led rouge
#define LedYellow 14   // GPIO utilisee par la led jaune
#define LedGreen 12   // GPIO utilisee par la led verte
bool ledOn = false; // pour garder en memoire l'etat de la led

// constantes pour la connexion wifi
const char *SSID = "securewifi";
const char *PASSWORD = "securiti";

MyServer *myServer = NULL;
WiFiManager wm;

void setup() {
  Serial.begin(9600);
  // initialisation de la pin de la led et s'assurer qu'elle est fermee au demarrage
  pinMode(LedRed, OUTPUT);
  pinMode(LedYellow, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  digitalWrite(LedRed, LOW);
  digitalWrite(LedYellow, LOW);
  digitalWrite(LedGreen, LOW);

  wm.autoConnect(SSID, PASSWORD);
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  // initialisation de l'objet senseur de temperature
  dht = new MyDHT(DHTPIN, DHTTYPE);
}

void loop() {
  //tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp
  //dht->printTemp();      // afficher la temperature dans la console

  delay(2000);
}