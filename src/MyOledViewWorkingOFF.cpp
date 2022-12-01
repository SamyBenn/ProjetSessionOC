#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"
using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();

    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print("SAC System");

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print("ID: ");
    //adafruit->setCursor(20, 20);
    //adafruit->print("ID: ");
    adafruit->setCursor(50, 20);
    adafruit->print("Ready");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(40,50);
    adafruit->print(getTag("ipAddr").c_str());

    adafruit->display();
}