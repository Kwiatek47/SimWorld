#include "Guarana.h"

Guarana::Guarana(int x, int y, int wiek) : Roslina("🍇", 0, x, y, wiek) {}

void Guarana::kolizja(Organizm* organizmNaNowejPozycji) {
    int nowaSila = organizmNaNowejPozycji->getSila() + bonusSily;
    
    std::string komunikat = "Guarana została zjedzona przez " + organizmNaNowejPozycji->getIkona() + 
                           ". Siła zjadającego wzrosła o " + std::to_string(bonusSily) + 
                           " (z " + std::to_string(organizmNaNowejPozycji->getSila()) + 
                           " do " + std::to_string(nowaSila) + ")";
    swiatRef->dodajKomunikat(komunikat);
    
    organizmNaNowejPozycji->setSila(nowaSila);
    
    this->setMartwy(true);
}
