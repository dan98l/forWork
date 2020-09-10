#include <iostream>
#include "gtest/gtest.h"
#include "Fraction.hpp"

using namespace std;

int main() {
    Fraction<int> frac("9/4"), frac2(12,-7);
    cout << -frac;
    return 0;
}