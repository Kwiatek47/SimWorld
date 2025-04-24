#include "Organizm.h"
#include <memory>
#include "Zwierzeta/Zolw.h"

Organizm::Organizm(std::string ikona, int sila, int inicjatywa, int x, int y, int wiek) : 
    sila(sila), inicjatywa(inicjatywa), x(x), y(y), wiek(wiek), ikona(ikona) {
    swiatRef = Swiat::getStanSwiata();
}

Organizm::~Organizm() {}

void Organizm::rysuj() {
        std::cout << "Rysuje organizm: " << ikona << std::endl;
        std::cout << "Kordynacje x: " << x << " y: " << y << std::endl;
}

int Organizm::getX() {
        return this->x;
}

int Organizm::getY() {
        return this->y;
}

int Organizm::getSila() {
        return this->sila;
}

void Organizm::setSila(int sila) {
        this->sila = sila;
}

bool Organizm::zmienPozycje(int x, int y) {
        if ( x < 0 || x >= swiatRef->getWidth() || y < 0 || y >= swiatRef->getHeight() ) {
                return false;
        }
        return true;
}

void Organizm::setWiek(int wiek) {
        this->wiek = wiek;
}

int Organizm::getWiek() {
        return this->wiek;
}

int Organizm::getInicjatywa() {
        return this->inicjatywa;
}

void Organizm::kolizja(Organizm* organizmNaNowejPozycji) {
        if (organizmNaNowejPozycji == nullptr) return;
        
        if(organizmNaNowejPozycji->czyOdbilAtak(this)) {
            return;
        }
        
        if(organizmNaNowejPozycji->czyUciekl(this)) {
            return;
        }
        
        std::string komunikat = "Kolizja między " + this->ikona + " i " + organizmNaNowejPozycji->ikona;
        if (this->ikona != "🌿" && this->ikona != "🌼" && organizmNaNowejPozycji->ikona != "🌿" && organizmNaNowejPozycji->ikona != "🌼") {
            swiatRef->dodajKomunikat(komunikat);
        }
        
        if ( this->sila >= organizmNaNowejPozycji->sila ) {
                std::string komunikatWalki;
                if (this->sila == organizmNaNowejPozycji->sila) {
                    komunikatWalki = "Wygrywa atakujący " + this->ikona + " (równa siła) z " + organizmNaNowejPozycji->getIkona();
                } else {
                    komunikatWalki = "Wygrywa: " + this->ikona + " z " + organizmNaNowejPozycji->getIkona();
                }
                if (this->ikona != "🌿" && this->ikona != "🌼" && organizmNaNowejPozycji->ikona != "🌿" && organizmNaNowejPozycji->ikona != "🌼") {
                    swiatRef->dodajKomunikat(komunikatWalki);
                }
                
                organizmNaNowejPozycji->setMartwy(true);
                this->x = organizmNaNowejPozycji->getX();
                this->y = organizmNaNowejPozycji->getY();
        }
        else {
                std::string komunikatWalki = "Wygrywa: " + organizmNaNowejPozycji->ikona + " z " + this->getIkona();
                if (this->ikona != "🌿" && this->ikona != "🌼" && organizmNaNowejPozycji->ikona != "🌿" && organizmNaNowejPozycji->ikona != "🌼") {
                    swiatRef->dodajKomunikat(komunikatWalki);
                }
                
                this->setMartwy(true);
        }
}