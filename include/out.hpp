//
// Created by noname on 12/11/21.
//

#ifndef TEMPLATE_OUT_HPP
#define TEMPLATE_OUT_HPP

#include "students.hpp"
#include <iomanip>

void print(Student& student, std::ostream& os);

void print(std::string s1, std::string s2, std::string s3, std::string s4, std::ostream& os);

void print(std::vector<Student>& students, std::ostream& os);

#endif  // TEMPLATE_OUT_HPP
