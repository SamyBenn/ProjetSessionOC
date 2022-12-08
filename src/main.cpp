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

bool FourOn = false;

// variables et constantes pour led
#define GPIOLedWhite 6
#define GPIOLedBlue 8
#define GPIOLedGreen 2  // GPIO utilisee par la led verte
#define GPIOLedYellow 4 // GPIO utilisee par la led jaune
#define GPIOLedRed 17    // GPIO utilisee par la led rouge
bool ledOn = false;      // pour garder en memoire l'etat de la led

// variables et constantes pour dht22
float tempAct = 0;               // pour la temperature actuelle
char strTemp[64] = "";           // pour convertir la temperature en char[] et l'afficher sur le oled
const unsigned int GPIODHT = 3; // GPIO utilisee par le DTH
#define DHTTYPE DHT22            // Modele du DHT
MyDHT *dht;

// Oled
MyOled *myOled;
MyOledViewWorking *myOledViewWorking;
MyOledViewErrorWifiConnexion *myOledViewErrorWifiConnexion;
MyOledViewInitialisation *myOledViewInitialisation;
MyOledViewWorkingOFF *myOledViewWorkingOFF;
MyOledViewWorkingCOLD *myOledViewWorkingCOLD;
MyOledViewWorkingHEAT *myOledViewWorkingHEAT;
MyOledViewWifiAp *myOledViewWifiAp;
const unsigned int SCREEN_WIDTH = 128; // OLED display width, in pixels
const unsigned int SCREEN_HEIGHT = 64; // OLED display height, in pixels
const unsigned int OLED_RESET = 4;     // Reset pin # (or -1 if sharing Arduino reset pin)

// constantes pour la connexion wifi
const char *NAME = "esp32";
const char *SSID = "securewifi";
const char *PASSWORD = "securiti";

MyServer *myServer = NULL;
WiFiManager wm;

void displayViewAP()
{
  myOledViewErrorWifiConnexion = new MyOledViewErrorWifiConnexion();
  myOledViewErrorWifiConnexion->setNomDuSysteme(SSID);
  myOled->displayView(myOledViewErrorWifiConnexion);
}

void displayViewOFF()
{
  myOledViewWorkingOFF->setParams("nomSystem", "SAC System");
  myOledViewWorkingOFF->setParams("idSystem", "01436");
  myOledViewWorkingOFF->setParams("ipSystem", "165.227.37.65");
  myOledViewWorkingOFF->setParams("temp", strTemp);
  myOled->displayView(myOledViewWorkingOFF);
  digitalWrite(GPIOLedGreen, LOW);
  digitalWrite(GPIOLedYellow, HIGH);
  digitalWrite(GPIOLedRed, LOW);
}

void displayViewCOLD()
{
  myOledViewWorkingCOLD->setParams("nomSystem", "SAC System");
  myOledViewWorkingCOLD->setParams("idSystem", "01436");
  myOledViewWorkingCOLD->setParams("ipSystem", "165.227.37.65");
  myOledViewWorkingCOLD->setParams("temp", strTemp);
  myOled->displayView(myOledViewWorkingCOLD);
  digitalWrite(GPIOLedGreen, HIGH);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedRed, LOW);
}

void displayViewHEAT()
{
  myOledViewWorkingHEAT->setParams("nomSystem", "SAC System");
  myOledViewWorkingHEAT->setParams("idSystem", "01436");
  myOledViewWorkingHEAT->setParams("ipSystem", "165.227.37.65");
  myOledViewWorkingHEAT->setParams("temp", strTemp);
  myOled->displayView(myOledViewWorkingHEAT);
  digitalWrite(GPIOLedGreen, LOW);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedRed, HIGH);
}


void setup()
{
  Serial.begin(115200);
  // initialisation de la pin de la led et s'assurer qu'elle est fermee au demarrage
  pinMode(GPIOLedGreen, OUTPUT);
  pinMode(GPIOLedYellow, OUTPUT);
  pinMode(GPIOLedRed, OUTPUT);
  digitalWrite(GPIOLedGreen, LOW);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedRed, LOW);

  // initialisation de l'objet senseur de temperature
  dht = new MyDHT(GPIODHT, DHTTYPE);
  tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp
  Serial.print("temperature: ");
  Serial.println(tempAct); // afficher la temperature dans la console

  // Oled
  myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
  myOled->init();
  myOled->veilleDelay(30); // En secondes

  myOledViewWorking = new MyOledViewWorking();
  myOledViewInitialisation = new MyOledViewInitialisation();
  myOled->displayView(myOledViewInitialisation);

  delay(3000);

  myOledViewWifiAp = new MyOledViewWifiAp();
  myOledViewWifiAp->setNomDuSysteme(NAME);
  myOledViewWifiAp->setSsIDDuSysteme(SSID);
  myOledViewWifiAp->setPassDuSysteme(PASSWORD);
  //myOled->displayView(myOledViewWifiAp);

  wm.disconnect();
  if (!wm.autoConnect(SSID))
  {
    Serial.println("Erreur de connexion.");
    displayViewAP();
  }
  else
  {
    Serial.println("Connexion Établie.");
  }
  // myServer = new MyServer(80);
  // myServer->initAllRoutes();
  myOledViewWorkingOFF = new MyOledViewWorkingOFF();
  myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
  myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
  delay(3000);
}

void loop()
{
  tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp
  Serial.print("temperature: ");
  Serial.println(tempAct); // afficher la temperature dans la console
  sprintf(strTemp, "%g", tempAct);
  myOledViewWorking->setParams("temp", strTemp);

  if (!FourOn)
  {
    displayViewOFF();
    delay(2000);
    displayViewCOLD();
    delay(2000);
    displayViewHEAT();
  }
  else
  {
    //myOled->displayView(myOledViewWorkingHEAT);
  }

  delay(2000); // reduct
}

