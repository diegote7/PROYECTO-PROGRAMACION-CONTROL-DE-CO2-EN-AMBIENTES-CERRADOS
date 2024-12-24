#ifndef EXTRACTOR_H
#define EXTRACTOR_H

class Extractor {
public:
    Extractor(int pin);
    void encender();
    void apagar();

private:
    int pin;
};

#endif
