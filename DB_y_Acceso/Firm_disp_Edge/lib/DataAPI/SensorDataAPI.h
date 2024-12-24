#ifndef SENSORDATAAPI_H
#define SENSORDATAAPI_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "Extractor.h"

class SensorDataAPI {
public:
    SensorDataAPI(const char* ssid, const char* password, const char* ruta, const char* apikey, Extractor& extractor, IPAddress ip, IPAddress gateway, IPAddress subnet);
    void conectarWiFi();
    void enviarLecturas(float co2, float temperatura, float humedad, float nivelBateria, int disp);
    void manejarComandosExtractor();

private:
    const char* ssid;
    const char* password;
    const char* ruta;
    const char* apikey;
    Extractor& extractor;
    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
    WiFiServer server;  // Servidor HTTP WiFi
};

#endif
