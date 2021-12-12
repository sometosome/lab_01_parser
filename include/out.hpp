//Copyright 2021 noname
// Created by noname on 12/11/21.
//

#ifndef TEMPLATE_OUT_HPP_
#define TEMPLATE_OUT_HPP_

#include "students.hpp"
#include <iomanip>
#include <string>
#include <vector>

void print(Student& student, std::ostream& os);

void print(std::string s1, std::string s2, std::string s3,
           std::string s4, std::ostream& os);

void print(std::vector<Student>& students, std::ostream& os);

#endif  // TEMPLATE_OUT_HPP_
