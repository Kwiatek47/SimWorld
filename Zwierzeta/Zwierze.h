#pragma once
#include "../Organizm.h"
#include <memory>

class Zwierze : public Organizm {
protected:
        int prevX, prevY;
public:
        Zwierze(std::string ikona, int sila, int inicjatywa, int x, int y, int wiek=0);

        void akcja() override;
        void kolizja(Organizm* organizmNaNowejPozycji) override;
        void rozmnazanie(Organizm* organizmNaNowejPozycji);

        void setPrevPosition(int x, int y);
        int getPrevX() const;
        int getPrevY() const;
        
        void setPosition(int newX, int newY);

        virtual std::unique_ptr<Organizm> kopiuj(int x, int y) = 0;
};