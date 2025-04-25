#pragma once
#include "../Organizm.h"
#include <memory>

class Roslina : public Organizm {
protected:
    const int szansaRozsiania = 15;
    
public:
    Roslina(std::string ikona, int sila, int x, int y, int wiek=0);
    
    void akcja() override; 
    
    void kolizja(Organizm* organizmNaNowejPozycji) override;
    
    void rozsianie();
    
    virtual std::unique_ptr<Organizm> kopiuj(int x, int y) = 0;
};
