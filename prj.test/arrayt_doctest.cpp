#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "arrayt/arrayt.hpp"

TEST_CASE("Default constructor and Size method") {
    ArrayT<int> array;
    CHECK(array.Size() == 0);
}

TEST_CASE("Constructor with size and operator[]") {
    ArrayT<int> array(5);
    CHECK(array.Size() == 5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i * 10;
        CHECK(array[i] == i * 10);
    }
}

TEST_CASE("Copy constructor") {
    ArrayT<int> array1(3);
    array1[0] = 1;
    array1[1] = 2;
    array1[2] = 3;

    ArrayT<int> array2(array1);
    CHECK(array2.Size() == 3);
    for (int i = 0; i < 3; ++i) {
        CHECK(array2[i] == array1[i]);
    }
}

TEST_CASE("Assignment operator") {
    ArrayT<int> array1(3);
    array1[0] = 1;
    array1[1] = 2;
    array1[2] = 3;

    ArrayT<int> array2;
    array2 = array1;
    CHECK(array2.Size() == 3);
    for (int i = 0; i < 3; ++i) {
        CHECK(array2[i] == array1[i]);
    }
}

TEST_CASE("Resize method") {
    ArrayT<int> array(3);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;

    array.Resize(5);
    CHECK(array.Size() == 5);
    CHECK(array[0] == 1);
    CHECK(array[1] == 2);
    CHECK(array[2] == 3);
    CHECK(array[3] == 0);
    CHECK(array[4] == 0);

    array.Resize(2);
    CHECK(array.Size() == 2);
    CHECK(array[0] == 1);
    CHECK(array[1] == 2);
}

TEST_CASE("Insert method") {
    ArrayT<int> array(3);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;

    array.Insert(1, 42);
    CHECK(array.Size() == 4);
    CHECK(array[0] == 1);
    CHECK(array[1] == 42);
    CHECK(array[2] == 2);
    CHECK(array[3] == 3);

    array.Insert(4, 100);
    CHECK(array[4] == 100);

    CHECK_THROWS_AS(array.Insert(-1, 50), std::invalid_argument);
    CHECK_THROWS_AS(array.Insert(100, 50), std::invalid_argument);
}

TEST_CASE("Remove method") {
    ArrayT<int> array(5);
    array[0] = 10;
    array[1] = 20;
    array[2] = 30;
    array[3] = 40;
    array[4] = 50;

    array.Remove(2);
    CHECK(array.Size() == 4);
    CHECK(array[0] == 10);
    CHECK(array[1] == 20);
    CHECK(array[2] == 40);
    CHECK(array[3] == 50);

    CHECK_THROWS_AS(array.Remove(-1), std::invalid_argument);
    CHECK_THROWS_AS(array.Remove(100), std::invalid_argument);
}

TEST_CASE("Operator[] and Out of range checks") {
    ArrayT<int> array(3);
    array[0] = 100;
    array[1] = 200;
    array[2] = 300;

    CHECK(array[0] == 100);
    CHECK(array[1] == 200);
    CHECK(array[2] == 300);

    CHECK_THROWS_AS(array[-1], std::invalid_argument);
    CHECK_THROWS_AS(array[3], std::invalid_argument);
}

TEST_CASE("Check destructor and memory cleanup") {
    ArrayT<int>* array = new ArrayT<int>(100);
    delete array; // Программа не должна падать при удалении
}

TEST_CASE("Resize to zero") {
    ArrayT<int> array(5);
    array.Resize(0);
    CHECK(array.Size() == 0);
}

TEST_CASE("Check exception for Resize with negative size") {
    ArrayT<int> array;
    CHECK_THROWS_AS(array.Resize(-5), std::invalid_argument);
}