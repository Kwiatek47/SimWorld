#pragma once 
#include "Zwierze.h"
#include <memory>

class Lis : public Zwierze {
public:
        Lis(int x, int y, int wiek=0);

        void akcja() override;

        std::unique_ptr<Organizm> kopiuj(int x, int y) override {
                return std::make_unique<Lis>(x, y, 0);
        }
};