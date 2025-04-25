#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <deque>
#include <fstream>

class Organizm;
class Czlowiek; 

class Swiat {
private:
        static Swiat* stanSwiata;
        int width, height;
        int tura = 0;
        std::vector<std::unique_ptr<Organizm>> organizmy;
        std::deque<std::string> historia;  
        const size_t max_historia_size = 15;
        const std::string save_filename = "save_game.txt";

        std::pair<int, int> znajdzLosowaPozycje();

public:
        Swiat(int w, int h);
        ~Swiat();

        void symulacja();
        void wykonajTure();
        void rysujSwiat();

        void dodajOrganizm(std::unique_ptr<Organizm> organizm);

        static Swiat* getStanSwiata();
        static Swiat* getStanSwiata(int szerokosc, int wysokosc);

        void nowaPopulacja();

        Organizm* getOrganizm(int x, int y);

        int getWidth() { return width; }
        int getHeight() { return height; } 
        int getTura() { return tura; }

        void usunMartweOrganizmy();

        std::vector<std::pair<int, int>> sasiedniePustePola(int x, int y, int parentX, int parentY);
        
        std::vector<std::pair<int, int>> sasiedniePustePola(int x, int y) {
            return sasiedniePustePola(x, y, -1, -1);
        }
        
        void dodajKomunikat(const std::string& komunikat);
        
        void wyswietlHistorie();

        Czlowiek* znajdzCzlowieka();
        
        bool zapiszStanGry();
        bool wczytajStanGry();
};