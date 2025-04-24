#include "Swiat.h"
#include <iostream>
#include <ctime>
#include <limits>

int main() {
        srand(static_cast<unsigned int>(time(0)));
        
        int width = 0, height = 0;
        constexpr int MIN_SIZE = 15;
        
        std::cout << "=== Witaj w symulacji świata ===" << std::endl;
        
        while (width < MIN_SIZE) {
            std::cout << "Podaj szerokość mapy (minimum " << MIN_SIZE << "): ";
            std::cin >> width;
            
            if (std::cin.fail() || width < MIN_SIZE) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nieprawidłowa wartość! Szerokość musi być liczbą całkowitą >= " << MIN_SIZE << std::endl;
                width = 0;
            }
        }
        
        while (height < MIN_SIZE) {
            std::cout << "Podaj wysokość mapy (minimum " << MIN_SIZE << "): ";
            std::cin >> height;
            
            if (std::cin.fail() || height < MIN_SIZE) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nieprawidłowa wartość! Wysokość musi być liczbą całkowitą >= " << MIN_SIZE << std::endl;
                height = 0;
            }
        }
        
        std::cout << "Tworzenie świata o wymiarach " << width << "x" << height << "..." << std::endl;
        
        Swiat* swiat = Swiat::getStanSwiata(width, height);
        swiat->symulacja();
        
        return 0;
}