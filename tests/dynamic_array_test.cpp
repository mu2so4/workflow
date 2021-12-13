#include "../dynamic_array.h"
#include <catch2/catch_test_macros.hpp>
#include <fstream>

TEST_CASE("int filling", "[int-dynamic]") {
    auto *arr = new DynamicArray<int>{};
    const int SIZE = 1234;
    for(int index = 0; index < SIZE; index++)
        arr->pushBack(index * 2);

    std::pair<int*, int> res = arr->exportData();
    delete arr;
    REQUIRE(res.second == SIZE);

    for(int index = 0; index < SIZE; index++)
        REQUIRE(( res.first[index] == index * 2 ));

    delete[] res.first;
}

TEST_CASE("string filling", "[string-dynamic]") {
    auto *arr = new DynamicArray<std::string>{};
    const int SIZE = 24;
    std::ifstream in("../tests/file1.txt");
    auto *check = new std::string[SIZE];
    for(int index = 0; index < SIZE; index++) {
        std::string str;
        in >> str;
        arr->pushBack(str);
        check[index] = str;
    }


    std::pair<std::string*, int> res = arr->exportData();
    delete arr;
    REQUIRE(res.second == SIZE);

    for(int index = 0; index < SIZE; index++)
        REQUIRE(( res.first[index] == check[index] ));

    delete[] res.first;
    delete[] check;
}
