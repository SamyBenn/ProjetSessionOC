#include <Arduino.h>
#include "MyOledViewWorkingCOLD.h"
using namespace std;

void MyOledViewWorkingCOLD::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);

    //adafruit->setTextSize(2);
    //adafruit->setCursor(0, 0);
    //adafruit->print("SAC System");

    //adafruit->setTextSize(1);
    //adafruit->setCursor(0, 20);
    //adafruit->print("ID: ");
    //adafruit->setCursor(20, 20);
    //adafruit->print(getTag("id").c_str());
    adafruit->setCursor(80, 20);
    adafruit->print("Waiting");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());

    adafruit->setCursor(80, 30);
    displayGifFire(adafruit, 60, 30);

    //adafruit->setTextSize(1);
    //adafruit->setCursor(40,50);
    //adafruit->print(getTag("ipAddr").c_str());

    adafruit->display();
}

void MyOledViewWorkingCOLD::update(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);

    adafruit->setTextSize(1);
    adafruit->setCursor(80, 20);
    adafruit->print("Waiting");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());

    //adafruit->setCursor(80, 30);
    //displayGifFire(adafruit, 60, 30);


    adafruit->display();
}