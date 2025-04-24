#include "Zolw.h"
#include <cstdlib>
#include <iostream>

Zolw::Zolw(int x, int y, int wiek) : Zwierze("🐢", 2, 1, x, y, wiek) {}

void Zolw::akcja() {
    int szansa = rand() % 100;
    if (szansa < 75) {
        return;
    }
    
    Zwierze::akcja();
}

bool Zolw::czyOdbilAtak(Organizm* atakujacy) {
    if (atakujacy->getSila() < 5) {
        std::string komunikat = "Żółw odparł atak " + atakujacy->getIkona();
        swiatRef->dodajKomunikat(komunikat);
        
        Zwierze* zwierzeAtakujace = dynamic_cast<Zwierze*>(atakujacy);
        if (zwierzeAtakujace) {
            zwierzeAtakujace->setPosition(zwierzeAtakujace->getPrevX(), zwierzeAtakujace->getPrevY());
        }
        return true;
    }
    return false;
} 