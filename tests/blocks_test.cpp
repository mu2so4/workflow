#include "../blocks.h"
#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <iostream>
#include <cstring>

TEST_CASE("readfile-test", "[readfile]") {
    Buffer buf;
    const int SIZE = 24;
    FileReader reader;
    reader.run("readfile ../tests/file1.txt", buf);
    REQUIRE(( buf.size == SIZE ));

    for(int index = 0; index < SIZE; index++)
        std::cout << buf.data[index] << '\n';

    try {
        reader.run("readfile ../tests/file1.txt", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops\n";
        REQUIRE(( std::strcmp(err.what(),"attempt to read one more file\n") == 0 ));
    }

    buf.isLoaded = false;
    try {
        reader.run("readfile file1.txt", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops2\n";
        REQUIRE(( std::strcmp(err.what(),"file1.txt not found\n") == 0 ));
    }

    try {
        reader.run("readfile ../tests/file1.txt uei", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops3\n";
        REQUIRE(( std::strcmp(err.what(),"too many arguments for reading\n") == 0 ));
    }

    try {
        reader.run("readfile", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops4\n";
        REQUIRE(( std::strcmp(err.what(),"too few arguments for reading\n") == 0 ));
    }
}

TEST_CASE("writefile-test", "[writefile]") {
    Buffer buf;
    FileReader reader;
    reader.run("readfile ../tests/file1.txt", buf);

    FileWriter writer;
    writer.run("writefile ../tests/out.txt", buf);
    REQUIRE(( buf.isSaved ));
    REQUIRE(( buf.data == nullptr ));
    REQUIRE(( buf.size == 0 ));

    try {
        writer.run("writefile ../tests/out2.txt", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops\n";
        REQUIRE(( std::strcmp(err.what(),"attempt to write one more file\n") == 0 ));
    }

    buf.isSaved = false;
    writer.run("writefile ../tests/out2.txt", buf);

    buf.isSaved = false;

    try {
        writer.run("writefile ../tests/file1.txt uei", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops3\n";
        REQUIRE(( std::strcmp(err.what(),"too many arguments for writing\n") == 0 ));
    }

    try {
        writer.run("writefile", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops4\n";
        REQUIRE(( std::strcmp(err.what(), "too few arguments for writing\n") == 0 ));
    }

    try {
        writer.run("readfile ../tests/file1.txt", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops5\n";
        REQUIRE(( std::strcmp(err.what(),"attempt to do something else, not writing\n") == 0 ));
    }

    system("rm ../tests/out2.txt");
}

TEST_CASE("dump-test", "[dump]") {
    Buffer buf;
    FileReader reader;
    reader.run("readfile ../tests/file1.txt", buf);

    FileDumper dumper;
    dumper.run("dump ../tests/out.txt", buf);
    REQUIRE(( buf.isDumped ));
    REQUIRE(( buf.data != nullptr ));
    REQUIRE(( buf.size != 0 ));

    try {
        dumper.run("dump ../tests/out2.txt", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops\n";
        REQUIRE(( std::strcmp(err.what(),"attempt to do one more dumping\n") == 0 ));
    }

    buf.isDumped = false;
    dumper.run("dump ../tests/out2.txt", buf);

    buf.isDumped = false;

    try {
        dumper.run("dump ../tests/file1.txt uei", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops3\n";
        REQUIRE(( std::strcmp(err.what(),"too many arguments for dumping\n") == 0 ));
    }

    try {
        dumper.run("dump", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops4\n";
        REQUIRE(( std::strcmp(err.what(), "too few arguments for dumping\n") == 0 ));
    }

    try {
        dumper.run("writefile ../tests/file1.txt", buf);
    }
    catch(std::exception &err) {
        std::cout << "oops5\n";
        REQUIRE(( std::strcmp(err.what(),"attempt to do something else, not dumping\n") == 0 ));
    }
}

TEST_CASE("sort-test", "[sort]") {
    Buffer buf;
    const int SIZE = 24;
    FileReader reader;
    reader.run("readfile ../tests/file1.txt", buf);

    Sorter sorter;
    sorter.run("sort", buf);

    std::ofstream out("../tests/out.txt");
    for(int index = 0; index < SIZE; index++)
        out << buf.data[index] << '\n';
    out.close();

    for(int index = 1; index < SIZE; index++) {
        REQUIRE(( buf.data[index - 1].compare(buf.data[index]) < 0 ));
    }
}

TEST_CASE("replace-test", "[replace]") {
    std::ifstream in("../tests/file2.txt");
    Buffer buf;
    const int SIZE = 29;
    buf.data = new std::string[SIZE];
    buf.size = SIZE;
    for(int index = 0; index < SIZE; index++) {
        getline(in, buf.data[index]);
    }
    buf.isLoaded = true;
    in.close();

    Replacer sorter;
    sorter.run("replace no yes", buf);

    std::ofstream out("../tests/out.txt");
    for(int index = 0; index < SIZE; index++)
        out << buf.data[index] << '\n';
    out.close();

    try {
        sorter.run("replace no yes oeuiuh ehoudoehnuh", buf);
    }
    catch(std::exception &err) {
        REQUIRE(( std::strcmp(err.what(), "too many arguments for replacement\n") == 0 ));
    }

    try {
        sorter.run("replace no", buf);
    }
    catch(std::exception &err) {
        REQUIRE(( std::strcmp(err.what(), "too few arguments for replacement\n") == 0 ));
    }

    try {
        sorter.run("riplace no yes", buf);
    }
    catch(std::exception &err) {
        REQUIRE(( std::strcmp(err.what(), "attempt to do something else, not replacement\n") == 0 ));
    }
}

TEST_CASE("grep-test", "[grep]") {
    Buffer buf;
    FileReader reader{};
    reader.run("readfile ../tests/file3.txt", buf);

    Grepper grepper;
    grepper.run("grep wor", buf);

    std::ofstream out("../tests/out.txt");
    for(int index = 0; index < buf.size; index++)
        out << buf.data[index] << '\n';
    out.close();

    try {
        grepper.run("grep wor m", buf);
    }
    catch(std::exception &err) {
        REQUIRE(( std::strcmp(err.what(), "too many arguments for grep\n") == 0 ));
    }

    try {
        grepper.run("grep", buf);
    }
    catch(std::exception &err) {
        REQUIRE(( std::strcmp(err.what(), "too few arguments for grep\n") == 0 ));
    }

    try {
        grepper.run("egrep no yes", buf);
    }
    catch(std::exception &err) {
        REQUIRE(( std::strcmp(err.what(), "attempt to do something else, not grep\n") == 0 ));
    }
}