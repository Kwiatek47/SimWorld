#pragma once
#include "Roslina.h"
#include <memory>

class Trawa : public Roslina {
public:
    Trawa(int x, int y, int wiek=0);
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<Trawa>(x, y, 0);
    }
};
