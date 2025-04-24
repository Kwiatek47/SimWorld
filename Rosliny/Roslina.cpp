#include "Roslina.h"
#include <cstdlib>

Roslina::Roslina(std::string ikona, int sila, int x, int y, int wiek) : Organizm(ikona, sila, 0, x, y, wiek) {
    swiatRef = Swiat::getStanSwiata();
}

void Roslina::akcja() {
    int szansa = rand() % 100;
    if (szansa < szansaRozsiania) {
        rozsianie();
    }
}

void Roslina::kolizja(Organizm* organizmNaNowejPozycji) {
    if (this->ikona != "🌿" && this->ikona != "🌼") {
        std::string komunikat = "Roślina " + this->ikona + " została zjedzona przez " + organizmNaNowejPozycji->getIkona();
        swiatRef->dodajKomunikat(komunikat);
    }
    
    this->setMartwy(true);
}

void Roslina::rozsianie() {
    auto sasiednie = swiatRef->sasiedniePustePola(this->x, this->y, -1, -1);
    
    if (!sasiednie.empty()) {
        auto [nx, ny] = sasiednie[rand() % sasiednie.size()];
        
        auto nowaRoslina = this->kopiuj(nx, ny);
        
        if (nowaRoslina) {
            swiatRef->dodajOrganizm(std::move(nowaRoslina));
        }
    }
}
