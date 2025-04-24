#pragma once 
#include "Zwierze.h"
#include <memory>

class Wilk : public Zwierze {
public:
        Wilk(int x, int y, int wiek=0);
        std::unique_ptr<Organizm> kopiuj(int x, int y) override {
                return std::make_unique<Wilk>(x, y, 0);
        }
};