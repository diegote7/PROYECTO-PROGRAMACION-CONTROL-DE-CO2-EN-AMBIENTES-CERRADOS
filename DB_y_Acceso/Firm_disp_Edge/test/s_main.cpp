#include <Arduino.h>
#include <WiFi.h>
#include "SensorDataAPI.h"
#include "time.h"

// Credenciales WiFi y API
const char* ssid = "Fibertel WiFi032 2.4GHz";
const char* password = "vuelalto67";
const char* apiEndpoint = "http://localhost:5000/data";  // Cambia según tu configuración
const char* loginEndpoint = "http://localhost:5000/login";  // Ruta para obtener el token JWT
const char* apiKey = "plata";
const char* username = "admin";  // Cambia según tu usuario
const char* userPassword = "password";  // Cambia según tu contraseña
const int id_disp = 6;

// Instancia de la clase SensorDataAPI
SensorDataAPI sensorAPI(ssid, password, apiEndpoint, loginEndpoint, apiKey, username, userPassword);

// Contador para simular el envío cada 60 segundos
int triggerAPI = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Conectar a la red WiFi
    sensorAPI.connectWiFi();

    // Obtener el token JWT
    if (!sensorAPI.getAuthToken()) {
        Serial.println("Error al obtener el token JWT, reiniciando...");
        ESP.restart();  // Reiniciar si no se puede obtener el token
    }
}

void loop() {
    // Simulación de los datos de los sensores
    float simulatedTemp = random(20, 30) + random(0, 100) / 100.0;
    float simulatedHumidity = random(40, 70) + random(0, 100) / 100.0;
    float simulatedPressure = random(1000, 1050) + random(0, 100) / 100.0;
    float simulatedGasConcentration = random(200, 400) + random(0, 100) / 100.0;

// Imprimir los valores simulados
    Serial.println("Datos simulados:");
    Serial.print("Temperatura: "); Serial.println(simulatedTemp);
    Serial.print("Humedad: "); Serial.println(simulatedHumidity);
    Serial.print("Presión: "); Serial.println(simulatedPressure);
    Serial.print("Concentración de gas: "); Serial.println(simulatedGasConcentration);

    // Enviar los datos simulados al middleware cada 60 segundos
    if (triggerAPI == 60) {
        triggerAPI = 0;
        Serial.println("Enviando los datos simulados al middleware...");
        sensorAPI.sendData(simulatedTemp, simulatedHumidity, simulatedPressure, simulatedGasConcentration, id_disp);
        Serial.println("Datos enviados.");
    }

    delay(1000); // Esperar 1 segundo antes de la siguiente simulación
    triggerAPI++;
}