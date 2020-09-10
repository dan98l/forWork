#include "gtest/gtest.h"
#include "Fraction.hpp"

TEST(correctResult, test1) {
    ASSERT_EQ(5,5);
}

TEST(correctStringRepresentation, test1) {
    Fraction<int> frac(9,4);

    ASSERT_EQ("9/4", frac.getFractionString());
}

TEST(correctStringRepresentation, test2) {
    Fraction<int> frac("9");

    ASSERT_EQ("9/1", frac.getFractionString());
}

TEST(correctStringRepresentation, test3) {
    Fraction<int> frac("9/-12");

    ASSERT_EQ("-9/12", frac.getFractionString());
}

TEST(correctCalculation, test1) {
    Fraction<int> frac("9/22"), frac2(21,22);

    ASSERT_EQ((frac + frac2).getFractionString(), "30/22");
}

TEST(correctCalculation, test2) {
    Fraction<int> frac("9/22"), frac2(21,22);

    ASSERT_EQ((frac - frac2).getFractionString(), "-12/22");
}

TEST(correctInverse, test1) {
    Fraction<int> frac("9/22");

    ASSERT_EQ("22/9", frac.inverse().getFractionString());
}