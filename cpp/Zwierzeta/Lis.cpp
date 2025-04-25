#include "Lis.h"
#include <vector>
#include <algorithm>
#include <random>

Lis::Lis(int x, int y, int wiek) : Zwierze("🦊", 3, 7, x, y, wiek) {}

void Lis::akcja() {
        std::vector<std::pair<int, int>> losowe_kierunki = this->directions;
        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(losowe_kierunki.begin(), losowe_kierunki.end(), g);
        
        for (auto [dx, dy] : losowe_kierunki) {
                int nx = this->x + dx;
                int ny = this->y + dy;
                if( !(this->zmienPozycje(nx, ny)) ) {
                        continue;
                }
                Organizm* organizmNaNowejPozycji = swiatRef->getOrganizm(nx, ny);

                if (organizmNaNowejPozycji == nullptr || organizmNaNowejPozycji->getSila() <= this->sila) {
                        this->prevX = this->x;
                        this->prevY = this->y;
                        this->x = nx;
                        this->y = ny;
                        return;
                }
        }
};
