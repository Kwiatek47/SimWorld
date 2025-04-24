#include "Antylopa.h"
#include <cstdlib>
#include <vector>

Antylopa::Antylopa(int x, int y, int wiek) : Zwierze("🦌", 4, 4, x, y, wiek) {}

void Antylopa::akcja() {
    std::vector<std::pair<int, int>> mozliweRuchy = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},       
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1},    
        
        {2, 0}, {-2, 0}, {0, 2}, {0, -2}        
    };
    
    int indeks = rand() % mozliweRuchy.size();
    int dx = mozliweRuchy[indeks].first;
    int dy = mozliweRuchy[indeks].second;
    
    int nx = x + dx;
    int ny = y + dy;
    
    if (nx < 0 || nx >= swiatRef->getWidth() || 
        ny < 0 || ny >= swiatRef->getHeight()) {
        return; 
    }
    
    Organizm* organizmNaNowejPozycji = swiatRef->getOrganizm(nx, ny);
    
    if (organizmNaNowejPozycji == nullptr) {
        
        this->prevX = this->x;
        this->prevY = this->y;
        this->x = nx;
        this->y = ny;
    } else {
        this->kolizja(organizmNaNowejPozycji);
    }
}

bool Antylopa::czyUciekl(Organizm* atakujacy) {
    if (rand() % 100 < 50) {
        std::vector<std::pair<int, int>> kierunki = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
            {1, 1}, {-1, 1}, {-1, -1}, {1, -1} 
        };
        
        std::vector<std::pair<int, int>> wolnePola;
        int ax = this->getX();
        int ay = this->getY();
        
        for(auto [dx, dy] : kierunki) {
            int nx = ax + dx;
            int ny = ay + dy;
            
            if(nx >= 0 && nx < swiatRef->getWidth() && 
               ny >= 0 && ny < swiatRef->getHeight() && 
               swiatRef->getOrganizm(nx, ny) == nullptr) {
                wolnePola.push_back({nx, ny});
            }
        }
        
        if(!wolnePola.empty()) {
            auto [nx, ny] = wolnePola[rand() % wolnePola.size()];
            
            this->setPosition(nx, ny);
            
            std::string komunikat = "Antylopa uciekła przed atakiem " + atakujacy->getIkona() + 
                                  " i przesunęła się na pole (" + std::to_string(nx) + "," + 
                                  std::to_string(ny) + ")";
            swiatRef->dodajKomunikat(komunikat);
            
            int staraPozycjaX = ax;
            int staraPozycjaY = ay;
            
            atakujacy->setPosition(staraPozycjaX, staraPozycjaY);
            
            return true;
        }
    }
    return false;
} 