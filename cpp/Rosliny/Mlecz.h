#pragma once
#include "Roslina.h"
#include <memory>

class Mlecz : public Roslina {
public:
    Mlecz(int x, int y, int wiek=0);
    
    void akcja() override;
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<Mlecz>(x, y, 0);
    }
};
