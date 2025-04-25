#pragma once
#include "Roslina.h"
#include <memory>

class BarszczSosnowskiego : public Roslina {
public:
    BarszczSosnowskiego(int x, int y, int wiek=0);
    
    // Nadpisana metoda akcja - zabija wszystkie zwierzęta w sąsiedztwie
    void akcja() override;
    
    // Przeciążona metoda kolizji - BarszczSosnowskiego zabija zjadającego
    void kolizja(Organizm* organizmNaNowejPozycji) override;
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<BarszczSosnowskiego>(x, y, 0);
    }
};
