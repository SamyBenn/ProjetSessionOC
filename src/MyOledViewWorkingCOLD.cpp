#include <Arduino.h>
#include "MyOledViewWorkingCOLD.h"
using namespace std;

void MyOledViewWorkingCOLD::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("WorkingCOLD");

    adafruit->display();
}

void MyOledViewWorkingCOLD::update(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("WorkingCOLD");

    adafruit->display();
}