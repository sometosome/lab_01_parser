//Copyright 2021 noname
// Created by noname on 12/12/21.
//

#include "out.hpp"

std::string convert(std::any& item)
{
  std::stringstream ss;
  if (item.type() == typeid(std::nullptr_t)){
    ss << "null";
    return ss.str();
  }
  if (item.type() == typeid(std::string)){
    ss << std::any_cast<std::string>(item);
    return ss.str();
  }
  if (item.type() == typeid(double)){
    ss << std::any_cast<double>(item);
    return ss.str();
  }
  if (item.type() == typeid(std::vector<std::string>)){
    ss << std::any_cast<std::vector<std::string>>(item).size();
    auto str = ss.str() + " items";
    return ss.str();
  }
  if (item.type() == typeid(size_t)){
    ss << std::any_cast<size_t>(item);
    return ss.str();
  }
  ss << "error";
  return ss.str();
}

void print(std::string s1, std::string s2, std::string s3,
           std::string s4, std::ostream& os)
{
  os << "| " << std::setw(20) << std::left << s1 << "| "
     <<  std::setw(10) << std::left << s2 << "| "
     <<  std::setw(10) << std::left << s3 << "| "
     <<  std::setw(10) << std::left << s4 << "|\n"
     << "|---------------------|-----------|-----------|-----------|\n";
}

void print(Student& student, std::ostream& os)
{
  print(student.name, convert(student.group),
        convert(student.avg), convert(student.debt), os);
}

void print(std::vector<Student>& students, std::ostream& os)
{
  print("name", "group", "avg", "debt", os);
  for (Student& student : students) {
    print(student, os);
  }
}
