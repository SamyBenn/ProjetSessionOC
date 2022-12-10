/* 
    @file           : MyDHT.h
    @author         : Samy Bennabi
    @version        : 1.0   04/05/22
    @description    : Classe permettant d'utiliser le senseur DHT

    platform = ESP32
    OS = Arduino
    Langage : C++

    Historique des versions
        Version     Date        Auteur      Description
        1.0         04/05/22    Samy        Premiere version du logiciel
        1.1         26/05/22    Samy        Ajout des fonctions pour humidité
        1.2         19/11/22    Samy        Retrait de fonctions inutiles

**/
#ifndef MYDHT_H
#define MYDHT_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class MyDHT
{
    private :
    sensor_t sensor;
    DHT_Unified *dht;
    sensors_event_t event;

    public :

    MyDHT(uint8_t DHTPIN, uint8_t DHTTYPE); // constructeur
    ~MyDHT(){}; // destructeur

    // obtenir les valeurs
    float getTemp();    // de la temperature
    float getHumidity();// de l'humidite
};

#endif