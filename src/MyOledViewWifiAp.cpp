#include <Arduino.h>
#include "MyOledViewWifiAp.h"
using namespace std;

void MyOledViewWifiAp::setNomDuSysteme(std::string val){
    MyOledViewWifiAp::nomDuSysteme = val;
}

void MyOledViewWifiAp::setSsIDDuSysteme(std::string val){
    MyOledViewWifiAp::ssIDDuSysteme = val;
}

void MyOledViewWifiAp::setPassDuSysteme(std::string val){
    MyOledViewWifiAp::passDuSysteme = val;
}

void MyOledViewWifiAp::display(Adafruit_SSD1306 *adafruit){
    Serial.println("MyOledViewWifiAp");
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(MyOledViewWifiAp::nomDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print(MyOledViewWifiAp::ssIDDuSysteme.c_str());
    adafruit->setCursor(40, 50);
    adafruit->print(MyOledViewWifiAp::passDuSysteme.c_str());

    adafruit->display();
}

void MyOledViewWifiAp::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
}