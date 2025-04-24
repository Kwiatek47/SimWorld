#pragma once
#include "Roslina.h"
#include <memory>

class Guarana : public Roslina {
private:
    const int bonusSily = 3;
    
public:
    Guarana(int x, int y, int wiek=0);
    
    void kolizja(Organizm* organizmNaNowejPozycji) override;
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<Guarana>(x, y, 0);
    }
};
