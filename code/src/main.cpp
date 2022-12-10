/**
    @file main.cpp
    @author Samy Bennabi
    @version 1.0 17/03/21  
    
    Historique des versions   
                            Versions    Date      Auteur      Description
                            1.0         24/11/22  Samy        Première version du projet
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        adafruit/DHT sensor library @ ^1.4.4
    adafruit/Adafruit GFX Library @ ^1.10.1
    adafruit/Adafruit SSD1306 @ ^2.4.0
    adafruit/Adafruit NeoPixel @ ^1.7.0
    ottowinter/ESPAsyncWebServer-esphome@^3.0.0
	bblanchon/ArduinoJson@^6.19.4
	esphome/AsyncTCP-esphome@^2.0.0
    Autres librairies (à copier dans le répertoire lib)
        MyLib
        WifiManager
    Résolution 128 x 64
            Protocole I2C, Adresse : 0x3C (défaut)
            GPIO21 : SDA
            GPIO22 : SCL

**/
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
#define GPIOLedGreen 2  // GPIO utilisee par la led verte
#define GPIOLedYellow 4 // GPIO utilisee par la led jaune
#define GPIOLedRed 17    // GPIO utilisee par la led rouge
bool ledOn = false;      // pour garder en memoire l'etat de la led

// variables et constantes pour dht22
float tempAct = 0;               // pour la temperature actuelle
char strTemp[64] = "";           // pour convertir la temperature en char[] et l'afficher sur le oled
char strCompteur[64] = "";
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
const char *SSID = "securewifi";
const char *PASSWORD = "securiti";

// serveur api 
const char* serverName = "http://165.227.37.65:3000/api/";

MyServer *myServer = NULL;
WiFiManager wm;

// fonctions pour gerer l'affichage du OLED
void displayViewAP()
{
  myOledViewWifiAp->setNomDuSysteme(wm.getWiFiHostname().c_str());
  myOledViewWifiAp->setSsIDDuSysteme(wm.getWiFiSSID().c_str());
  myOledViewWifiAp->setPassDuSysteme(wm.getWiFiPass().c_str());
  myOled->displayView(myOledViewWifiAp);
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

bool FourOn = false; // pour garder en memoire l'etat du four
int tempMin = 0;
int compteur = 0;
// fonction statique qui permet aux objets d'envoyer des messages (callBack)
//   arg0 : Action
//  arg1 ... : Parametres
std::string CallBackMessageListener(string message)
{
  while (replaceAll(message, std::string("  "), std::string(" ")));

    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);
    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string arg4 = getValue(message, ' ', 4);
    string arg5 = getValue(message, ' ', 5);
    string arg6 = getValue(message, ' ', 6);
    string arg7 = getValue(message, ' ', 7);
    string arg8 = getValue(message, ' ', 8);
    string arg9 = getValue(message, ' ', 9);
    string arg10 = getValue(message, ' ', 10);

  
  std::string tempDuFour = strTemp; //Lire le senseur de température
  if (string(actionToDo.c_str()).compare(string("askTempFour")) == 0) {
  return(tempDuFour.c_str()); }

  std::string tempsCompteur = strCompteur; //Lire le compteur
  if (string(actionToDo.c_str()).compare(string("askTempsCompteur")) == 0) {
  return(tempsCompteur.c_str()); }

if (string(actionToDo.c_str()).compare(string("select")) == 0) 
  {
    if(string(arg1.c_str()).compare(string("envoyerInfo")) == 0) 
        {
            compteur = atoi(arg2.c_str());
            tempMin = atoi(arg3.c_str());
            FourOn = false;
            Serial.println("revived Info");
            return(String("Ok").c_str());
        }

  }
  if (string(actionToDo.c_str()).compare(string("button")) == 0) 
  {
        if(string(arg1.c_str()).compare(string("demarrer"))==0){
          FourOn=true;
          Serial.println("recived GO");
            return(String("Ok").c_str());
        }
  }
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

  // Oled
  myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
  myOled->init();
  myOled->veilleDelay(30); // En secondes

  myOledViewWorking = new MyOledViewWorking();
  myOledViewInitialisation = new MyOledViewInitialisation();
  myOled->displayView(myOledViewInitialisation);

  delay(3000);


// initialisation du wifi manager
  wm.disconnect();
  if (!wm.autoConnect(SSID, PASSWORD))
  { Serial.println("Erreur de connexion.");}
  else {
    Serial.println("Connexion Établie.");
    myOledViewWifiAp = new MyOledViewWifiAp();
    displayViewAP();
  }

  myOledViewWorkingOFF = new MyOledViewWorkingOFF();
  myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
  myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);
  delay(3000);
}

void loop()
{
  tempAct = dht->getTemp(); // obtenir la temperature et la stocker dans la variable temp

  // convertissage pour utilisation dans la vue
  sprintf(strTemp, "%g", tempAct);
  sprintf(strCompteur, "%d", compteur);

  myOledViewWorking->setParams("temp", strTemp);

  if(compteur == 0){ FourOn = false; }

  if(!FourOn) { displayViewOFF(); }
  if (FourOn && tempAct >= tempMin)
  {
    displayViewHEAT();
    compteur --;
  }

  if(FourOn && tempAct < tempMin){displayViewCOLD(); }

  delay(1000); // reduct
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}