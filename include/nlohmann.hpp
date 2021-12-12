//Copyright 2021 noname
// Created by noname on 12/11/21.
//

#ifndef TEMPLATE_NLOHMANN_HPP_
#define TEMPLATE_NLOHMANN_HPP_

#include <nlohmann/json.hpp>
#include <fstream>


using nlohmann::json;

json takeJson(int argc, char** argv);

#endif  // TEMPLATE_NLOHMANN_HPP_
