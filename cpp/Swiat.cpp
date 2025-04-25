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
#include <fstream>

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

bool Swiat::zapiszStanGry() {
    std::ofstream file(save_filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << width << " " << height << " " << tura << std::endl;
    
    int validOrgs = 0;
    for (auto& org : organizmy) {
        if (org) validOrgs++;
    }
    
    file << validOrgs << std::endl;
    
    for (auto& org : organizmy) {
        if (org) {
            std::string ikona = org->getIkona();
            file << ikona << " ";
            
            file << org->getX() << " " << org->getY() << " ";
            file << org->getSila() << " " << org->getInicjatywa() << " ";
            file << org->getWiek() << " ";
            file << org->isMartwy() << " "; 
            
            if (ikona == "🧙") {
                Czlowiek* czlowiek = dynamic_cast<Czlowiek*>(org.get());
                if (czlowiek) {
                    file << czlowiek->czyTarczaAktywna() << " ";
                    file << czlowiek->pozostaleTuryTarczy() << " ";
                    file << czlowiek->pozostaleTuryCooldownu() << " ";
                }
            }
            
            file << std::endl;
        }
    }
    
    file.close();
    return true;
}

bool Swiat::wczytajStanGry() {
    std::ifstream file(save_filename);
    if (!file.is_open()) {
        return false;
    }
    
    organizmy.clear();
    
    historia.clear();
    
    file >> width >> height >> tura;
    
    int orgCount;
    file >> orgCount;
    
    for (int i = 0; i < orgCount; i++) {
        std::string ikona;
        int x, y, sila, inicjatywa, wiek;
        bool martwy;
        
        file >> ikona >> x >> y >> sila >> inicjatywa >> wiek >> martwy;
        
        std::unique_ptr<Organizm> nowyOrganizm;
        
        if (ikona == "🧙") {
            bool tarczaAktywna;
            int pozostaleTuryTarczy, pozostaleTuryCooldownu;
            file >> tarczaAktywna >> pozostaleTuryTarczy >> pozostaleTuryCooldownu;
            
            auto czlowiek = std::make_unique<Czlowiek>(x, y, wiek);
            if (tarczaAktywna) {
                czlowiek->aktywujTarcze();
                czlowiek->setLicznikTarczy(pozostaleTuryTarczy);
            }
            czlowiek->setCooldownTarczy(pozostaleTuryCooldownu);
            nowyOrganizm = std::move(czlowiek);
        }
        // Zwierzęta
        else if (ikona == "🐺") { 
            nowyOrganizm = std::make_unique<Wilk>(x, y, wiek);
        }
        else if (ikona == "🐑") { 
            nowyOrganizm = std::make_unique<Owca>(x, y, wiek);
        }
        else if (ikona == "🦊") {
            nowyOrganizm = std::make_unique<Lis>(x, y, wiek);
        }
        else if (ikona == "🐢") { 
            nowyOrganizm = std::make_unique<Zolw>(x, y, wiek);
        }
        else if (ikona == "🦌") {
            nowyOrganizm = std::make_unique<Antylopa>(x, y, wiek);
        }
        else if (ikona == "🌿") {
            nowyOrganizm = std::make_unique<Trawa>(x, y, wiek);
        }
        else if (ikona == "🌼") {
            nowyOrganizm = std::make_unique<Mlecz>(x, y, wiek);
        }
        else if (ikona == "🍇") {
            nowyOrganizm = std::make_unique<Guarana>(x, y, wiek);
        }
        else if (ikona == "🍄") {
            nowyOrganizm = std::make_unique<WilczeJagody>(x, y, wiek);
        }
        else if (ikona == "🌱") {
            nowyOrganizm = std::make_unique<BarszczSosnowskiego>(x, y, wiek);
        }
        
        if (nowyOrganizm) {
            nowyOrganizm->setSila(sila);
            nowyOrganizm->setMartwy(martwy);
            organizmy.push_back(std::move(nowyOrganizm));
        } 
    }
    
    file.close();

    std::string komunikat = "Wczytano stan gry z pliku " + save_filename;
    dodajKomunikat(komunikat);
    
    return true;
}

void Swiat::symulacja() {
    bool gameLoaded = false;
    if (std::ifstream(save_filename).good()) {
        std::cout << "Znaleziono zapisaną grę. Naciśnij C aby wczytać, lub dowolny inny klawisz aby rozpocząć nową grę...\n";
        int input = getch();
        if (input == 'c' || input == 'C') {
            gameLoaded = wczytajStanGry();
        }
    }
    
    if (!gameLoaded) {
        nowaPopulacja();
    }
    
    rysujSwiat();
    
    while (true) {
        Czlowiek* czlowiek = znajdzCzlowieka();
        
        if (czlowiek) {
            std::cout << "Sterowanie: Strzałki - ruch, Q - aktywacja Tarczy Alzura, N - następna tura bez ruchu, ESC - wyjście\n";
            std::cout << "S - zapisz grę, C - wczytaj grę\n";
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
            std::cout << "S - zapisz grę, C - wczytaj grę\n";
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
        else if (input == 's' || input == 'S') {
            if (zapiszStanGry()) {
                std::cout << "Gra została zapisana do pliku " << save_filename << std::endl;
                dodajKomunikat("Zapisano stan gry do pliku " + save_filename);
            } else {
                std::cout << "Nie udało się zapisać gry!" << std::endl;
                dodajKomunikat("Nie udało się zapisać gry!");
            }
            continue;
        } else if (input == 'c' || input == 'C') {
            if (wczytajStanGry()) {
                std::cout << "Gra została wczytana z pliku " << save_filename << std::endl;
                rysujSwiat();
                continue;
            } else {
                std::cout << "Nie udało się wczytać gry!" << std::endl;
                dodajKomunikat("Nie udało się wczytać gry!");
                continue;
            }
        }
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
    }
}

void Swiat::wykonajTure() {
    historia.clear();
    
    usunMartweOrganizmy();
    
    std::string komunikat = "Rozpoczęcie tury " + std::to_string(tura + 1);
    dodajKomunikat(komunikat);
    
    std::vector<std::reference_wrapper<std::unique_ptr<Organizm>>> organizmy_ref;
    for (auto& organizm : organizmy) {
        if (organizm && !organizm->isMartwy()) {
            organizmy_ref.push_back(std::ref(organizm));
        }
    }
    
    std::sort(
        organizmy_ref.begin(), 
        organizmy_ref.end(), 
        [](const auto& a, const auto& b) {
            if (a.get()->getInicjatywa() == b.get()->getInicjatywa()) {
                return a.get()->getWiek() > b.get()->getWiek();
            }
            return a.get()->getInicjatywa() > b.get()->getInicjatywa();
        }
    );
    
    for (auto& org_ref : organizmy_ref) {
        auto& org = org_ref.get();
        if (org && !org->isMartwy()) {
            org->setWiek(org->getWiek() + 1);
            org->akcja();
        }
    }

    usunMartweOrganizmy();
    this->tura++;
}

void Swiat::usunMartweOrganizmy() {}

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
    
    std::cout << "👨 - Człowiek, W - Wilk, L - Lis, O - Owca, Z - Żółw, A - Antylopa, 🌿 - Trawa, 🌼 - Mlecz, 🍇 - Guarana, 🍄 - Wilcze Jagody, 🌱 - Barszcz Sosnowskiego, . - puste pole\n\n";

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

    std::cout << "\nNaciśnij Enter dla następnej tury, ESC aby wyjść, S aby zapisać grę, C aby wczytać grę\n";
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