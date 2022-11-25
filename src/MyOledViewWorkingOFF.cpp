#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"
using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("WorkingOFF");

    adafruit->display();
}