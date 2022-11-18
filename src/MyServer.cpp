
/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

void MyServer::initAllRoutes() { 
    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        return;
    }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

    this->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });
    this->on("/leddartech.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/leddartech.jpg", "image/jpeg", "Content-Length: 50108");
    });

    this->on("/GetTemp", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("GetTemp");
        request->send(200, "text/plain", repString.c_str());
    });

    this->on("/SetTemp", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(request->hasParam("temp")){
            request->send(200, "text/plain",  "Temperature changed");
            String action = "SetTemp" ;

            char buffer[40];

            String inputTemp = request->getParam("temp")->value();
            sprintf(buffer, "%s|%s", action.c_str(), inputTemp.c_str());
            if(ptrToCallBackFunction)(*ptrToCallBackFunction)(buffer);
        }
    });
    
    this->begin();
};