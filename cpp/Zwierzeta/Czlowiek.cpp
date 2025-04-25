#include "Czlowiek.h"
#include "../Swiat.h"
#include <iostream>

Czlowiek::Czlowiek(int x, int y, int wiek) : Zwierze("🧙", 5, 4, x, y, wiek) {}

void Czlowiek::akcja() {
    aktualizujTarcze();
    
    int nx = x, ny = y;
    
    switch (kierunekRuchu) {
        case KierunekRuchu::GORA:    ny = y - 1; break;
        case KierunekRuchu::DOL:     ny = y + 1; break;
        case KierunekRuchu::LEWO:    nx = x - 1; break;
        case KierunekRuchu::PRAWO:   nx = x + 1; break;
        case KierunekRuchu::BRAK:    return;    
    }
    
    kierunekRuchu = KierunekRuchu::BRAK;
    
    if (nx < 0 || nx >= swiatRef->getWidth() || 
        ny < 0 || ny >= swiatRef->getHeight()) {
        return;
    }
    
    Organizm* organizmNaNowejPozycji = swiatRef->getOrganizm(nx, ny);
    
    if (organizmNaNowejPozycji == nullptr) {
        if (this->zmienPozycje(nx, ny)) {
            this->prevX = this->x;
            this->prevY = this->y;
            this->x = nx;
            this->y = ny;
        }
    } else {
        this->kolizja(organizmNaNowejPozycji);
    }
}

void Czlowiek::kolizja(Organizm* organizmNaNowejPozycji) {
    if (tarczaAktywna) {
        Zwierze* zwierzeNaPolu = dynamic_cast<Zwierze*>(organizmNaNowejPozycji);
        if (zwierzeNaPolu) {
            int ox = zwierzeNaPolu->getX();
            int oy = zwierzeNaPolu->getY();
            
            auto sasiednie = swiatRef->sasiedniePustePola(ox, oy);
            
            if (!sasiednie.empty()) {
                auto [nx, ny] = sasiednie[rand() % sasiednie.size()];
                
                if (zwierzeNaPolu->zmienPozycje(nx, ny)) {
                    zwierzeNaPolu->setPrevPosition(ox, oy);
                    zwierzeNaPolu->setPosition(nx, ny);
                    
                    std::string komunikat = "Tarcza Alzura odrzuciła " + 
                                           zwierzeNaPolu->getIkona() + 
                                           " na pozycję (" + std::to_string(nx) + 
                                           "," + std::to_string(ny) + ")";
                    swiatRef->dodajKomunikat(komunikat);
                    
                    if (this->zmienPozycje(ox, oy)) {
                        this->prevX = this->x;
                        this->prevY = this->y;
                        this->x = ox;
                        this->y = oy;
                    }
                    return;
                }
            }
        }
    }
    
    Organizm::kolizja(organizmNaNowejPozycji);
}

void Czlowiek::ustawKierunekRuchu(KierunekRuchu kierunek) {
    this->kierunekRuchu = kierunek;
}

bool Czlowiek::aktywujTarcze() {
    if (!tarczaAktywna && cooldownTarczy == 0) {
        tarczaAktywna = true;
        licznikTarczy = 5;
        
        std::string komunikat = "Aktywowano Tarczę Alzura!";
        swiatRef->dodajKomunikat(komunikat);
        return true;
    }
    return false;
}

void Czlowiek::aktualizujTarcze() {
    if (tarczaAktywna) {
        licznikTarczy--;
        
        if (licznikTarczy <= 0) {
            tarczaAktywna = false;
            cooldownTarczy = 5;
            
            std::string komunikat = "Tarcza Alzura wygasła! Czas odnowienia: 5 tur.";
            swiatRef->dodajKomunikat(komunikat);
        }
    } 
    else if (cooldownTarczy > 0) {
        cooldownTarczy--;
        
        if (cooldownTarczy == 0) {
            std::string komunikat = "Tarcza Alzura jest gotowa do użycia!";
            swiatRef->dodajKomunikat(komunikat);
        }
    }
} 