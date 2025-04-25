#pragma once
#include "Zwierze.h"
#include <memory>

class Zolw : public Zwierze {
public:
    Zolw(int x, int y, int wiek=0);
    
    void akcja() override;
    
    bool czyOdbilAtak(Organizm* atakujacy) override;
    
    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<Zolw>(x, y, 0);
    }
}; 