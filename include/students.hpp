//Copyright 2021 noname

#ifndef INCLUDE_STUDENTS_HPP_
#define INCLUDE_STUDENTS_HPP_

//#include <vector>
//#include <string>
#include <any>
#include <string>
#include <vector>
#include "nlohmann.hpp"

struct Student {
 public:
  Student();
  Student(std::string _name, std::any _group, std::any _avg, std::any _debt);
  bool operator == (Student const & student) const;
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void from_json(const json& j, Student& s);

std::vector<Student> parsJson(json& data);

#endif // INCLUDE_STUDENTS_HPP_
