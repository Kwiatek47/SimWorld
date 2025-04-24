#pragma once
#include "Roslina.h"
#include <memory>

class WilczeJagody : public Roslina {
public:
    WilczeJagody(int x, int y, int wiek=0);
    
    void kolizja(Organizm* organizmNaNowejPozycji) override;
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<WilczeJagody>(x, y, 0);
    }
};
