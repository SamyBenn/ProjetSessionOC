#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"
using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print("FOUR");

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 30);
    adafruit->print("Eteint, En attente...");

    adafruit->display();
}