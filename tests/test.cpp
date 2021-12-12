// Copyright 2021 Your Name <your_email>

#include <stdexcept>

#include <gtest/gtest.h>

#include <out.hpp>

#ifndef _JSON_DIR
#define JSON_DIR "nobody"
#else
#define JSON_DIR _JSON_DIR
#endif

//Вывод одного Item'а
TEST(printTest, StudentItem)
{
  std::stringstream ss;
  Student s("test", (std::string)"test", (size_t)3, std::vector<std::string>());
  print(s, ss);
  ASSERT_EQ("| test                | test      | 3         | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}

//Вывод нескольких Item'ов
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

//Проверка эквивалентности Item'а
TEST(printTest, json)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"1\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Sidorov Ivan\",\n"
      "      \"group\": 31,\n"
      "      \"avg\": 4,\n"
      "      \"debt\": \"C++\"\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Pertov Nikita\",\n"
      "      \"group\": \"IU8-31\",\n"
      "      \"avg\": 3.33,\n"
      "      \"debt\":  [\n"
      "        \"C++\",\n"
      "        \"Linux\",\n"
      "        \"Network\"\n"
      "      ]\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 3\n"
      "  }\n"
      "}";

  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = parsJson(_json);
  std::stringstream ss;
  print(students_parsed, ss);
  ASSERT_EQ("| name                | group     | avg       | debt      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Ivanov Petr         | 1         | 4.25      | null      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Sidorov Ivan        | 31        | 4.00      | C++       |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Pertov Nikita       | IU8-31    | 3.33      | 3 items   |\n"
      "|---------------------|-----------|-----------|-----------|\n", ss.str());
}

//Проверка эквивалентности Student'ов
TEST(parseTest, jsonParse)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"1\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Sidorov Ivan\",\n"
      "      \"group\": 31,\n"
      "      \"avg\": 4,\n"
      "      \"debt\": \"C++\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 3\n"
      "  }\n"
      "}";
  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = parsJson(_json);
  std::vector<Student> student_inited = {
      Student("Ivanov Petr", (std::string)"1",
              (std::string)"4.25", nullptr),
      Student("Sidorov Ivan", (size_t)31,
              (size_t)4, (std::string)"C++")
  };
  ASSERT_EQ(student_inited, students_parsed);
}

//Проверка эквивалентности Item'а из файла
TEST(parseTest, fromFile)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"1\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Sidorov Ivan\",\n"
      "      \"group\": 31,\n"
      "      \"avg\": 4,\n"
      "      \"debt\": \"C++\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 3\n"
      "  }\n"
      "}";
  nlohmann::json json1 = json::parse(jsonData);
  std::string path = JSON_DIR;
  path+="/test1.json";
  char* argv[] ={(char*)"", (char*)(path.c_str())};
  nlohmann::json json2 = takeJson(2, argv);
  ASSERT_EQ(json1, json2) << "Test passed!";
}

//Проверка с отсутствием аргумента
TEST(errorCheck, lessArgsTest)
{
  try {
    std::string path = JSON_DIR;
    path+="test1.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = takeJson(1, argv);
    FAIL() << "Expected: The file path was not passed";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("The file path was not passed"));
  }
  catch(...) {
    FAIL() << "Expected The file path was not passed";
  }
}

//Проверка эквивалентности _meta
TEST(errorCheck, _metaCheck)
{
  try {
    std::string path = JSON_DIR;
    path+="/test2.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = takeJson(2, argv);
    FAIL() << "Expected: _meta value does not match the array size";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("_meta value does not match the array size"));
  }
  catch(...) {
    FAIL() << "Expected: _meta value does not match the array size";
  }
}