#include "Swiat.h"
#include "Organizm.h"
#include "Zwierzeta/Wilk.h"
#include "Zwierzeta/Lis.h"
#include "Zwierzeta/Owca.h"
#include "Zwierzeta/Zolw.h"
#include "Zwierzeta/Antylopa.h"
#include "Zwierzeta/Czlowiek.h"
#include "Rosliny/Trawa.h"
#include "Rosliny/Mlecz.h"
#include "Rosliny/Guarana.h"
#include "Rosliny/WilczeJagody.h"
#include "Rosliny/BarszczSosnowskiego.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <memory>
#include <iomanip>
#include <cctype> 
#include <ctime>  

#ifdef _WIN32
#include <conio.h>
#else
#include <iostream>
#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#include <iostream>

Swiat* Swiat::getStanSwiata(){
        return stanSwiata;
}
    
Swiat* Swiat::getStanSwiata(int szerokosc, int wysokosc){
        if(stanSwiata != nullptr){
            delete stanSwiata;
        }
    
        stanSwiata = new Swiat(szerokosc,wysokosc);
        return stanSwiata;
}
    
Swiat* Swiat::stanSwiata = nullptr;

Swiat::Swiat(int w, int h) : width(w), height(h) {}
    
std::pair<int, int> Swiat::znajdzLosowaPozycje() {
    int x, y;
    do {
        x = rand() % width;
        y = rand() % height;
    } while (getOrganizm(x, y) != nullptr);
    
    return {x, y};
}

void Swiat::nowaPopulacja(){
        srand(time(nullptr)); 
        
        auto [x, y] = znajdzLosowaPozycje();
        dodajOrganizm(std::make_unique<Czlowiek>(x, y));
        
        for (int i = 0; i < 3; i++) {
            auto [x, y] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Wilk>(x, y));
            
            auto [x2, y2] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Lis>(x2, y2));
            
            auto [x3, y3] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Owca>(x3, y3));
            
            auto [x4, y4] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Zolw>(x4, y4));
            
            auto [x5, y5] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Antylopa>(x5, y5));
        }
        
        for (int i = 0; i < 3; i++) { 
            auto [x, y] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Trawa>(x, y));
            
            auto [x2, y2] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Mlecz>(x2, y2));
            
            auto [x3, y3] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<Guarana>(x3, y3));
        }
        
        for (int i = 0; i < 2; i++) {
            auto [x, y] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<WilczeJagody>(x, y));
            
            auto [x2, y2] = znajdzLosowaPozycje();
            dodajOrganizm(std::make_unique<BarszczSosnowskiego>(x2, y2));
        }
}

Swiat::~Swiat(){}

void Swiat::symulacja() {
    nowaPopulacja();
    rysujSwiat();
    
    while (true) {
        Czlowiek* czlowiek = znajdzCzlowieka();
        
        if (czlowiek) {
            std::cout << "Sterowanie: Strzałki - ruch, Q - aktywacja Tarczy Alzura, N - następna tura bez ruchu, ESC - wyjście\n";
            std::cout << "Stan Tarczy Alzura: ";
            if (czlowiek->czyTarczaAktywna()) {
                std::cout << "AKTYWNA (pozostało " << czlowiek->pozostaleTuryTarczy() << " tur)\n";
            } else if (czlowiek->pozostaleTuryCooldownu() > 0) {
                std::cout << "COOLDOWN (pozostało " << czlowiek->pozostaleTuryCooldownu() << " tur)\n";
            } else {
                std::cout << "GOTOWA DO UŻYCIA\n";
            }
        } else {
            std::cout << "Człowiek nie żyje! Naciśnij ESC aby wyjść lub ENTER aby kontynuować symulację\n";
        }
        
        std::cout << "Naciśnij klawisz, aby kontynuować (Strzałki=ruch, Q=tarcza, N=następna tura, ESC=wyjście)...\n";
        
        int input = getch();
        
        if (input == 27) { 
            #ifdef _WIN32
            return;
            #else
            if (getch() == 91) { 
                int strzalka = getch(); 
                
                if (czlowiek) {
                    switch (strzalka) {
                        case 65:
                            czlowiek->ustawKierunekRuchu(KierunekRuchu::GORA);
                            break;
                        case 66:
                            czlowiek->ustawKierunekRuchu(KierunekRuchu::DOL);
                            break;
                        case 68: 
                            czlowiek->ustawKierunekRuchu(KierunekRuchu::LEWO);
                            break;
                        case 67:
                            czlowiek->ustawKierunekRuchu(KierunekRuchu::PRAWO);
                            break;
                    }
                }
            } else {
                return;
            }
            #endif
        } else if (input == 'q' || input == 'Q') {
            if (czlowiek) {
                czlowiek->aktywujTarcze();
            }
        } else if (input == 'n' || input == 'N') {} 
        #ifdef _WIN32
        else if (input == 0 || input == 224) {
            input = getch();
            
            if (czlowiek) {
                switch (input) {
                    case 72: 
                        czlowiek->ustawKierunekRuchu(KierunekRuchu::GORA);
                        break;
                    case 80:
                        czlowiek->ustawKierunekRuchu(KierunekRuchu::DOL);
                        break;
                    case 75: 
                        czlowiek->ustawKierunekRuchu(KierunekRuchu::LEWO);
                        break;
                    case 77: 
                        czlowiek->ustawKierunekRuchu(KierunekRuchu::PRAWO);
                        break;
                }
            }
        }
        #endif
        
        wykonajTure();
        rysujSwiat();
        this->tura = this->tura + 1;
    }
}

void Swiat::wykonajTure() {
        try {
                historia.clear();
                
                std::string komunikat = "Rozpoczęcie tury " + std::to_string(tura + 1);
                dodajKomunikat(komunikat);
                
                std::sort(organizmy.begin(), organizmy.end(), [](const std::unique_ptr<Organizm>& a, const std::unique_ptr<Organizm>& b) {
                        if (!a || !b) return false;
                        if (a->getInicjatywa() == b->getInicjatywa()) {
                            return a->getWiek() > b->getWiek();
                        }
                        return a->getInicjatywa() > b->getInicjatywa();
                });

                std::vector<Organizm*> organizmyTemp;
                for (const auto& org : organizmy) {
                        if (org && !org->isMartwy()) {
                                organizmyTemp.push_back(org.get());
                        }
                }

                for (auto organizm : organizmyTemp) {
                        if (organizm && !organizm->isMartwy()) {
                                organizm->akcja();
                        }
                }

                for (auto& organizm : organizmy) {
                        if (organizm && !organizm->isMartwy()) {
                                organizm->setWiek(organizm->getWiek() + 1);
                        }
                }

                usunMartweOrganizmy();
        } catch (const std::exception& e) {
                std::cerr << "Błąd podczas wykonywania tury: " << e.what() << std::endl;
        } catch (...) {
                std::cerr << "Nieznany błąd podczas wykonywania tury" << std::endl;
        }
}

void Swiat::usunMartweOrganizmy() {
        organizmy.erase(
            std::remove_if(organizmy.begin(), organizmy.end(),
                [](const std::unique_ptr<Organizm>& org) {
                    return !org || org->isMartwy();
                }),
            organizmy.end()
        );
}

void Swiat::dodajKomunikat(const std::string& komunikat) {
    historia.push_back(komunikat);
    
    if (historia.size() > max_historia_size) {
        historia.pop_front();
    }
}

void Swiat::wyswietlHistorie() {
    std::cout << "\n=== Log wydarzeń ===\n";
    
    if (historia.empty()) {
        std::cout << "Brak zdarzeń do wyświetlenia.\n";
    } else {
        int i = 1;
        for (const auto& komunikat : historia) {
            std::cout << i << ". " << komunikat << "\n";
            i++;
        }
    }
    
    std::cout << "==================\n";
}

void Swiat::rysujSwiat() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif

    std::cout << "==========================================\n";
    std::cout << "                   SimWorld               \n";
    std::cout << "==========================================\n";
    std::cout << "Autor: Antoni Kwiatek                     \n";
    std::cout << "Indeks: 203548                            \n";
    std::cout << "==========================================\n\n";

    std::cout << "Tura: " << tura << "\n";
    std::cout << "Legenda: ";
    
    std::cout << "👨 - Człowiek, W - Wilk, L - Lis, O - Owca, Z - Żółw, A - Antylopa, 🌿 - Trawa, 🌼 - Mlecz, 🍇 - Guarana, 🫐 - Wilcze Jagody, 🌱 - Barszcz Sosnowskiego, . - puste pole\n\n";

    std::cout << "+";
    for (int i = 0; i < 2 * width; ++i) std::cout << "-";
    std::cout << "+\n";

    for (int y = 0; y < height; ++y) {
        std::cout << "|";
        for (int x = 0; x < width; ++x) {
            Organizm* org = getOrganizm(x, y);
            if (org != nullptr && !org->isMartwy()) {
                std::cout << org->getIkona();
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "|\n";
    }

    std::cout << "+";
    for (int i = 0; i < 2 * width; ++i) std::cout << "-";
    std::cout << "+\n";

    wyswietlHistorie();

    std::cout << "\nNaciśnij Enter dla następnej tury, ESC aby wyjść\n";
}

void Swiat::dodajOrganizm(std::unique_ptr<Organizm> organizm) {
        if (organizm) {
                organizmy.push_back(std::move(organizm));
        }
}

Organizm* Swiat::getOrganizm(int x, int y) {
        for (auto& organizm : organizmy) {
            if (organizm && organizm->getX() == x && organizm->getY() == y && !organizm->isMartwy()) {
                return organizm.get();
            }
        }
        return nullptr;
}

std::vector<std::pair<int, int>> Swiat::sasiedniePustePola(int x, int y, int parentX, int parentY) {
        std::vector<std::pair<int, int>> wolnePola;
        
        const std::vector<std::pair<int, int>> kierunki = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0} 
        };
    
        for (const auto& [dx, dy] : kierunki) {
            int noweX = x + dx;
            int noweY = y + dy;
            
            if (noweX >= 0 && noweX < width &&
                noweY >= 0 && noweY < height &&
                getOrganizm(noweX, noweY) == nullptr &&
                !(noweX == parentX && noweY == parentY)) {
                wolnePola.emplace_back(noweX, noweY);
            }
        }
    
        return wolnePola;
}

Czlowiek* Swiat::znajdzCzlowieka() {
    for (auto& organizm : organizmy) {
        Czlowiek* czlowiek = dynamic_cast<Czlowiek*>(organizm.get());
        if (czlowiek && !czlowiek->isMartwy()) {
            return czlowiek;
        }
    }
    return nullptr;
}