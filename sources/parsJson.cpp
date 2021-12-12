//Copyright 2021 noname
// Created by noname on 12/12/21.
//

#include "nlohmann.hpp"
#include "students.hpp"

json takeJson(int argc, char** argv) {
  if (argc < 2) throw std::runtime_error{"The file path was not passed"};
  std::string filePath(argv[1]);
  std::ifstream jsonFile(filePath);
  if (!jsonFile) throw std::runtime_error{"unable to open json: " + filePath};
  json data;
  jsonFile >> data;
  if (!data.at("items").is_array())
    throw std::runtime_error{"the array must be contained in the file"};
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>())
    throw std::runtime_error{"_meta value does not match the array size"};
  return data;
}

std::vector<Student> parsJson(json& data)
{
  std::vector<Student> students;
  for (auto const& item : data.at("items"))
  {
    Student student1;
    from_json(item, student1);
    students.push_back(student1);
  }

  std::vector<Student> students2;
  for (auto const& item : data.at("items")) {
    auto student = item.get<Student>();
    students2.push_back(student);
  }
  return students;
}