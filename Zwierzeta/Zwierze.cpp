#include "Zwierze.h"

Zwierze::Zwierze(std::string ikona, int sila, int inicjatywa, int x, int y, int wiek) : Organizm(ikona, sila, inicjatywa, x, y, wiek) {
        swiatRef = Swiat::getStanSwiata();
}

void Zwierze::akcja() {
        int randMove = rand() % 4;

        int nx = x, ny = y;
        switch (randMove) {
                case 0: nx = x + 1; break; 
                case 1: nx = x - 1; break; 
                case 2: ny = y + 1; break; 
                case 3: ny = y - 1; break; 
        }

        if (nx < 0 || nx >= swiatRef->getWidth() || 
                ny < 0 || ny >= swiatRef->getHeight()) {
                return;
        }

        Organizm* organizmNaNowejPozycji = swiatRef->getOrganizm(nx, ny);

        if( organizmNaNowejPozycji == nullptr ) {
                if ( this->zmienPozycje(nx, ny) ) {
                        this->prevX = this->x;
                        this->prevY = this->y;
                        this->x = nx;
                        this->y = ny;
                }
                return;
        } else {
                this->kolizja( organizmNaNowejPozycji );
                return;
        }
}


void Zwierze::kolizja(Organizm* organizmNaNowejPozycji) {
        if (this->getIkona() == organizmNaNowejPozycji->getIkona()) {
                rozmnazanie(organizmNaNowejPozycji);
        } else {
                Organizm::kolizja( organizmNaNowejPozycji );
        }
}

void Zwierze::rozmnazanie(Organizm* drugiOrganizm) {
        Zwierze* drugieZwierze = dynamic_cast<Zwierze*>(drugiOrganizm);
        if (!drugieZwierze) return;
        
        auto sasiednie = swiatRef->sasiedniePustePola(
            drugiOrganizm->getX(), drugiOrganizm->getY(),
            this->getX(), this->getY()
        );
    
        if (!sasiednie.empty()) {
                auto [nx, ny] = sasiednie[rand() % sasiednie.size()];
                auto nowyOrganizm = this->kopiuj(nx, ny);
                if (nowyOrganizm) {
                    std::string komunikat = "Nowe " + this->ikona + " urodziło się na pozycji (" + std::to_string(nx) + "," + std::to_string(ny) + ")";
                    swiatRef->dodajKomunikat(komunikat);
                    swiatRef->dodajOrganizm(std::move(nowyOrganizm));
                }
        } else {
            std::string komunikat = "Brak wolnych miejsc do rozmnażania dla " + this->ikona;
            swiatRef->dodajKomunikat(komunikat);
        }
}

void Zwierze::setPrevPosition(int x, int y) {
        this->prevX = x;
        this->prevY = y;
}

int Zwierze::getPrevX() const {
        return this->prevX;
}

int Zwierze::getPrevY() const {
        return this->prevY;
}

void Zwierze::setPosition(int newX, int newY) {
        this->prevX = this->x;
        this->prevY = this->y;
        this->x = newX;
        this->y = newY;
}