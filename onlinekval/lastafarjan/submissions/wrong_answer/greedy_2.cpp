#include <iostream>
int main() {
    int N, L, n, sum = -4, len = 0;     // Tar -4 från början (de fyra första bilarna har inget säkerhetsavstånd)
    std::cin >> N >> L;
    while(!(std::cin >> n).eof())       // Läs in tal för tal
        if((sum += n + 1) > L*4) break; // Om summan överstiger L*4 så har vi funnit svaret, avbryt
        else len++;                     // Antalet bilar som får plats, öka med ett
    std::cout << len;
}
