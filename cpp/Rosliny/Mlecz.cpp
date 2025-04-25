#include "Mlecz.h"
#include <cstdlib>

Mlecz::Mlecz(int x, int y, int wiek) : Roslina("🌼", 0, x, y, wiek) {}

void Mlecz::akcja() {
    for (int i = 0; i < 3; i++) {
        Roslina::akcja();
    }
}
