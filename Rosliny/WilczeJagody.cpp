#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(int x, int y, int wiek) : Roslina("🍄", 99, x, y, wiek) {}

void WilczeJagody::kolizja(Organizm* organizmNaNowejPozycji) {
    std::string komunikat = "Wilcze Jagody zostały zjedzone przez " + organizmNaNowejPozycji->getIkona() + 
                          ". Zwierzę umiera po zjedzeniu trującej rośliny!";
    swiatRef->dodajKomunikat(komunikat);
    
    organizmNaNowejPozycji->setMartwy(true);
    this->setMartwy(true);
}
