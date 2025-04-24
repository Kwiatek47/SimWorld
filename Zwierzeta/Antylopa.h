#pragma once
#include "Zwierze.h"
#include <memory>

class Antylopa : public Zwierze {
public:
    Antylopa(int x, int y, int wiek=0);
    
    void akcja() override;
    
    // Metoda implementująca specjalną zdolność antylopy do ucieczki
    bool czyUciekl(Organizm* atakujacy) override;
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<Antylopa>(x, y, 0);
    }
}; 