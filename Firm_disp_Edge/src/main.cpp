#include <Arduino.h>
#include <Wire.h>
#include "MQ135Sensor.h"
#include "AHT25Sensor.h"
#include "SensorDataAPI.h"
#include "Extractor.h"
#include "time.h"

// --------------------- Configuración de Pines ---------------------
#define MQ135_PIN 36 // GPIO36 (ADC1_CH0)
#define BATERIA 34 // GPIO34 (ADC1_CH6)
#define EXTRACTOR 12 // GPIO12

// Credenciales WiFi y API
const char* ssid = /*"Fibertel WiFi986 2.4GHz-2.4GHz"*/"Fibertel WiFi032 2.4GHz";
const char* password = /*"00434990126"*/"vuelalto67";
const char* apiEndpoint = "http://localhost:5000/api/lecturas";
const char* apiKey = "adamantium";
const int id_disp = 2;

// Configuración de IP estática
IPAddress ip(192, 168, 0, 100);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// --------------------- Inicialización de Sensores y Periféricos ---------------------
MQ135Sensor mq135(MQ135_PIN);
AHT25Sensor aht25;
Extractor extractor(EXTRACTOR);
//Control_bat bateria(BATERIA);

int triggerAPI = 0;

// Instancia de la clase SensorDataAPI
SensorDataAPI sensorAPI(ssid, password, apiEndpoint, apiKey, extractor, ip, gateway, subnet);

// --------------------- Configuración Inicial ---------------------
void setup() {
    Serial.begin(115200);
    while (!Serial);
    // Conectar a la red WiFi
    sensorAPI.conectarWiFi();
    
    Wire.begin();
    
    // Inicializar sensores y perifericos
    mq135.begin();
    aht25.begin();

   }

// --------------------- Bucle Principal ---------------------
void loop() {
    // Lectura de Sensores
    float mq135Data = mq135.readFilteredData();
    float ahtTemp, ahtHumidity;
    aht25.readData(ahtTemp, ahtHumidity);
    float nivel_bat = (analogRead(BATERIA) / 4095.0) * 3.3 * 2;

    //Pasaron 60 segundos?
    if (triggerAPI == 60){
        triggerAPI = 0;
        Serial.println("Procedemos a enviar las lecturas a la base de datos!");
        // Enviar datos a la API
        sensorAPI.enviarLecturas(ahtTemp, ahtHumidity, mq135Data, nivel_bat, id_disp);
        Serial.println("Enviaremos nuevas lecturas dentro de 60 segundos.");
    }
    sensorAPI.manejarComandosExtractor();
    delay(1000); // Esperar 1 segundo antes de la siguiente lectura
    triggerAPI ++;
}
