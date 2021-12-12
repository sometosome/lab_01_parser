#include <iostream>
#include "out.hpp"


int main(int argc, char** argv)
{
  nlohmann::json data = takeJson(argc, argv);
  std::vector<Student> students = parsJson(data);
  print(students, std::cout);
}