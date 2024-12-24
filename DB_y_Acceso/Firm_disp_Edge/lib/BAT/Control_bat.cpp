#include "Control_bat.h"
#include <Arduino.h>

Control_bat::Control_bat(int pin) : pin(pin) {
    pinMode(pin, INPUT);
}

float Control_bat::leerNivelBateria() {
    int valorLeido = analogRead(pin);  // Lectura analógica
    return (valorLeido / 4095.0) * 3.3 * 2;  // Ajuste de escala para divisor resistivo
}
