#include <Arduino.h>
#include "MyOledViewWorkingHEAT.h"
using namespace std;

void MyOledViewWorkingHEAT::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("WorkingHEAT");

    adafruit->display();
}