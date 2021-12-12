// Copyright 2021 Your Name <your_email>

#include <stdexcept>

#include <gtest/gtest.h>

#include <out.hpp>

TEST(printTest, StudentItem)
{
  std::stringstream ss;
  Student s("test", (std::string)"test", (size_t)3, std::vector<std::string>());
  print(s, ss);
  ASSERT_EQ("| test                | test      | 3         | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, StudentsArray) {
  std::stringstream ss;
  std::vector<Student> students;
  students.emplace_back("test", (std::string)"test",
                        (size_t)3, std::vector<std::string>());
  students.emplace_back("test", (size_t)4,
                        (double)3.33, std::vector<std::string>());
  print(students, ss);
  ASSERT_EQ("| name                | group     | avg       | debt      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| test                | test      | 3         | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| test                | 4         | 3.33      | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}