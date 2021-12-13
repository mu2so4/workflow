#include "../workflow.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("reading config file", "[read-config]") {
    Workflow flow;
    flow.init("../tests/config0.txt");
    flow.work();
}