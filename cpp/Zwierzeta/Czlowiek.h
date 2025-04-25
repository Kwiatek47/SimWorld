#pragma once
#include "Zwierze.h"
#include <memory>

enum class KierunekRuchu {
    GORA,
    DOL,
    LEWO,
    PRAWO,
    BRAK
};

class Czlowiek : public Zwierze {
private:
    bool tarczaAktywna = false;
    int licznikTarczy = 0;   
    int cooldownTarczy = 0;  
    
    KierunekRuchu kierunekRuchu = KierunekRuchu::BRAK;

public:
    Czlowiek(int x, int y, int wiek=0);
    
    void akcja() override;
    void kolizja(Organizm* organizmNaNowejPozycji) override;
    
    void ustawKierunekRuchu(KierunekRuchu kierunek);
    bool aktywujTarcze();    
    void aktualizujTarcze();   
    
    bool czyTarczaAktywna() const { return tarczaAktywna; }
    int pozostaleTuryTarczy() const { return licznikTarczy; }
    int pozostaleTuryCooldownu() const { return cooldownTarczy; }
    
    void setLicznikTarczy(int licznik) { licznikTarczy = licznik; }
    void setCooldownTarczy(int cooldown) { cooldownTarczy = cooldown; }

    std::unique_ptr<Organizm> kopiuj(int x, int y) override {
        return std::make_unique<Czlowiek>(x, y, 0);
    }
}; 