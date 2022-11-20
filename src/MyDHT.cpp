/* 
    @file           : MyDHT.cpp
    @author         : Samy Bennabi
    @version        : 1.0   04/05/22
    @description    : Fonctions de la classe du senseur DHT

    platform = ESP32
    OS = Arduino
    Langage : C++

    Historique des versions
        Version     Date        Auteur      Description
        1.0         04/05/22    Samy        Premiere version du logiciel
        1.1         26/05/22    Samy        Ajout des fonctions pour humidité
        1.2         19/11/22    Samy        Retrait de fonctions inutiles

**/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MyDHT.h"

MyDHT::MyDHT(uint8_t DHTPIN, uint8_t DHTTYPE) // constructeur
{
    MyDHT::dht = new DHT_Unified(DHTPIN, DHTTYPE);
    dht->begin();
    dht->temperature().getSensor(&sensor);
    dht->humidity().getSensor(&sensor);
};

// obtenir la valeur de la temperature
// return : 0 en cas d`erreur sinon la valeur de la temperature en float
float MyDHT::getTemp()
{
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
        return 0;
    }
    else {
        return event.temperature;
    }
};

// obtenir la valeur de l`humidité
// return : 0 en cas d`erreur sinon la valeur de l`humidité en float
float MyDHT::getHumidity()
{
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
        return 0;
    }
    else {
        return event.relative_humidity;
    }
};