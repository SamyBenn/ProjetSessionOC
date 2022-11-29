#include "MyOledViewInitialisation.h"

void MyOledViewInitialisation::setIdDuSysteme(std::string val){
    idDuSysteme = val;
}

void MyOledViewInitialisation::setNomDuSysteme(std::string val){
    nomDuSysteme=val;
}

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print("Initialisation");

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 40);
    adafruit->print("wait....");
    
    adafruit->display();
}

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    //
}