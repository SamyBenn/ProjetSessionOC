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
#include "MyOled.h"
#include "MyOledView.h"
#include "MyOledViewErrorWifiConnexion.h"
#include "MyOledViewInitialisation.h"
#include "MyOledViewWifiAp.h"
#include "MyOledViewWorking.h"
#include "MyOledViewWorkingCOLD.h"
#include "MyOledViewWorkingHEAT.h"
#include "MyOledViewWorkingOFF.h"
#include "MyServer.h"

// variables et constantes pour led
#define GPIOLedRed 27   // GPIO utilisee par la led rouge
#define GPIOLedYellow 14   // GPIO utilisee par la led jaune
#define GPIOLedGreen 12   // GPIO utilisee par la led verte
bool ledOn = false; // pour garder en memoire l'etat de la led

// variables et constantes pour dht22
float tempAct=0; //pour la temperature actuelle
char strTemperature[64] = ""; //pour convertir la temperature en char[] et l'afficher sur le oled
const unsigned int GPIODHT = 15; // GPIO utilisee par le DTH
#define DHTTYPE DHT22           // Modele du DHT
MyDHT *dht;

// Oled
MyOled *myOled;
MyOledViewWorking *myoledViewWorking;
MyOledViewWorkingOFF *myoledViewWorkingOFF;
MyOledViewWorkingHEAT *myoledViewWorkingHEAT;
MyOledViewWifiAp *myOledViewWifiAp;
const unsigned int SCREEN_WIDTH = 128; // OLED display width, in pixels
const unsigned int SCREEN_HEIGHT = 64; // OLED display height, in pixels
const unsigned int OLED_RESET = 4;    // Reset pin # (or -1 if sharing Arduino reset pin)



// constantes pour la connexion wifi

const char *SSID = "securewifi";
const char *PASSWORD = "securiti";


//MyServer *myServer = NULL;
//WiFiManager wm;

void setup() {
  Serial.begin(115200);
  // initialisation de la pin de la led et s'assurer qu'elle est fermee au demarrage
  pinMode(GPIOLedRed, OUTPUT);
  pinMode(GPIOLedYellow, OUTPUT);
  pinMode(GPIOLedGreen, OUTPUT);
  digitalWrite(GPIOLedRed, LOW);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedGreen, LOW);

  String ssIDRandom, PASSRandom;
  String stringRandom;
  stringRandom = get_random_string(4).c_str();
  ssIDRandom = SSID;
  ssIDRandom = ssIDRandom + stringRandom;
  stringRandom = get_random_string(4).c_str();
  PASSRandom = PASSWORD;
  PASSRandom = PASSRandom + stringRandom;

  // initialisation de l'objet senseur de temperature
  dht = new MyDHT(GPIODHT, DHTTYPE);
  tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp
  Serial.print("temperature: ");
  Serial.println(tempAct);      // afficher la temperature dans la console

  // Oled
  myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
  myOled->init();
  myOled->veilleDelay(30); //En secondes
  myOledViewWifiAp = new MyOledViewWifiAp();
  myOledViewWifiAp->setNomDuSysteme(ssIDRandom.c_str());
  myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
  myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());

  myoledViewWorking = new MyOledViewWorking();
  myoledViewWorking->init("1");
  myoledViewWorkingOFF = new MyOledViewWorkingOFF();
  myoledViewWorkingHEAT = new MyOledViewWorkingHEAT();
  myOled->displayView(myoledViewWorkingHEAT);
  //myOled->displayView(myOledViewWifiAp);


  /*if (!wm.autoConnect(SSID, PASSWORD))
  {Serial.println("Erreur de connexion.");}
  else
  {Serial.println("Connexion Établie.");}*/
  //myServer = new MyServer(80);
  //myServer->initAllRoutes();
}

void loop() {
  tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp
  Serial.print("temperature: ");
  Serial.println(tempAct);      // afficher la temperature dans la console
  

  delay(2000);//(rduct)
}