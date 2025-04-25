#pragma once
#include <iostream>
#include "Swiat.h"

class Organizm {
protected:
        bool martwy = false;

        int sila;
        int inicjatywa;
        int x, y;
        int wiek;
        std::string ikona;
        Swiat* swiatRef;
        std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
public:
        Organizm(std::string ikona, int sila, int inicjatywa, int x, int y, int wiek);
        ~Organizm();

        bool isMartwy() { return martwy; }
        void setMartwy(bool martwy) { this->martwy = martwy; }
        int getX();
        int getY();
        int getSila();
        void setSila(int sila);
        int getInicjatywa();
        int getWiek();
        void setWiek(int wiek);
        
        virtual void setPosition(int newX, int newY) { this->x = newX; this->y = newY; }

        virtual void akcja() = 0;
        virtual void kolizja(Organizm* organizmNanowejPozycji);

        virtual bool czyOdbilAtak( Organizm* atakujacy) { return false; }
        virtual bool czyUciekl(Organizm* atakujacy) { return false; }
        
        void rysuj();

        std::string getIkona() { return ikona; }

        bool zmienPozycje(int x, int y);
};