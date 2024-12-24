#ifndef CONTROL_BAT_H
#define CONTROL_BAT_H

class ControlBateria {
public:
    void Control_bat(int pin);
    float leerNivelBateria();  // Devuelve el nivel de batería en voltios

private:
    int pin;
};

#endif
