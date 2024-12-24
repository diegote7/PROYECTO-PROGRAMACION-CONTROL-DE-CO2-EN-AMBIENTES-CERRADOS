#include "Extractor.h"
#include <Arduino.h>

Extractor::Extractor(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);  // Iniciar apagado
}

void Extractor::encender() {
    digitalWrite(pin, HIGH);
}

void Extractor::apagar() {
    digitalWrite(pin, LOW);
}
