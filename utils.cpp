//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#include "utils.h"

int random(int a, int b){
    return a + rand()%(b-a+1);
}

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}
