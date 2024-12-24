#include "SensorDataAPI.h"

SensorDataAPI::SensorDataAPI(const char* ssid, const char* password, const char* ruta, const char* apikey, Extractor& extractor, IPAddress ip, IPAddress gateway, IPAddress subnet)
    : ssid(ssid), password(password), ruta(ruta), apikey(apikey), extractor(extractor), ip(ip), gateway(gateway), subnet(subnet), server(80) {}

void SensorDataAPI::conectarWiFi() {
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conectado a WiFi con IP: " + WiFi.localIP().toString());

    server.begin();  // Iniciar el servidor HTTP
}

void SensorDataAPI::enviarLecturas(float co2, float temperatura, float humedad, float nivelBateria, int id_disp) {
    HTTPClient http;
    http.begin(ruta);  // Cambia la IP según tu servidor

    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-API-KEY", apikey);

    String postData = "{\"dispositivo_id\": "+ String(id_disp) +", \"co2_ppm\": " + String(co2) +
                      ", \"temperatura\": " + String(temperatura) +
                      ", \"humedad\": " + String(humedad) +
                      ", \"nivel_bateria\": " + String(nivelBateria) + "}";

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Respuesta del servidor: " + response);
    } else {
        Serial.println("Error al enviar datos: " + String(httpResponseCode));
    }

    http.end();
}

void SensorDataAPI::manejarComandosExtractor() {


    WiFiClient client = server.available();
    if (client) {
        String request = client.readStringUntil('\r');
        client.flush();

        if (request.indexOf("/control_extractor?accion=ENCENDER") != -1) {
            extractor.encender();
            client.println("HTTP/1.1 200 OK\r\n\r\nExtractor encendido");
        } else if (request.indexOf("/control_extractor?accion=APAGAR") != -1) {
            extractor.apagar();
            client.println("HTTP/1.1 200 OK\r\n\r\nExtractor apagado");
        }
    }
}
