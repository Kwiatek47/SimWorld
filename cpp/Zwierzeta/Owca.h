#pragma once 
#include "Zwierze.h"
#include <memory>

class Owca : public Zwierze {
public:
        Owca(int x, int y, int wiek=0);
        std::unique_ptr<Organizm> kopiuj(int x, int y) override {
                return std::make_unique<Owca>(x, y, 0);
        }
};