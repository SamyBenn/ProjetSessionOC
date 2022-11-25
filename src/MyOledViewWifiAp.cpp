#include <Arduino.h>
#include "MyOledViewWifiAp.h"
using namespace std;

void MyOledViewWifiAp::setNomDuSysteme(std::string val){
    nomDuSysteme = val;
}

void MyOledViewWifiAp::setSsIDDuSysteme(std::string val){
    ssIDDuSysteme = val;
}

void MyOledViewWifiAp::setPassDuSysteme(std::string val){
    passDuSysteme = val;
}

void MyOledViewWifiAp::display(Adafruit_SSD1306 *adafruit){
    if(adafruit){
        Serial.print("adafruuit");
    }
    Serial.println("MyOledViewWifiAp");
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("Nom: ");
    adafruit->setCursor(40, 0);
    adafruit->print(nomDuSysteme.c_str());
    adafruit->setCursor(0, 20);
    adafruit->print("SSID: ");
    adafruit->setCursor(40, 20);
    adafruit->print(ssIDDuSysteme.c_str());
    adafruit->setCursor(0, 50);
    adafruit->print("Pass: ");
    adafruit->setCursor(40, 50);
    adafruit->print(passDuSysteme.c_str());

    adafruit->display();
}

void MyOledViewWifiAp::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
}