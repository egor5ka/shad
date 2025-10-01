#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

struct Student {
    std::string name, surname;
    int year, month, day;
};

enum class SortType { kByName, kByDate };

inline void SortStudents(std::vector<Student> *students, SortType sort_type) {
    std::sort(students->begin(), students->end(), [sort_type](const Student& student1, const Student& student2) {
        if (sort_type == SortType::kByDate) {
        return std::tie(student1.year, student1.month, student1.day, student1.surname, student1.name) <
            std::tie(student2.year, student2.month, student2.day, student2.surname, student2.name);
    }
    return std::tie(student1.surname, student1.name, student1.year, student1.month, student1.day) <
           std::tie(student2.surname, student2.name, student2.year, student2.month, student2.day);
    });
}
