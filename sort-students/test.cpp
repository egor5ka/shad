#include <catch.hpp>
#include "sort_students.h"
#include <vector>
#include <string>

TEST_CASE("SortStudents by date") {
    std::vector<Student> students = {
        {"Egor", "Ivanov", 2000, 5, 20},
        {"Anna", "Petrova", 1999, 12, 15},
        {"Ivan", "Sidorov", 2000, 5, 20},
        {"Olga", "Ivanova", 2001, 1, 10}
    };

    SortStudents(&students, SortType::kByDate);

    REQUIRE(students[0].name == "Anna");
    REQUIRE(students[1].name == "Egor");
    REQUIRE(students[2].name == "Ivan");
    REQUIRE(students[3].name == "Olga");
}

TEST_CASE("SortStudents by name") {
    std::vector<Student> students = {
        {"Egor", "Ivanov", 2000, 5, 20},
        {"Anna", "Petrova", 1999, 12, 15},
        {"Ivan", "Sidorov", 2000, 5, 20},
        {"Olga", "Ivanova", 2001, 1, 10}
    };

    SortStudents(&students, SortType::kByName);

    REQUIRE(students[0].surname == "Ivanov");
    REQUIRE(students[0].name == "Egor");

    REQUIRE(students[1].surname == "Ivanova");
    REQUIRE(students[1].name == "Olga");

    REQUIRE(students[2].surname == "Petrova");
    REQUIRE(students[2].name == "Anna");

    REQUIRE(students[3].surname == "Sidorov");
    REQUIRE(students[3].name == "Ivan");
}
