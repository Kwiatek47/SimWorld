#include "BarszczSosnowskiego.h"
#include "../Zwierzeta/Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, int wiek) : Roslina("🌱", 10, x, y, wiek) {}

void BarszczSosnowskiego::akcja() {
    Roslina::akcja();
    
    const std::vector<std::pair<int, int>> kierunki = {
        {0, 1}, {0, -1}, {-1, 0}, {1, 0}, 
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1} 
    };
    
    bool zabitoKogos = false;
    for (const auto& [dx, dy] : kierunki) {
        int nx = x + dx;
        int ny = y + dy;
        
        if (nx < 0 || nx >= swiatRef->getWidth() || ny < 0 || ny >= swiatRef->getHeight()) {
            continue;
        }
        
        Organizm* organizm = swiatRef->getOrganizm(nx, ny);
        if (organizm != nullptr && !organizm->isMartwy()) {
            Zwierze* zwierze = dynamic_cast<Zwierze*>(organizm);
            if (zwierze) {
                zwierze->setMartwy(true);
                zabitoKogos = true;
                
                std::string komunikat = "Barszcz Sosnowskiego zabił " + zwierze->getIkona() + 
                                       " na pozycji (" + std::to_string(nx) + "," + std::to_string(ny) + ")";
                swiatRef->dodajKomunikat(komunikat);
            }
        }
    }
    
    if (zabitoKogos) {
        std::string komunikat = "Barszcz Sosnowskiego spowodował śmierć zwierząt w swoim sąsiedztwie!";
        swiatRef->dodajKomunikat(komunikat);
    }
}

void BarszczSosnowskiego::kolizja(Organizm* organizmNaNowejPozycji) {
    std::string komunikat = "Barszcz Sosnowskiego został zjedzony przez " + organizmNaNowejPozycji->getIkona() + 
                          ". Zwierzę umiera po zjedzeniu trującej rośliny!";
    swiatRef->dodajKomunikat(komunikat);
    
    organizmNaNowejPozycji->setMartwy(true);
    this->setMartwy(true);
}
